#define NULL        0
#define EOF         (-1)
#define BUFSIZ      1024
#define OPEN_MAX    20  /* max #files open at once */

typedef struct iobuf 
{
    int cnt;    /* characters left */
    char *ptr;  /* next character position */
    char *base; /* location of buffer */
    int flag;   /* mode of file access */
    int fd;     /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];
#define stdin       (&_iob[0])
#define stdout      (&_iob[1])
#define stderr      (&_iob[2])

enum _flags 
{
    _READ   = 01,   /* file open for reading */ 
    _WRITE  = 02,   /* file open for writing */     
    _UNBUF  = 04,   /* file is unbuffered */
    _EOF    = 010,  /* EOF has occurred on this file */
    _ERR    = 020   /* error occurred on this file */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose(FILE *);
int fseek(FILE *, long, int);
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
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
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
        if((fp->flag & (_READ | _WRITE)) == 0)
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}


/* fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;
    if((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if(fp->base == NULL)    /* no buffer yet */
        if((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;     /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if(--fp->cnt < 0) 
    {
        if(fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

/* flushbuf: flush the buf to file*/
int _flushbuf(int x, FILE *fp)
{
    int bufsize;
    if((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
    {
        fp->flag |= _ERR;
        return EOF;
    }
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    fp->cnt = bufsize;
    if(fp->base == NULL)
    {
        if((fp->base = (char *) malloc(bufsize)) == NULL)
        {
            fp->flag |= _ERR;
            return EOF;
        }
        fp->ptr = fp->base; 
    }
    else
    {
        int rc = write(fp->fd, fp->base, bufsize);
        if(rc != bufsize)
        {
            fp->flag |= _ERR;
            return EOF;
        }
        fp->ptr = fp->base;
    }     
    *fp->ptr++ = x;
    fp->cnt--;
    return x;
}

/*fflush - flush a stream*/
int fflush(FILE *fp)
{
    FILE *nfp;
    int bufsize;
    // if fp is NULL, flush all open output streams
    if(fp == NULL)
    {
        for(nfp = _iob; nfp < _iob + OPEN_MAX; nfp++)
            if((nfp->flag & (_WRITE | _EOF | _ERR)) == _WRITE)
                if(fflush(nfp) != 0)
                    return EOF;
        return 0; 
    }
    if((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
    {
        fp->flag |= _ERR;
        return EOF;
    }
    if(fp->base == NULL)
        return 0;
    bufsize = ((fp->flag & _UNBUF) ? 1 : BUFSIZ) - fp->cnt;
    int rc = write(fp->fd, fp->base, bufsize);
    if(rc != bufsize)
    {
        fp->flag |= _ERR;
        return EOF;
    }    
    fp->ptr = fp->base;  
    fp->cnt += bufsize;
    return 0;
}


/*fclose: close a stream*/
int fclose(FILE *fp)
{
    if(fp == NULL)
        return EOF;
    FILE *nfp;
    for(nfp = _iob; nfp < _iob + OPEN_MAX; nfp++)
    {
        if(nfp == fp)
            break;
    }     
    if(nfp == _iob+OPEN_MAX)
        return EOF;
    // if output stream, flush it
    if((fp->flag & (_WRITE | _EOF | _ERR)) == _WRITE)
        if(fflush(fp) != 0)
            return EOF;
    // if buffer is not empty, free buffer     
    if(fp->base != NULL)
        free(fp->base);
    // set flag to 0
    fp->flag = 0;
    // close file
    if(close(fp->fd) != 0)
        return EOF;
    return 0;    
}


int fseek(FILE *fp, long offset, int origin)
{
    if(fp == NULL)
        return -1;
    FILE *nfp;
    for(nfp = _iob; nfp < _iob + OPEN_MAX; nfp++)
    {
        if(nfp == fp)
            break;
    }
    if(nfp == _iob+OPEN_MAX || (fp->flag & (_READ | _WRITE)) == 0)
        return -1;
    // if fp is output stream, first flush the buffer
    if(fp->flag & _WRITE != 0)
    {
        if(fflush(fp) != 0)
        {
            printf("error\n");
            return -1;
        }
    }
    // set buffer to empty
    else
    {
        if(fp->base != NULL)
        {
            fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
            fp->ptr = fp->base;            
        }
    }
    return lseek(fp->fd, offset, origin);        
}

int main()
{
    FILE *fin = fopen("input.c", "r");
    FILE *fout = fopen("output.c", "w");
    printf("fin: %p, fout: %p\n", fin, fout);

    int c;
    while((c = getc(fin)) != EOF)
 //       printf("c: %c\n", c);
        putc(c,fout);
    fflush(fout);    
//    lseek(fout->fd, 0L,0);
    fseek(fout, 0L, 0);
    putc('1', fout);
    printf("%d\n", fflush(fout));
    printf("%d, %d\n", fclose(fin), fclose(fout));
    
    return 0;
}
