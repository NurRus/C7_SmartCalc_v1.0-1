#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double base_calculation(char str[], double arg, int *er);
char *verification(char expr[], int *er);
int check_for_error(char *s);
int check_for_function(char simv);
int check_for_operand(char simv);
int check_for_token(char simv);
char *two_transformation(char *s);
void replace_name_to_simvol(char *s);
int conversion_to_rpn(char *s, char s_rpn[]);
void action_if_token(int *nf, char simv1, char simv2, char *str);
int check_for_stack(char simv, char st);
void action_if_bracket(char *st, int *er, char *str);
void action_if_operand(char *st, char *str, char simv);
double calculation(char *s, double arg_x, int *err);
double function_calculation(char *s, char f, int *er);
double operand_calculation(char *s0, char *s1, char op, int *er);
int check_for_number(char simv);
void writing_empty_string(char *str, int n);
void rpn_string_to_array(char (*s_arr)[20], char *s, double x, int n);
int number_lines(char *s);
void clear_stack(char *str, char *st);
double achtof(char *s);

#define PI 3.141592653589793

#endif