
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAXWORD 1000

#define MAX_SIZE 100

struct tnode
{
        char *word[MAX_SIZE];
        char *prefix;
        int wc;
        struct tnode *left;
        struct tnode *right;
};

int getword(char *, int);
void process(char *buf, char *newfile);
struct tnode *addtree(struct tnode *p, char *w, char *prew);
void treeprint(struct tnode *p);

char *input;
int file_len;
int prefix_num;

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "lack of argument\n");
		exit(1);
	}
	prefix_num = strtol(argv[2], NULL, 10);
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

	input = (char*)malloc(sizeof(char)*(file_stat.st_size+10));
	memset(input, 0, sizeof(input));
	process(buf, input);	
/*
	FILE *fout = fopen("output_file.c", "w");
	if(fout == NULL)
	{
		fprintf(stderr, "cannot open file: output_file.c\n");
                exit(1);
	}
	fwrite(newfile, sizeof(char), file_len, fout);
	fclose(fout);		
*/

	char word[MAXWORD];
	struct tnode *root = NULL; 
        while (getword(word, MAXWORD) != '\0')
        {
                if(isalpha(word[0]))
		{
			char *prew = (char*)malloc(sizeof(char)*(strlen(word)+1));
        		memset(prew, 0, sizeof(prew));
        		strncpy(prew, word, prefix_num);
        		root = addtree(root, word, prew);
		}
	}
	treeprint(root);
        return 0;

}


struct tnode *talloc(void);
/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, char *prew)
{
	int cond, i;
	if (p == NULL) /* a new word has arrived */
	{
		p = talloc(); /* make a new node */
		p->prefix = strdup(prew); 
		p->word[0] = strdup(w);
		p->wc = 1;
		p->left = p->right = NULL;
	} 
	else if ((cond = strcmp(prew, p->prefix)) == 0)
	{
		for(i = 0; i < p->wc; i++)
		{
			if(strcmp(p->word[i], w) == 0)
				break;
		}
		if(i == p->wc)
			p->word[(p->wc)++] = strdup(w); /* repeated word */
	}
	else if (cond < 0) 	/* less than into left subtree */
		p->left = addtree(p->left, w, prew);
	else			/* greater than into right subtree */
		p->right = addtree(p->right, w, prew);
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	int i;
	if (p != NULL) 
	{
		treeprint(p->left);
		printf("%s:\n", p->prefix);
		for(i = 0; i < p->wc; i++)
			printf("\t%s\n", p->word[i]);
		treeprint(p->right);
	}
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *)malloc(sizeof(struct tnode));
}


void process(char *buf, char *newfile)
{
	int i = 0, len = strlen(buf);
	int b = 0;
	while(i < len)
	{
		if(buf[i] == '\"')
                {
                        newfile[b++] = buf[i];
                        i++;
                        while(i < len && buf[i] != '\"')
                        {
                                newfile[b++] = buf[i];
                        	if(i+1 < len && buf[i] == '\\')
				{
					i++;
					newfile[b++] = buf[i];
				}
			        i++;
                        }
                        newfile[b++] = buf[i];
                        i++;
                }
                else if(buf[i] == '\'')
                {
                        newfile[b++] = buf[i];
                        i++;
                        while(i < len && buf[i] != '\'')
                        {
                                newfile[b++] = buf[i];
				if(i+1 < len && buf[i] == '\\')
                                {
                                        i++;
                                        newfile[b++] = buf[i];
                                }
                                i++;
                        }
                        newfile[b++] = buf[i];
                        i++;
                }
		else if(i+1 < len && buf[i] == '/' && buf[i+1] == '*')
		{
			i = i+2;
			while(i+1 < len && !(buf[i] == '*' && buf[i+1] == '/'))
				i++;
			i = i+2;					
		}
		else if(i+1 < len && buf[i] == '/' && buf[i+1] == '/')
		{
			i = i+2;
			while(i < len && buf[i] != '\n')
				i++;
			i++;	
		}
		else
		{
			newfile[b++] = buf[i];
			i++;
		}
	}		
	file_len = b;	
}


/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word, pre;
	while (isspace(c = getch()))
		;
	if (c != '\0') 
		*w++ = c; 
	if (!isalpha(c)) 
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




