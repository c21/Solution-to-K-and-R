#include <stdlib.h>
#include <string.h>
struct nlist 
{	/* table entry: */
	struct nlist *next;	/* next entry in chain */
	char *name;		/* defined name */
	char *defn;		/* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}


/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np; 	/* found */
	return NULL;			/* not found */
}


struct nlist *lookup(char *);

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) 
	{ /* not found */
		np = (struct nlist *)malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} 
	else	/* already there */
		free((void *)np->defn); /* free previous defn */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAXWORD 1000

#define MAX_SIZE 1000


int getword(char *, int);

char *input, *output;
int file_len;
int output_len = 0;

int main(int argc, char *argv[])
{
	int i;
	if(argc != 2)
	{
		fprintf(stderr, "lack of argument\n");
		exit(1);
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		fprintf(stderr, "cannot open file: %s\n", argv[1]);
		exit(1);
	}
	struct stat file_stat;
	fstat(fileno(fp), &file_stat);
	char *buf = (char*)malloc(sizeof(char)*(file_stat.st_size+10));	
	memset(buf, 0, sizeof(buf));
	fread(buf, sizeof(char), file_stat.st_size, fp);			
	fclose(fp);

	input = buf;

	char word[MAXWORD];
	FILE *fout = fopen("output_file.c", "w");
        output = (char*)malloc(sizeof(char)*(file_stat.st_size+10));
        memset(output, 0, sizeof(output));
	struct nlist *p;

	while (getword(word, MAXWORD) != '\0')
        {

		if(strcmp(word, "#define") == 0)
		{
			char s[100];
			char t[100];
			getword(s, MAXWORD);
			getword(t, MAXWORD);
			install(s, t);			
		}
                else if((p = lookup(word)) != NULL)
			output_len += sprintf(output+output_len, "%s ", p->defn);
		else
			output_len += sprintf(output+output_len, word[0] == '\n'? "%s" : "%s ", word);	
	}
	fwrite(output, sizeof(char), output_len, fout);
        fclose(fout);
        return 0;

}




/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word, pre;
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c != '\0')
	{ 
		*w++ = c; 
	}
	if (!isalnum(c) && c != '#') 
	{ 
		*w = '\0'; 
		return c;
	}
	for (; --lim > 0; w++)
	{
		if (!isalnum(*w = getch()))
		{
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}



int bufp = 0;           /* next free position in buf */

int getch(void)  /* get a (possibly pushed back) character */
{
        return input[bufp++];
}

void ungetch(int c)  /* push character back on input */
{
	input[--bufp] = c;
}

