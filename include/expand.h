/*
** expand.h
** 
** Made by krishna
** Login   <krishna@krishna-laptop>
** 
** Started on  Tue Nov 17 03:25:14 2009 krishna
** Last update Tue Nov 17 03:25:14 2009 krishna
*/

#ifndef   	EXPAND_H_
# define   	EXPAND_H_

int expand(CUBE *F, CUBE *R);
int remove_duplicate_rows(CUBE *F);
int remove_row(CUBE *F, int row);
int compare (char *str1, char *str2, int num);
int expand1(char *c, CUBE *R, CUBE *F);
signed int essentials(CUBE *B);
int elim1(CUBE *B, CUBE *C, signed int col);
signed int mfc(CUBE *C);
signed int end_game(CUBE *B, CUBE *C);
signed int inessentials(CUBE *B);
int elim2(CUBE *B, CUBE *C,signed int J);
int minlow(SET *L, CUBE *B);
int print_cube(CUBE *f);
int free_set(SET *s);
int free_cube(CUBE *f);



#endif 	    /* !EXPAND_H_ */
