/*
File Name: logic_minimization.c
Project 3 ECE574A
Author: Venkata Krishna Nimmagadda
Email IDs: vkn@email.arizona.edu  vtbhat@email.arizona.edu
University of Arizona, Tucson
Description: This file contains all the functions related 
to customized boolean logic minimization: JATAYU
*/
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include"../include/main.h"
#include "../include/parse.h"
#include "../include/expand.h"

int logic_min(CUBE *F)
{
  int flag,index1,index2,roller,cost;
  char *black_board;
  SET ie_cubes;
  CUBE X,Y;

  ie_cubes.values = (int *)malloc(sizeof(int)*(F->rows));
  ie_cubes.num = 0;
  black_board = (char *)malloc (sizeof(char)*logic_min_two_power(F->cols));
  if(ie_cubes.values == NULL || black_board == NULL)
    {
      printf("memory allocation failed");
      exit(0);
    }
  //memset(ie_cubes->values,0,F->rows);
  for(index2=0;index2<F->rows;index2++)
    {
      memset(black_board,0,logic_min_two_power(F->cols));
      map_selected_cube(F,index2,black_board);
      map_other_cubes(F,index2,black_board);
      flag=0;
      for(index1=0;index1<logic_min_two_power(F->cols);index1++)
	{
	  if(black_board[index1] ==1)
	    {	
	      flag=1;
	    }
	}
      //for(index1=0;index1<logic_min_two_power(F->cols);index1++)
      //printf("%d\t",black_board[index1]);
      if(flag == 0)
	{
	  ie_cubes.values[ie_cubes.num++] = index2;
	}
    }

  cost = F->rows;
  cube_copy(&Y,F);
  //iterating for every possible set of inessential cubes
  for(roller=0;roller<logic_min_two_power(ie_cubes.num);roller++)
    {
      memset(black_board,0,logic_min_two_power(F->cols));
      cube_copy(&X,F);
      //remove the selected cubes by brute force every time
      for(index1=roller,index2 = 0;index2 < ie_cubes.num;index2++)
  	{
  	  if(index1%2 == 1)
  	    {
  	      remove_row(&X,ie_cubes.values[ie_cubes.num-1-index2]);
  	    }
	  index1=index1>>1;
  	}
      if(cost > X.rows)
	{
      if(is_cover_complete(&X,F,black_board) == 1 )
	{
	  cost = X.rows;

	  destroy_cube(&Y);
	  cube_copy(&Y,&X);
	}
	}
  
      destroy_cube(&X);
    }
  printf("\nhmm the optimized cost is %d and the cube is printed below\n",cost);
  destroy_cube(F);
  cube_copy(F,&Y);
  destroy_cube(&Y);
  print_cube(F);
  printf("\n");

}
int logic_min_value(int *cube)
{

}

int logic_min_two_power(int cols)
{
  int index,return_value=1;
  for(index=0;index<cols;index++)
    {
      return_value *= 2;
    }
  return return_value;
}

int map_selected_cube(CUBE *F,int row,char *black_board)
{
  int check=0,temp,index1,flag;
  //iterate for all possible values
  for(check =0; check < logic_min_two_power(F->cols);check++)
    {
      //make flag zero
      temp = check;
      flag = 0;

      for(index1=0;index1<F->cols;index1++)
	{
	  if((F->data[row][F->cols - index1-1]-'0') != temp%2)
	    {
	      if(F->data[row][F->cols-index1-1] != '2')
		{
		  //make flag one when necessary
		  flag =1;

		}
	    }

	  temp = temp>>1;
	}
      //check for flag
      if(flag == 0)
	{
	  //update the blackboard
	  black_board[check]++;
	}
    }
}

int map_other_cubes(CUBE *F, int row,char *black_board)
{
  int index1,index2,temp,flag,check;

  for(index1=0;index1<F->rows;index1++)
    {
      if(index1==row)
	continue;
      for(check =0; check < logic_min_two_power(F->cols);check++)
	{
	  //make flag zero
	  temp = check;
	  flag = 0;

	  for(index2=0;index2<F->cols;index2++)
	    {
	      if((F->data[index1][F->cols - index2-1]-'0') != temp%2)
		{
		  if(F->data[index1][F->cols-index2-1] != '2')
		    {
		      //make flag one when necessary
		      flag =1;
		    }
		}
	      temp = temp>>1;
	    }
	  //check for flag
	  if(flag == 0)
	    {
	      //update the blackboard
	      if(black_board[check])
		black_board[check]++;
	    }
	}

    }
}
int destroy_cube(CUBE *f)
{
  int index1;
  for(index1=0;index1<f->rows;index1++)
    {
      free(f->data[index1]);

    }
  free(f->data);
  f->data = NULL;
}

int is_cover_complete(CUBE *X, CUBE *F, char *black_board)
{
  int index1;
  map_cubes(X,1,black_board);
  map_cubes(F,2,black_board);
  if(X->rows ==0)
    return 0;
  for(index1=0;index1<logic_min_two_power(F->cols);index1++)
    {
      if((black_board[index1] == 1) || (black_board[index1] == 2))
	return 0;
    }
  return 1;
}

int map_cubes(CUBE *F, int iteration,char *black_board)
{
  int index1,index2,temp,flag,check;

  for(index1=0;index1<F->rows;index1++)
    {

      for(check =0; check < logic_min_two_power(F->cols);check++)
	{
	  //make flag zero
	  temp = check;
	  flag = 0;

	  for(index2=0;index2<F->cols;index2++)
	    {
	      if((F->data[index1][F->cols - index2-1]-'0') != temp%2)
		{
		  if(F->data[index1][F->cols-index2-1] != '2')
		    {
		      //make flag one when necessary
		      flag =1;
		    }
		}
	      temp = temp>>1;
	    }
	  //check for flag
	  if(flag == 0)
	    {
	      //update the blackboard
	      if(iteration ==1)
		black_board[check] = 1;
	      else if((black_board[check] == 0) || (black_board[check] == 1))
		black_board[check] = (2 + black_board[check]);
	    }
	}

    }
}
