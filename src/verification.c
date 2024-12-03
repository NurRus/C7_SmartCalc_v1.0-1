#include "smartcalc.h"

char *verification(char expr[], int *er) {
  int error = 0;
  char *result_ver = NULL;
  replace_name_to_simvol(expr);
  error = check_for_error(expr);
  if (error == 0) {
    result_ver = two_transformation(expr);
  }
  *er = error;

  return result_ver;
}

int check_for_error(char *s) {
  int result = 0;
  int i = 0;
  int count = 0;
  if (check_for_operand(s[0] == 1) &&
      (s[0] != '-' || s[0] != '+')) {  // проверка на операнд в начале строки
    result = 1;
  }
  while (s[i] != '\0' && result == 0) {
    if (s[i] ==
        '(') {  // проверка на кол-во открывающихся и закрывающихся скобок
      count++;
      if (s[i + 1] == ')') {
        result = 1;
      }
    }
    if (s[i] == ')') {
      count--;
      if (s[i + 1] == '(') {
        result = 1;
      }
    }
    if (check_for_function(s[i]) == 1 &&
        s[i + 1] != '(') {  // после ф-ции д.б. открывающаяся скобка
      result = 1;
    } else if (check_for_token(s[i]) == 1 && s[i + 1] != ',' &&
               s[i + 1] != '.' &&  // после цифры д.б. ',' или '.',
               check_for_token(s[i + 1]) != 1 &&
               s[i + 1] != '\0' &&  // либо цифра, либо '\0',
               check_for_operand(s[i + 1]) != 1 &&
               s[i + 1] != ')') {  // либо операнд, либо ')'
      result = 1;
    } else if (s[i] == 'x' && s[i + 1] != ')'  // После 'x' д.б. либо ')'
               && check_for_operand(s[i + 1]) != 1 &&
               s[i + 1] != '\0') {  // либо операнд, либо '\0'
      result = 1;
    } else if ((s[i] == ',' || s[i] == '.') &&
               check_for_token(s[i + 1]) !=
                   1) {  // после ',' или '.' д.б. цифра
      result = 1;
    } else if (check_for_operand(s[i]) == 1 &&
               s[i + 1] != '(' &&  // после операнда д.б. '(',
               s[i + 1] != 'x' &&
               check_for_function(s[i + 1]) != 1 &&  // либо 'x', либо функция,
               check_for_token(s[i + 1]) != 1) {  // либо цифра
      result = 1;
    } else if (s[i] == ')' &&
               check_for_operand(s[i + 1]) == 0 &&  // после ')' д.б.
               s[i + 1] != '\0' &&
               s[i + 1] != ')') {  // либо ')', либо операнд, либо '\0'
      result = 1;
    }
    i++;
  }
  if (count != 0) {
    result = 1;
  }

  return result;
}

char *two_transformation(char *s) {
  char *new_str = (char *)calloc(500, sizeof(char));
  writing_empty_string(new_str, 500);
  int i = 0;
  int j = 0;
  while (s[i] != '\0') {
    if ((s[i] == '+' || s[i] == '-') && (i == 0 || s[i - 1] == '(')) {
      if (check_for_token(s[i + 1]) > 0) {
        new_str[j] = '(';
        j++;
      }
      new_str[j] = '0';
      j++;
      new_str[j] = s[i];
      j++;
      while (check_for_token(s[i + 1]) > 0) {
        i++;
        new_str[j] = s[i];
        j++;
      }
      if (check_for_token(new_str[j - 1]) > 0) {
        new_str[j] = ')';
        j++;
      }
    } else {
      new_str[j] = s[i];
      j++;
    }
    i++;
  }

  return new_str;
}
