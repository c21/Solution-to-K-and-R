/* fsize: print size of file "name" */
void fsize(char *name)
{
    struct stat stbuf;
    if(stat(name, &stbuf) == -1) 
    {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if((stbuf.st_mode & S_IFMT) == S_IFOIR)
        dirwalk(name, fsize);
    printf("size: %8ld name:%s dev: %d ino: %d mode: %d\n", stbuf.st_size, name, stbuf.st_dev, stbuf.st_ino,
            stbuf.st_mode);
    
}

