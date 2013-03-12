/*
** parse.h
** 
** Made by krishna
** Login   <krishna@krishna-laptop>
** 
** Started on  Mon Nov 16 21:56:06 2009 krishna
** Last update Mon Nov 16 21:56:06 2009 krishna
*/

#ifndef   	PARSE_H_
# define   	PARSE_H_
#include "main.h"

//
int read_inputs_from_file(CUBE *F,CUBE *R, CUBE *D,char *filename );
int pow2(int exponent);
int set_function(CUBE *f,int);
int kill_function(CUBE *f);

#endif 	    /* !PARSE_H_ */
