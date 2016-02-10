
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
        int line[MAX_SIZE];
        char *word;
        int lc;
        struct tnode *left;
        struct tnode *right;
};

int getword(char *, int);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
int remove_noise(char *w);

char *input;
int file_len;
int line_count;

int main(int argc, char *argv[])
{
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
	line_count = 0;
        while (getword(word, MAXWORD) != '\0')
        {
		if(word[0] == '\n')
			line_count++;
                if(isalpha(word[0]) && !remove_noise(word))
		{
        		root = addtree(root, word);
		}
	}
	treeprint(root);
        return 0;

}

#define LIST_SIZE	2
char *list[] = {"the", "and"};
int remove_noise(char *w)
{
	int i;
	for(i = 0; i < LIST_SIZE; i++)
	{
		if(strcmp(list[i], w) == 0)
			return 1;
	}	
	return 0;
}
struct tnode *talloc(void);
/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond, i;
	if (p == NULL) /* a new word has arrived */
	{
		p = talloc(); /* make a new node */
		p->word = strdup(w);
		p->line[0] = line_count+1;
		p->lc = 1;
		p->left = p->right = NULL;
	} 
	else if ((cond = strcmp(w, p->word)) == 0)
	{

		for(i = 0; i < p->lc; i++)
		{
			if(p->line[i] == line_count+1)
				break;
		}
		if(i == p->lc)
			p->line[(p->lc)++] = line_count+1;

	}
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
		printf("%s: ", p->word);
		for(i = 0; i < p->lc; i++)
			printf("%d ", p->line[i]);
		printf("\n");
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




