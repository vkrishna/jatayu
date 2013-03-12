/*
File Name: parse.c
Project 3 ECE574A
Author: Venkata Krishna Nimmagadda
Email IDs: vkn@email.arizona.edu  vtbhat@email.arizona.edu
University of Arizona, Tucson
Description: This file contains all input parsing related
functions
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "../include/parse.h"
#include "../include/main.h"

int read_inputs_from_file(CUBE *F,CUBE *R, CUBE *D,char *filename )
{
  int index=0,no_of_inputs=0;
  char ch;
  char *token=NULL,*temp=NULL;
  char line[200];
  int read_flag=1;

  FILE *fp = fopen (filename, "r");

  while(read_flag)
    {
      index = 0;
      while (((ch = fgetc(fp))!= '\n'))
	{
	  if(ch == EOF)
	    {
	      read_flag = 0;
	      break;
	    }
	  else
	    {
	      line[index] = ch;
	      index++;
	    }
	}
      line[index] = '\0';

      if((token = strtok(line," ")) != NULL)
	{

	  if(token[0] == '#')
	    continue;
	  else if(!strcmp(token, ".i"))
	  {
	    no_of_inputs = atoi(strtok(NULL," "));
	    set_functions(F,no_of_inputs);
	    set_functions(R,no_of_inputs);
	    set_functions(D,no_of_inputs);

	  }
	  else if(!strcmp(token, ".ilb"))
	    {

	      for(index =0; index< no_of_inputs ;index++)
	      	{

	      	  token = strtok(NULL, " ");
	      	  if(token != NULL)
	      	    {
	      	      if(F->vars != NULL)
	      		F->vars[index] = token[0];
	      	      R->vars[index] = token[0];
	      	      D->vars[index] = token[0];
	      	    }

	      	}


	    }
	  else if(!strcmp(token,".o"))
	    {
	      if(atoi(strtok(NULL," ")) != 1)
		{			
		  printf("\noops! This program is only designed for single output function\n");
	          exit(0);
                }
	    }
	  else if (!strcmp(token,".ob"))
	    {
	       token = strtok(NULL, " ");
	       if(token != NULL)
	      	 {
	      	    opvar = token[0]; 
	      	 } 	    
	    }
	  else
	    {
	      temp = strtok(NULL," ");
	     
	      if(temp !=NULL)
		{
		  if(temp[0]=='1')
		{
		  for(index = 0; index <no_of_inputs ;index++)
		    {
		      F->data[F->rows][index] =  (token[index] == '-')?'2':token[index];

		    }
		  F->rows++;
		}
	      else if(temp[0]=='0')
		{
		  for(index = 0; index <no_of_inputs ;index++)
		    {
		      R->data[R->rows][index] = (token[index] == '-')?'2':token[index];

		    }
		  R->rows++;
		}
	      else if(temp[0]=='-')
		{
		  for(index = 0; index <no_of_inputs ;index++)
		    {
		      D->data[D->rows][index] = (token[index] == '-')?'2':token[index];

		    }
		  D->rows++;
		}
		}

	    }
	}
    }
  return 0;
}

int pow2(int exponent)
{
  int result=1;
  while(exponent--)
    {
      result *= 2;
    }

  return result;
}

int set_functions(CUBE *f, int no_of_inputs)
{
  int index;
  f->data = (char **) malloc(sizeof(char *)*pow2(no_of_inputs));
  if(f->data == NULL)
    printf("memory allocation failed\n");
  for(index = 0; index < pow2(no_of_inputs) ; index++)
    {
      f->data[index] = (char *) malloc (sizeof(char )*no_of_inputs);
      if(f->data[index] == NULL)
	printf("memory allocation failed\n");
    }
  f->vars = (char *) malloc (sizeof(char)*no_of_inputs);
  if(f->vars == NULL)
    printf("memory allocation failed\n");
  f->cols = no_of_inputs;
  f->rows = 0;

  return 0;
}

