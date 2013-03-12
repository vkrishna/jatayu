/*
File Name: expand.c
Project 3 ECE574A
Author: Venkata Krishna Nimmagadda
Email IDs: vkn@email.arizona.edu  vtbhat@email.arizona.edu
University of Arizona, Tucson
Description: This file contains all the functions related 
to execute Espresso Expand 

*/


#include<stdio.h>
#include <stdlib.h>

#include "../include/main.h"
#include "../include/expand.h"
#include "../include/parse.h"



int expand(CUBE *F, CUBE *R)
{
  int index,index1,index2;


  for(index = 0; index < F->rows ; index++)
    {
      expand1(F->data[index],R,F);
    }
    remove_duplicate_rows(F);     

}

int remove_duplicate_rows(CUBE *F)
{

  int index1,index2,index3,flag=0;
  for(index3=0;index3<F->rows;index3++)
  for(index1=0;index1<F->rows;index1++)
    {
      flag =0;
      for(index2=0;index2<F->cols;index2++)
	{
	  if(F->data[index3][index2] != F->data[index1][index2])
	    flag =1;
	}
      if(flag ==0 && index3!=index1)
	{
	  remove_row(F,index1);
	  index1--;
	}
    }
}

int remove_row(CUBE *F, int row)
{
  int index1,index2;
  for(index1=row; index1<F->rows-1;index1++)
    {
      for(index2 =0;index2<F->cols;index2++)
  	{

  	      F->data[index1][index2] = F->data[index1+1][index2];

  	}
    }
  if(F->data[F->rows] != NULL)
    {
      free(F->data[F->rows]);
      F->data[F->rows--] = NULL;
    }
  return 0;
}


int compare (char *str1, char *str2, int num)
{
  int index;
  for(index =0; index < num;index++)
    {
      if(str2[index] != '2' && str2[index] != str1[index])
	return 0;
    }
  return 1;

}

int expand1(char *c, CUBE *R, CUBE *F)
{
  CUBE B,C;
  SET L,RA;
  int index1,index2;
  signed int J,Xi;
  signed int X; //essential
  int flag;
  L.num = 0;
  L.values = (int *) malloc (sizeof(int)*(F->cols));
  if(L.values == NULL)
    {
      printf("\n memory allocation\n");
      exit(0);
    }
  RA.num =0;
  RA.values = (int *) malloc (sizeof(int)*(F->cols));
  if(RA.values ==NULL)
    {
      printf("\n memory allocation\n");
      exit(0);
    }

  set_functions(&B, R->cols);
  B.rows = R->rows;
  for(index1=0;index1<B.rows;index1++)
    {
      for(index2=0;index2 < B.cols ; index2++)
	{
	  if( (c[index2] =='1' &&  R->data[index1][index2]== '0')||(c[index2] =='0'&& R->data[index1][index2] == '1'))
	    {
	      B.data[index1][index2] = '1';
	    }
	  else 
	    {
	      B.data[index1][index2] = '0';
	    }
	  B.vars[index2] = index2;
	}
    }

  set_functions(&C, F->cols);
  C.rows = F->rows;
  for(index1=0;index1<C.rows;index1++)
    {
      for(index2=0;index2 < C.cols ; index2++)
	{
	  if( (c[index2] =='1' &&  F->data[index1][index2] != '1')||(c[index2] =='0'&& F->data[index1][index2] != '0'))
	    {
	      C.data[index1][index2] = '1';
	    }
	  else 
	    {
	      C.data[index1][index2] = '0';
	    }
	  C.vars[index2] = index2;
	}
    }
  while( ((L.num + RA.num) < F->cols) && (B.rows != 0 && B.cols != 0) && (C.rows !=0 && C.cols != 0) )
    {

      X = essentials(&B);
      if(X != -1 )
	{
	  L.values[L.num++] = B.vars[X];
	}
      elim1(&B,&C,X);
      if(X == -1)
	{
	  J=mfc(&C);
	  if(J == -1)
	    J=end_game(&B,&C);
	  elim2(&B,&C,J);
	
	  if(J!=-1)
	    RA.values[RA.num++] = C.vars[J];
	}
      if(( Xi=inessentials(&B)) != -1)
	{
	    RA.values[RA.num++] = B.vars[Xi];
	  elim2(&B,&C,Xi);
	}
    }
  if(B.rows !=0 &&  B.cols != 0 )
    minlow(&L,&B);


  for(index1=0;index1<F->cols;index1++)
    {
      flag =0;
      for(index2=0;index2<L.num;index2++)
	{
	  if(index1 == L.values[index2])
	    flag =1;

	} 
      if(flag != 1)
	c[index1] = '2';

    }

  free_set(&L);
  free_set(&RA);
  free_cube(&B);
  free_cube(&C);
}


signed int essentials(CUBE *B)
{
  int index1,index2;
  int sum=0,return_value ;

  for(index1 = 0; index1 < B->rows ; index1++)
    {
      sum = 0;
      for(index2 =0; index2 < B->cols; index2++)
	{
	  sum += (int) (B->data[index1][index2] - '0');
	  
	}
      if(sum == 1)
	{
	  for(index2=0;index2<B->cols;index2++)
	    if(B->data[index1][index2] == '1')
	      return index2;
	}
    }
  return -1;

}

int elim1(CUBE *B, CUBE *C, signed int col)
{
 signed  int index1,index2,index3,index4;

  if(col == -1)
    return 0;
  

  for(index1=0;index1<B->rows;index1++)
    {
      if(B->data[index1][col] == '1')
	{
	  for(index3 =index1; index3 < B->rows-1 ; index3++)
	    {
	      for(index4 =0;index4 <B->cols ; index4++)
		{
		  B->data[index3][index4] = B->data[index3+1][index4];
		}
		 
	    }
	  if(B->data[B->rows] != NULL)
	    {
	      free(B->data[B->rows]);
	      B->data[B->rows--] = NULL;
	    }
	  index1--;
	}

    }
  for(index1=0;index1< B->rows ; index1++)
    {
      for(index2=col;index2< (B->cols-1);index2++)
	{
	  B->data[index1][index2] = B->data[index1][index2+1];
	 
	}
    }
  for(index1 = col; index1<B->cols-1;index1++)
    {
      B->vars[index1] = B->vars[index1+1];
    }
  B->cols--;

  
  for(index1=0;index1<C->rows;index1++)
    {
      if(C->data[index1][col] == '1')
	{
	  for(index3 =index1; index3 < C->rows-1 ; index3++)
	    {
	      for(index4 =0;index4 <C->cols ; index4++)
		{
		  C->data[index3][index4] = C->data[index3+1][index4];
		}
		 
	    }
	  if(C->data[C->rows] != NULL)
	    {
	      free(C->data[C->rows]);
	      C->data[C->rows--] = NULL;
	    }
	  index1--;
	}

    }
  for(index1=0;index1< C->rows ; index1++)
    {
      for(index2=col;index2< C->cols-1;index2++)
	{
	  C->data[index1][index2] = C->data[index1][index2+1];

	}
    }
  for(index1 = col; index1<C->cols-1;index1++)
    {
      C->vars[index1] = C->vars[index1+1];
    }

  C->cols--;
}

signed int mfc(CUBE *C)
{
  int index1,index2,sum;
  for(index1=0;index1< C->rows ;index1++)
    {
      sum =0;
      for(index2=0;index2< C->cols;index2++)
	{
	  sum += (int)(C->data[index1][index2] - '0');
	}

      if(sum == 1)
	{
	  for(index2=0;index2< C->cols;index2++)
	    if(C->data[index1][index2] == '1')
	      {
		return index2;
	      }
	}
    }
  return -1;

}

signed int end_game(CUBE *B, CUBE *C)
{
  int index1,index2,sum,return_value;

  if(B->rows == 0 || B->cols == 0)
    {
      for(index1=0;index1 < C->cols;index1++)
	{
	  return index1;
	}
      return -1;
    }
  else
    {
      if( (C->rows !=0) && (C->cols != 0) )
	{
	  for(index1=0;index1<C->cols;index1++)
	    {
	      sum = 0;
	      for(index2=0;index2< C->rows;index2++)
		{
		  sum += (int)(C->data[index2][index1] - '0');
		}
	      if(index1==0)
		{
		  return_value = index1;
		}
	      else if(sum > return_value)
		  return_value = index1;

	    }
	  return return_value;
	}
    }
}


signed int inessentials(CUBE *B)
{
  int index1,index2,sum;

  for(index1=0;index1<B->cols;index1++)
    {
      sum =0;
      for(index2=0;index2 < B->rows; index2++)
	{
	  sum += (int) (B->data[index2][index1]-'0');
	}
      if(sum ==0)
	{
	  return index1;
	}
    }
  return -1;
}



int elim2(CUBE *B, CUBE *C,signed int J)
{
  int index1,index2, index3;
  int sum;
  if(J != -1)
    {
      for(index1=J;index1< B->cols-1;index1++)
	{
	  for(index2=0;index2 < B->rows ; index2++)
	    {
	      B->data[index2][index1] = B->data[index2][index1+1];

	    }
	}
  for(index1 = J; index1<B->cols-1;index1++)
    {
      B->vars[index1] = B->vars[index1+1];
    }

      B->cols--;
      for(index1=J;index1< C->cols-1;index1++)
	{
	  for(index2=0;index2<C->rows;index2++)
	    {
	      C->data[index2][index1] = C->data[index2][index1+1];

	    }
	}
  for(index1 = J; index1<C->cols-1;index1++)
    {
      C->vars[index1] = C->vars[index1+1];
    }

      C->cols--; 
    }
  for(index1=0;index1<C->rows;index1++)
    {
      sum = 0;
      for(index2=0;index2< C->cols;index2++)
	{
	  sum += (int) (C->data[index1][index2]-'0');
	}
      if(sum == 0)
	{
	  for(index2=index1;index2<C->rows-1;index2++)
	    {
	      for(index3=0;index3 < C->cols; index3++)
		{
		  C->data[index2][index3] = C->data[index2+1][index3];
		}
	    }
	  if(C->rows >0)
	    free(C->data[C->rows--]);

	  index1--;
	}
    }
}



int minlow(SET *L, CUBE *B)
{
  int index1;

  for(index1=0;index1 < B->cols ; index1++)
    {
      L->values[L->num++] = B->vars[index1];
    }
}


int print_cube(CUBE *f)
{
  int index1,index2;
  for(index1=0;index1 < f->rows;index1++)
    {
      for(index2=0;index2< f->cols; index2++)
	{
	  printf("%c\t",f->data[index1][index2]);
	}
      printf("\n");
    }
  printf("Vars are\n");
  for(index1=0;index1 < f->cols ; index1++)
    {
      printf("%c\t",f->vars[index1]);
    }
  return 0;
}

int print_set(SET *s)
{
  int index;
  for(index =0;index <s->num;index++)
    {
      printf("%d\t",s->values[index]);
    }
}

int free_set(SET *s)
{
  free(s->values);
  s->values = NULL;
}

int free_cube(CUBE *f)
{
  int index1;
  for(index1=0;index1 < f->rows; index1++)
    {
      free(f->data[index1]);
    }
  free(f->data);
  f->data = NULL;
}
