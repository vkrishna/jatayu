/*
** main.h
** 
** Made by krishna
** Login   <krishna@krishna-laptop>
** 
** Started on  Mon Nov 16 21:51:36 2009 krishna
** Last update Mon Nov 16 21:51:36 2009 krishna
*/

#ifndef   	MAIN_H_
# define   	MAIN_H_

#define OPT_TEXT_OUTPUT 1
#define ESPEXP_TEXT_OUTPUT 2

/*Globals*/
extern char opvar;

typedef struct 
{
  int rows;
  int cols;
  char **data;
  char *vars;
} CUBE;


typedef struct 
{
  int num;
  int *values;
} SET;
#endif 	    /* !MAIN_H_ */
