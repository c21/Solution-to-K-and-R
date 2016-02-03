#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


void process(char *buf, char *newfile);
int file_len;


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

	char *newfile = (char*)malloc(sizeof(char)*(file_stat.st_size+10));
	memset(newfile, 0, sizeof(newfile));
	process(buf, newfile);	
/*
	FILE *fout = fopen("output_file.c", "w");
	if(fout == NULL)
	{
		fprintf(stderr, "cannot open file: output_file.c\n");
                exit(1);
	}
	fwrite(newfile, sizeof(char), file_len, fout);
	fclose(fout);		
*/	return 0;
}

void process(char *buf, char *newfile)
{
	int pc = 0, bkc = 0, bec = 0;

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
			if(buf[i] == '(')
				pc++;
			else if(buf[i] == ')')
			{
				pc--;
				if(pc < 0)
				{
					fprintf(stderr, "find unbalanced ()\n");
					exit(1);
				}						
			}
		
			if(buf[i] == '[')
                                bkc++;
                        else if(buf[i] == ']')
                        {
                                bkc--;
                                if(bkc < 0)
                                {
                                        fprintf(stderr, "find unbalanced []\n");
                                        exit(1);
                                }
                        }

			if(buf[i] == '{')
                                bec++;
                        else if(buf[i] == '}')
                        {
                                bec--;
                                if(bec < 0)
                                {
                                        fprintf(stderr, "find unbalanced {}\n");
                                        exit(1);
                                }
                        }
	
			newfile[b++] = buf[i];
			i++;
		}
	}		
	file_len = b;

	if(pc != 0)
		fprintf(stderr, "find unbalanced ()\n");
	if(bkc != 0)
                fprintf(stderr, "find unbalanced []\n");
	if(bec != 0)
                fprintf(stderr, "find unbalanced {}\n");
	if(pc != 0 || bkc != 0 || bec != 0)
		exit(1);
}
