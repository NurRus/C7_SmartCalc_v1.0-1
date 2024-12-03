#include "smartcalc.h"

int conversion_to_rpn(char *s, char s_rpn[]) {
  int error = 0;
  char stack[100] = {'\0'};
  writing_empty_string(stack, 100);
  int i = 0;
  int fl_num = 0;
  while (s[i] != '\0' && error == 0) {
    if (s[i] == '(' || check_for_function(s[i]) == 1) {
      stack[strlen(stack)] = s[i];
      stack[strlen(stack) + 1] = '\0';
    } else if (check_for_token(s[i]) > 0) {
      action_if_token(&fl_num, s[i], s[i + 1], s_rpn);
    } else if (s[i] == ')') {
      action_if_bracket(stack, &error, s_rpn);
    } else if (check_for_operand(s[i]) == 1) {
      action_if_operand(stack, s_rpn, s[i]);
    } else {
      error = 1;
    }
    i++;
  }
  clear_stack(s_rpn, stack);

  return error;
}

void action_if_token(int *fn, char simv1, char simv2, char *str) {
  if (*fn == 0) {
    str[strlen(str)] = '\'';
  }
  str[strlen(str)] = simv1;
  *fn = 1;
  if (check_for_token(simv2) == 0) {
    str[strlen(str)] = '\'';
    *fn = 0;
  }
}

void action_if_bracket(char *st, int *er, char *str) {
  int k = strlen(st);
  while (k >= 0 && st[k] != '(') {
    str[strlen(str)] = st[k];
    st[k] = '\0';
    k--;
  }
  if (k == 0 && st[k] != '(') {
    *er = 1;
  } else if (k > 0 && check_for_function(st[k - 1]) == 1) {
    str[strlen(str)] = st[k - 1];
    st[k - 1] = '\0';
  }
  st[k] = '\0';
}

void action_if_operand(char *st, char *str, char simv) {
  int n = strlen(st);
  if (n == 0 || (n > 0 && st[n - 1] == '(')) {
    st[n] = simv;
  } else if (n > 0 && check_for_stack(simv, st[n - 1]) == 1) {
    str[strlen(str)] = st[n - 1];
    st[n - 1] = simv;
  } else if (n > 0) {
    st[n] = simv;
  }
}
