#include "smartcalc.h"

double base_calculation(char str[], double arg, int *er) {
  double result = 0;
  if (strlen(str) <= 255) {
    char *str_ver = verification(str, er);
    if (*er == 0) {
      char str_rpn[500];
      writing_empty_string(str_rpn, 500);
      *er = conversion_to_rpn(str_ver, str_rpn);
      if (*er == 0) {
        result = calculation(str_rpn, arg, er);
      }
    }
    free(str_ver);
  } else {
    *er = 1;
  }

  return result;
}

double calculation(char *s, double arg_x, int *err) {
  int count_rpn = number_lines(s);
  char arr_rpn[count_rpn][20];
  char result_calc[count_rpn][20];
  for (int i = 0; i < count_rpn; i++) {
    writing_empty_string(arr_rpn[i], 20);
    writing_empty_string(result_calc[i], 20);
  }
  rpn_string_to_array(arr_rpn, s, arg_x, count_rpn);

  int i = 0;
  int j = 0;
  double f = 0;

  while (i < count_rpn && *err == 0) {
    if (check_for_token(arr_rpn[i][0]) == 1 ||
        check_for_token(arr_rpn[i][1]) == 1) {
      strcpy(result_calc[j], arr_rpn[i]);
      j++;
    } else if (check_for_function(arr_rpn[i][0]) == 1) {
      j--;
      if (check_for_token(result_calc[j][0]) == 1 || result_calc[j][0] == '-') {
        f = function_calculation(result_calc[j], arr_rpn[i][0], err);
        sprintf(result_calc[j], "%0.14lf", f);
        j++;
      } else {
        *err = 1;
      }
    } else if (check_for_operand(arr_rpn[i][0]) == 1 &&
               check_for_token(arr_rpn[i][1]) != 1) {
      j--;
      if ((check_for_token(result_calc[j][0]) == 1 ||
           check_for_token(result_calc[j][1]) == 1) &&
          (check_for_token(result_calc[j - 1][0]) == 1 ||
           check_for_token(result_calc[j - 1][1]) == 1)) {
        f = operand_calculation(result_calc[j - 1], result_calc[j],
                                arr_rpn[i][0], err);
        j--;
        sprintf(result_calc[j], "%0.14lf", f);
        j++;
      } else {
        j += 2;
      }
    } else {
      *err = 1;
    }
    i++;
  }
  f = achtof(result_calc[0]);

  return f;
}

double function_calculation(char *s, char f, int *er) {
  double y = 0;
  double x = achtof(s);

  /*if (f == 's' || f == 'c' || f == 't') {
    x = PI * x / 180;
  }*/

  if (f == 't' && sin(x) == 1) {
    *er = 2;
  } else if ((f == 'l' || f == 'g') && x <= 0) {
    *er = 3;
  } else if (f == 'q' && x < 0) {
    *er = 4;
  }
  if (*er == 0) {
    switch (f) {
      case 's':
        y = sin(x);
        break;
      case 'c':
        y = cos(x);
        break;
      case 't':
        y = tan(x);
        break;
      case 'o':
        y = acos(x);
        break;
      case 'i':
        y = asin(x);
        break;
      case 'a':
        y = atan(x);
        break;
      case 'l':
        y = log(x);
        break;
      case 'g':
        y = log10(x);
        break;
      case 'q':
        y = sqrt(x);
        break;
      case 'b':
        y = fabs(x);
        break;
    }
  }
  return y;
}

double operand_calculation(char *s0, char *s1, char op, int *er) {
  double y = 0;
  double x0 = achtof(s0);
  double x1 = achtof(s1);

  if ((op == '/' || op == 'm') && x1 == 0) {
    *er = 2;
  } else {
    switch (op) {
      case '+':
        y = x0 + x1;
        break;
      case '-':
        y = x0 - x1;
        break;
      case '*':
        y = x0 * x1;
        break;
      case '/':
        y = x0 / x1;
        break;
      case 'm':
        y = fmod(x0, x1);
        break;
      case '^':
        y = pow(x0, x1);
        break;
    }
  }

  return y;
}
