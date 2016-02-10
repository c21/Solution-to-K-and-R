
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAXWORD 1000

#define MAX_SIZE 1000

struct tnode
{
        char *word;
        int wc;
        struct tnode *left;
        struct tnode *right;
};

int getword(char *, int);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);

char *input;
int file_len;
struct tnode* array[MAX_SIZE];
int tp = -1;

int mycompare(const void *p1, const void *p2)
{
	int w1 = (*(struct tnode**)p1)->wc;
	int w2 = (*(struct tnode**)p2)->wc;
	if(w1 > w2)
		return 1;
	else if(w1 == w2)
		return 0;
	else
		return -1;
}

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

/*	input = (char*)malloc(sizeof(char)*(file_stat.st_size+10));
	memset(input, 0, sizeof(input));
	process(buf, input);	
*/
	input = buf;
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
        		root = addtree(root, word);
		}
	}
	treeprint(root);
	printf("tp: %d\n", tp);
	qsort(array, tp+1, sizeof(struct tnode*), mycompare);

	for(i = 0; i <= tp; i++)
		printf("%d: %s\n", array[i]->wc, array[i]->word);	
        return 0;

}


struct tnode *talloc(void);
/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL) /* a new word has arrived */
	{
		p = talloc(); /* make a new node */
		p->word = strdup(w);
		p->wc = 1;
		p->left = p->right = NULL;
	} 
	else if ((cond = strcmp(w, p->word)) == 0)
		p->wc++;
	else if (cond < 0) 	/* less than into left subtree */
		p->left = addtree(p->left, w);
	else			/* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{

	int i;
	if (p != NULL) 
	{
		treeprint(p->left);
		array[++tp] = p;	
		treeprint(p->right);
	}

}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *)malloc(sizeof(struct tnode));
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




