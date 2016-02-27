#define NULL        0
#define EOF         (-1)
#define BUFSIZ      1024
#define OPEN_MAX    20  /* max #files open at once */


typedef struct _flags     
{
    int _READ;   /* file open for reading */
    int _WRITE;   /* file open for writing */  
    int _UNBUF;   /* file is unbuffered */
    int _EOF;  /* EOF has occurred on this file */
    int _ERR;   /* error occurred on this file */
}_flags;

typedef struct iobuf 
{
    int cnt;    /* characters left */
    char *ptr;  /* next character position */
    char *base; /* location of buffer */
    _flags flag;   /* mode of file access */
    int fd;     /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];
#define stdin       (&_iob[0])
#define stdout      (&_iob[1])
#define stderr      (&_iob[2])


int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)     (--(p)->cnt >= 0 \
                    ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p)   (--(p)->cnt >= 0 \
                    ? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)

FILE _iob[OPEN_MAX] = 
{   /* stdin, stdout, stderr: */
    { 0, (char *) 0, (char *) 0, {1,0,0,0,0}, 0 },
    { 0, (char *) 0, (char *) 0, {0,1,0,0,0}, 1 },
    { 0, (char *) 0, (char *) 0, {0,1,1,0,0}, 2 }
};


#include <fcntl.h>
#include <stdlib.h>
#define PERMS 0666  /* RW for owner, group, others */

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;
    if(*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for(fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if( !fp->flag._READ && !fp->flag._WRITE)
//        if((fp->flag & (_READ | _WRITE)) == 0)
            break;              /* found free slot */
    if(fp >= _iob + OPEN_MAX)   /* no free slots */
        return NULL;
    if(*mode == 'w')
        fd = creat(name, PERMS);
    else if(*mode == 'a') 
    {
        if((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } 
    else
        fd = open(name, O_RDONLY, 0);
    if(fd == -1)                /* couldn't access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
//    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    if(*mode == 'r')
        fp->flag._READ = 1;
    else
        fp->flag._WRITE = 1;
    return fp;
}


/* fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;
//    if((fp->flag & (_READ | _EOF | _ERR)) != _READ)
    if(!fp->flag._READ || fp->flag._EOF || fp->flag._ERR)
        return EOF;
    bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
    if(fp->base == NULL)    /* no buffer yet */
        if((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;     /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if(--fp->cnt < 0) 
    {
        if(fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int main()
{

    FILE *fp = fopen("input.c", "r");
    printf("fp: %p\n", fp);
/*
    int c;
    while((c = getchar()) != EOF)
        putchar(c);
*/    return 0;
}
