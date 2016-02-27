#define NULL    0

typedef long Align; /* for alignment to long boundary */

/* block header: */
union header 
{   
    struct 
    {
        union header *ptr;  /* next block if on free list */
        unsigned size;      /* size of this block */
    } s;
    Align x;    /* force alignment of blocks */
};
typedef union header Header;

static Header *morecore(unsigned nu);
void free(void *ap);

static Header base;             /* empty list to get started */
static Header *freep = NULL;    /* start of free list */

#define MAXSIZE 100000

/* malloc: general-purpose storage allocator */
void *malloc(unsigned nbytes)
{
    if(nbytes > MAXSIZE)
        return NULL;

    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;
    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
    if((prevp = freep) == NULL)         /*no free list yet*/
    { 
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) 
    {
        if(p->s.size >= nunits)         /* big enough */
        {
            if (p->s.size == nunits)    /* exactly */
                prevp->s.ptr = p->s.ptr;
            else                        /* allocate tail end */
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if(p == freep) /* wrapped around free list */
            if((p = morecore(nunits)) == NULL)
                return NULL;    /* none left */
    }
}


#define NALLOC  1024    /* minimum #units to request */

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;
    if(nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if(cp == (char *)-1)   /* no space at all */
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up+1));
    return freep;
}


/* free: put block ap in free list */
void free(void *ap)
{
    Header *bp, *p;
    bp = (Header *)ap - 1;  /* point to block header */
    if(bp == NULL || bp->s.size < 0 || bp->s.size > MAXSIZE)
        return;

    for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;  /* freed block at start or end of arena */
    
    if (bp + bp->s.size == p->s.ptr)    /* join to upper nbr */
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } 
    else
        bp->s.ptr = p->s.ptr;
    
    if(p + p->s.size == bp)     /* join to lower nbr */
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } 
    else
        p->s.ptr = bp;
    freep = p;
}

/*
The standard library function calloc(n, size) returns a
pointer to n objects of size size, with the storage initialized to zero. Write
calloc, by calling malloc by modifying it
*/
void * calloc(unsigned n, unsigned size)
{
    void *p = malloc(n*size), *ip;
    if(p == NULL)  
        return NULL;
    for(ip = p; ip < p+n*size; ip++)
        *(int*)ip = 0;
    return p;   
}


/*
Write a routine bfree (p, n) that will free an arbitrary block p
of n characters into the free list maintained by mal1oc and free. By using
bfree, a user can add a static or external array to the free list at any time.
*/
void bfree(void *ap, unsigned n)
{
    Header *bp, *p;
    bp = (Header *)ap;  /* point to block header */
    bp->s.size = n*sizeof(char);

    for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;  /* freed block at start or end of arena */

    if (bp + bp->s.size == p->s.ptr)    /* join to upper nbr */
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;

    if(p + p->s.size == bp)     /* join to lower nbr */
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;
    freep = p; 
}

int a[100];
int main()
{
    int *p = malloc(sizeof(int));
    *p = 1;
    int *xp = calloc(100, sizeof(int));
    bfree(a, 100*sizeof(int));
    return 0;
}
