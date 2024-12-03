#include <check.h>

#include "smartcalc.h"

START_TEST(calc_1) {
  char str[256] = "-256+256*1.34-234.52/42.765";
  int error = 0;
  double correct = -256 + 256 * 1.34 - 234.52 / 42.765;

  double y = base_calculation(str, 0, &error);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_2) {
  char str[256] = "(1.213/sqrt(6986.32))^3.5";
  int error = 0;
  double correct = pow(1.213 / sqrt(6986.32), 3.5);

  double y = base_calculation(str, 0, &error);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_3) {
  int error = 0;
  char str[256] = "1/sin(3)+cos(4)/tan(2.45)";

  double y = base_calculation(str, 0, &error);
  double correct = 1 / sin(3) + cos(4) / tan(2.45);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_4) {
  int error = 0;
  char str[256] = "ln(321.423)/log(3.78)";

  double y = base_calculation(str, 0, &error);
  double correct = log(321.423) / log10(3.78);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_5) {
  int error = 0;
  char str[256] = "1.4*asin(0.453)/acos(0.9876)-atan(2)";

  double y = base_calculation(str, 0, &error);
  double correct = 1.4 * asin(0.453) / acos(0.9876) - atan(2);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_6) {
  int error = 0;
  char str[256] = "44mod3+43.4mod3.7";

  double y = base_calculation(str, 0, &error);
  double correct = 44 % 3 + fmod(43.4, 3.7);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_7) {
  int error = 0;
  double x = 1.5;
  char str[256] = "sin(sqrt((x*sin(x)+cos(x))^3.5))";

  double y = base_calculation(str, x, &error);
  double correct = sin(sqrt(pow(x * sin(x) + cos(x), 3.5)));
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_8) {
  int error = 0;
  double x = 1.5;
  char str[256] = "sinsqrt((x*sin(x)+cos(x))^3.5)";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_9) {
  int error = 0;
  double x = 1.5;
  char str[256] = "-2+3*x/";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_10) {
  int error = 0;
  double x = 1.5;
  char str[256] = "-2+3*x/cos4";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_11) {
  int error = 0;
  double x = 1.5;
  char str[256] = "(-2+)3*x/cos4";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_12) {
  int error = 0;
  double x = 0;
  char str[256] = "1/sin(x)";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 2);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_13) {
  int error = 0;
  double x = -1;
  char str[256] = "sqrt(x)";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 4);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_14) {
  int error = 0;
  double x = 0;
  char str[256] = "ln(x)";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 3);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_15) {
  int error = 0;
  double x = 1.5;
  char str[256] = "/+3";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_16) {
  int error = 0;
  double x = 1.5;
  char str[256] = "3*x/cos()";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_17) {
  int error = 0;
  double x = 1.5;
  char str[256] = "3*x/cos(x)(-2)";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_18) {
  int error = 0;
  double x = 1.5;
  char str[256] = "3sin(x)*x/cos(x)";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_19) {
  int error = 0;
  char str[260] =
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1";
  double y = base_calculation(str, 0, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_20) {
  int error = 0;
  double x = -1.5;
  char str[256] = "3*sin(abs(x))*x/cos(abs(x))";
  double y = base_calculation(str, x, &error);
  double correct = 3 * sin(fabs(x)) * x / cos(fabs(x));
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_21) {
  int error = 0;
  double x = -1.5;
  char str[256] = "sin(cos(tan(x)))";
  double y = base_calculation(str, x, &error);
  double correct = sin(cos(tan(x)));
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_22) {
  int error = 0;
  double x = PI / 2;
  char str[256] = "tan(x)";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 2);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_23) {
  int error = 0;
  double x = 1.5;
  char str[256] = "3*x1";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

START_TEST(calc_24) {
  int error = 0;
  double x = 1.5;
  char str[256] = "3.x+5";
  double y = base_calculation(str, x, &error);
  double correct = y;
  ck_assert_int_eq(error, 1);
  ck_assert_double_eq_tol(y, correct, 1e-7);
}
END_TEST

Suite *s21_calculator_test(void) {
  Suite *suite = suite_create("s21_calculator");
  TCase *tCase = tcase_create("s21_calculator");

  tcase_add_test(tCase, calc_1);
  tcase_add_test(tCase, calc_2);
  tcase_add_test(tCase, calc_3);
  tcase_add_test(tCase, calc_4);
  tcase_add_test(tCase, calc_5);
  tcase_add_test(tCase, calc_6);
  tcase_add_test(tCase, calc_7);
  tcase_add_test(tCase, calc_8);
  tcase_add_test(tCase, calc_9);
  tcase_add_test(tCase, calc_10);
  tcase_add_test(tCase, calc_11);
  tcase_add_test(tCase, calc_12);
  tcase_add_test(tCase, calc_13);
  tcase_add_test(tCase, calc_14);
  tcase_add_test(tCase, calc_15);
  tcase_add_test(tCase, calc_16);
  tcase_add_test(tCase, calc_17);
  tcase_add_test(tCase, calc_18);
  tcase_add_test(tCase, calc_19);
  tcase_add_test(tCase, calc_20);
  tcase_add_test(tCase, calc_21);
  tcase_add_test(tCase, calc_22);
  tcase_add_test(tCase, calc_23);
  tcase_add_test(tCase, calc_24);

  suite_add_tcase(suite, tCase);

  return suite;
}

int main() {
  Suite *suite = s21_calculator_test();
  SRunner *sRunner = srunner_create(suite);
  srunner_set_fork_status(sRunner, CK_NOFORK);
  srunner_run_all(sRunner, CK_VERBOSE);
  int total_tests = srunner_ntests_run(sRunner);
  int failed_tests = srunner_ntests_failed(sRunner);
  srunner_free(sRunner);
  printf("\nВсего тестов: %d\n", total_tests);
  printf("Провалено тестов: %d\n", failed_tests);

  return (failed_tests == 0) ? 0 : 1;
}