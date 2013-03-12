/*
File Name: file_output.c
Project 3 ECE574A
Author: Vivek Tulsidas
Email IDs: vtbhat@email.arizona.edu vkn@email.arizona.edu 
University of Arizona, Tucson
Description: This file contains all the functions related 
to generation of output file formats
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file_output.h"
#include "../include/main.h"


void text_file_output (CUBE *org, CUBE *opt, CUBE *offset, CUBE *D, 
		char *filename, char file_type)
{
   FILE *fp;
   char check;
   int index1,index2;
   
   strcat(filename, ".txt");

   /*open file*/
   fp = fopen(filename , "w");
   
   /*err handling*/
   if (fp == NULL)
    {
       printf("Error opening file %s\n", filename);
       return;       
    }
   
   /*initial comments*/
   fprintf(fp, "#CAD proj 3\n"); 
   
   /*print the original fxn*/
   fprintf(fp, "#%c = ", opvar);
   
   for (index1 = 0; index1 < org->rows; index1++)
     {
        for (index2 = 0; index2 < org->cols; index2++)
          {		     
	     if (org->data[index1][index2] == '2')
	          continue;
	     else 
	       { 
		  fprintf(fp,"%c", org->vars[index2]); 	       
	          if (org->data[index1][index2] == '0')
		   {
		      fprintf(fp,"'");	   
		   }	   
               }	     
          }
	if (index1 != ((org->rows) - 1))  
          fprintf(fp," + ");	
     }
   
   fprintf(fp, "\n");

   /*print the optimized fxn*/
   if (file_type == OPT_TEXT_OUTPUT)
     {
         fprintf(fp, "#%c (optimized) = ", opvar);
     }
   else if (file_type == ESPEXP_TEXT_OUTPUT)
     {
         fprintf(fp, "#%c (espresso expand) = ", opvar);
     }
 
   for (index1 = 0; index1 < opt->rows; index1++)
     {
	 /*check if row already has been printed*/     
         if (row_exist (opt, index1))
	    continue;
	 if (index1 != 0)  
            fprintf(fp," + ");
	 for (index2 = 0; index2 < opt->cols; index2++)
          {		     
	     if (opt->data[index1][index2] == '2')
	          continue;
	     else 
	       { 
		  fprintf(fp,"%c", opt->vars[index2]); 	       
	          if (opt->data[index1][index2] == '0')
		   {
		      fprintf(fp,"'");	   
		   }	   
               }	     
          }
		
     }
   fprintf(fp,"\n");
   fprintf(fp,"\n");   

   /*print the other parameters*/
   fprintf(fp,".i %d\n",opt->cols);
   fprintf(fp,".o 1\n");
   fprintf(fp,".ilb ");
   for(index1 = 0; index1 < opt->cols; index1++)
     {		     
	fprintf(fp,"%c ",opt->vars[index1]);     	     
     }
   fprintf(fp,"\n");
   fprintf(fp,".olb %c\n", opvar);
   
   fprintf(fp,"\n");

   /*print the truth table*/
   /*first the onset*/
   for (index1 = 0; index1 < opt->rows; index1++)
     {
	 /*check if row already has been printed*/     
         if (row_exist (opt, index1))
	     continue;

	 for (index2 = 0; index2 < opt->cols; index2++)
          {		     
	     fprintf(fp,"%c", check = ((opt->data[index1][index2] == '2')?'-':opt->data[index1][index2]));	     
          }
         fprintf(fp," 1\n");  	 
     }
   
   /*then the offset*/
   for (index1 = 0; index1 < offset->rows; index1++)
     {    
	 for (index2 = 0; index2 < offset->cols; index2++)
          {		     
	     fprintf(fp,"%c", check = ((offset->data[index1][index2] == '2')?'-':offset->data[index1][index2]));	     
          }
	 fprintf(fp," 0\n");		 
     } 
   fprintf(fp,"\n\n.e");

   fclose(fp);		
}/*end of text_file_output*/


void verilog_file_output (CUBE *F, char *filename)
{
   FILE *fp;
   char check = FALSE;
   int index1,index2;
   
   strcat(filename, ".v");

   /*open file*/
   fp = fopen(filename , "w");
   
   /*err handling*/
   if (fp == NULL)
    {
       printf("Error opening file %s\n", filename);
       return;       
    }
   
   /*initial comments*/
   fprintf(fp,"`timescale 1ns / 1ps\n");
   fprintf(fp, "//CAD proj 3\n");
   
   /*define the module*/
   fprintf(fp , "module logic_min( ");
   for (index1 = 0; index1 < F->cols; index1++)
     {
	fprintf(fp, "%c,",F->vars[index1]);     
     }
   fprintf(fp, "%c);\n",opvar);

   /*body of the verilog file*/
   /*input and output variables*/
   fprintf(fp , "\t");
   for (index1 = 0; index1 < F->cols; index1++)
     {
	fprintf(fp, "input %c;\n\t",F->vars[index1]);     
     }
   fprintf(fp, "output reg %c;\n\n\t",opvar);

   /*senstivity list*/
   fprintf(fp, "always @(");
   for (index1 = 0; index1 < F->cols; index1++)
     {
	fprintf(fp, "%c",F->vars[index1]);
        if (index1 != (F->cols - 1))
	   fprintf(fp , " or ");	
     }
   fprintf (fp, ")\n\tbegin\n\t\t");
   
    /*print the optimized fxn*/
   fprintf(fp, "%c <= ", opvar);
   
   for (index1 = 0; index1 < F->rows; index1++)
     {
	 /*check if row already has been printed*/     
         if (row_exist (F, index1))
	    continue;
	 if (index1 != 0)  
            fprintf(fp," | ");
	 for (index2 = 0; index2 < F->cols; index2++)
          {      		  
	     if (F->data[index1][index2] == '2')
	          continue;
	     else 
	       {
		  (check ==  FALSE)? (check = TRUE):fprintf(fp," & ");   
		  		   
		  fprintf(fp,"(");
		  if (F->data[index1][index2] == '0')
		   {
		      fprintf(fp,"~");	   
		   }     
		  fprintf(fp,"%c)", F->vars[index2]); 	       
   
               }	     
          }
	 check = FALSE;
		
     }
   fprintf(fp,";\n\tend\n");

   /*All done!*/
   fprintf(fp,"endmodule"); 

   /*close the file*/
   fclose(fp); 

}/*end of verilog_file_output*/

char row_exist (CUBE *f, int curr_row_index)
{
   int index1,index2;
   char row_found = FALSE;

   for (index1 = 0; index1 < curr_row_index; index1++)
     {
	row_found = TRUE;     
	for (index2 = 0; index2 < f->cols ; index2++)
	  {
	     if (f->data[index1][index2] != f->data[curr_row_index][index2])
	       {
		  row_found = FALSE;
		  break;
	       }	       
          }
        if (row_found == TRUE)
	  {
	     break;	
	  }	
     }	     
   return row_found;	
}

void cube_copy (CUBE *a, CUBE *b)
{
   int index1,index2;

   set_functions(a,b->cols);  	 
   a->rows = b->rows;
   a->cols = b->cols;
   for(index1=0;index1<b->rows;index1++)
    {
      for(index2=0;index2<b->cols;index2++)
       {
	 a->data[index1][index2] = b->data[index1][index2];
       }
    }
   for(index1=0;index1<b->cols;index1++)
    {
       a->vars[index1] = b->vars[index1];
    }	
}	
