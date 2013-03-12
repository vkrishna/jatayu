/*
File Name: main.c
Project 3 ECE574A
Author: Venkata Krishna Nimmagadda
Email IDs: vkn@email.arizona.edu  vtbhat@email.arizona.edu
University of Arizona, Tucson
Description: This file contains the code for main function
*/

#include<stdio.h>
#include<stdlib.h>
#include "../include/main.h"

/*Global*/
char opvar; /*holds the output function variable*/


int main(int argc, char **argv)
{
  int index1,index2;
  CUBE F,R,D;
  CUBE W; /*this will store the original ON-set function*/
  CUBE V; /*this will store the espresso expand output*/

  /*in case of improper invocation*/
  if(argc != 4)
    {
      printf("Please check the usage:\n");
      printf("Usage: ./logic_min <input_file> <file_flag> <output_file\n");
      printf("Example ./logic_min input_file -e\n");
      exit(0);
    }
  
  /*parse the input file and build up the ON-set,
   *OFF-set and dont-care set*/ 
  read_inputs_from_file(&F,&R,&D,argv[1]);
    
  /*preserve org onset function*/ 
  cube_copy(&W, &F);

  /*call the expand function*/
  expand(&F,&R); 

  /*printing party*/
  printf("\nJust after Espresso Expand and before logic_min\n");
  printf("\n**********************************************\n");
      printf("\nThe ON set is %d %d\n",F.rows,F.cols);
      print_cube(&F);
      printf("\n");
      printf("\nThe OFF set is %d %d\n",R.rows,R.cols);
      print_cube(&R);
      printf("\n");
      printf("\nThe DONT CARE set is %d %d\n",D.rows,D.cols);
      print_cube(&D);
      printf("\n");
  printf("\n**********************************************\n");

  /*preserve the espresso expand output*/ 
  cube_copy(&V, &F);

  /*logic minimization routine*/
  logic_min(&F);

  /*parse the command line argument to check what type of
   * output file needs to be generated*/
  if (strcmp(argv[2],"-e") == 0)
   {
      text_file_output(&W, &V, &R, &D,argv[3], ESPEXP_TEXT_OUTPUT);
   }
  else if (strcmp(argv[2],"-t") == 0)
   {
      text_file_output(&W, &F, &R, &D,argv[3], OPT_TEXT_OUTPUT);
   }
  else if (strcmp(argv[2],"-v") == 0)
   {
      verilog_file_output(&F, argv[3]);
   }
  else
   {
      printf("Invalid flag.\n");	   
   }  
}/*end of main*/

