/*
** expand.h
** 
** Made by krishna
** Login   <krishna@krishna-laptop>
** 
** Started on  Tue Nov 17 03:25:14 2009 krishna
** Last update Tue Nov 17 03:25:14 2009 krishna
*/

#ifndef   	FILE_OUTPUT_H_
# define   	FILE_OUTPUT_H_

#include "main.h"

#define TRUE 1
#define FALSE 0

//
void text_file_output (CUBE *org, CUBE *opt, CUBE *offset, CUBE *D,char *filename, char file_type);
void verilog_file_output (CUBE *, char *filename);
char row_exist (CUBE *f, int curr_row_index);
void cube_copy (CUBE *a, CUBE *b);

#endif 	    /* !FILE_OUTPUT_H_ */
