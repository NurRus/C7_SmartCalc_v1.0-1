#include "smartcalc.h"

struct procedure {
  char op;
  int pr;
  char name[5];
} oper[] = {{'s', 3, "sin"},  {'c', 3, "cos"},  {'t', 3, "tan"},
            {'o', 3, "acos"}, {'i', 3, "asin"}, {'a', 3, "atan"},
            {'q', 3, "sqrt"}, {'l', 3, "ln"},   {'g', 3, "log"},
            {'b', 3, "abs"},  {'n', 3, "\0"},   {'m', 1, "mod"},
            {'^', 2, "\0"},   {'*', 1, "\0"},   {'/', 1, "\0"},
            {'+', 0, "\0"},   {'-', 0, "\0"}};

void replace_name_to_simvol(char *s) {
  char bufer[20] = {'\0'};
  int i = 0;
  int j;
  int k;
  int flag;
  while (s[i] != '\0') {
    j = 0;
    flag = -1;
    k = i;
    writing_empty_string(bufer, 20);
    while (s[k] >= 97 && s[k] <= 122 && s[k] != 'x') {
      bufer[j] = s[k];
      j++;
      k++;
    }
    if (strlen(bufer) > 0) {
      k = 0;
      while (k < 12 && flag < 0) {
        if (strcmp(bufer, oper[k].name) == 0) {
          flag = k;
        }
        k++;
      }
    }
    if (flag >= 0) {
      s[i] = oper[flag].op;
      j = i + strlen(bufer);
      k = i + 1;
      while (s[j] != '\0') {
        s[k] = s[j];
        j++;
        k++;
      }
      s[k] = '\0';
    }
    i++;
  }
}

int check_for_function(char simv) {
  int result = 0;
  int i = 0;
  while (i < 11 && result == 0) {
    if (simv == oper[i].op) {
      result = 1;
    }
    i++;
  }
  return result;
}

int check_for_operand(char simv) {
  int result = 0;
  int i = 11;
  while (i < 17 && result == 0) {
    if (simv == oper[i].op) {
      result = 1;
    }
    i++;
  }
  return result;
}

int check_for_token(char simv) {
  int result = 0;
  if (simv <= 57 && simv >= 48) {
    result = 1;
  }
  if (simv == 'x') {
    result = 2;
  }
  if (simv == ',' || simv == '.') {
    result = 3;
  }
  return result;
}

int check_for_stack(char simv, char st) {
  int result = 0;
  int p_simv = 0;
  int p_st = 0;
  for (int i = 0; i < 17; i++) {
    if (simv == oper[i].op) {
      p_simv = oper[i].pr;
    }
    if (st == oper[i].op) {
      p_st = oper[i].pr;
    }
  }
  if (p_st >= p_simv) {
    result = 1;
  }
  return result;
}

void rpn_string_to_array(char (*s_arr)[20], char *s, double x, int n) {
  int j = 0;
  int k = 0;

  for (int i = 0; i < n; i++) {
    if (s[k] == '\'') {
      k++;
      while (s[k] != '\'' && s[k] != '\0') {
        if (s[k] == 'x') {
          sprintf(s_arr[i], "%0.14lf", x);
        } else {
          s_arr[i][j] = s[k];
        }
        j++;
        k++;
      }
    } else {
      s_arr[i][j] = s[k];
    }
    j = 0;
    k++;
  }
}

int number_lines(char *s) {
  int result = 0;
  int i = 0;

  while (s[i] != '\0') {
    if (s[i] == '\'') {
      i++;
      while (s[i] != '\'' && s[i] != '\0') {
        i++;
      }
    }
    result++;
    i++;
  }

  return result;
}

void writing_empty_string(char *str, int n) {
  for (int i = 0; i < n; i++) {
    str[i] = '\0';
  }
}

void clear_stack(char *str, char *st) {
  int i = strlen(st);
  int j = strlen(str);
  while (i > 0) {
    str[j] = st[i - 1];
    str[j + 1] = '\0';
    i--;
    j++;
  }
}

double achtof(char *s) {
  int share = 0;
  int sign = 1;
  double result = 0;
  int i = 0;
  while (s[i] != '\0') {
    if (s[i] == '-') {
      sign = -1;
    }
    if (share > 0) {
      result = result * 10 + s[i] - '0';
      share++;
    } else if (s[i] == '.' || s[i] == ',') {
      share++;
    } else if (s[i] != '-') {
      result = result * 10 + s[i] - '0';
    }
    i++;
  }
  if (share == 0) {
    share = 1;
  }
  result = result * sign / (pow(10, share - 1));

  return result;
}
