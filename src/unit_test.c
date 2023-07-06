#include <check.h>
#include <stdio.h>
#include <string.h>

#include "my_sscanf.h"
int size = sizeof(MY_NULL);

char mass1[100] = {'\0'}, mass2[100] = {'\0'};
char Lmass1[255] = {'\0'}, Lmass2[255] = {'\0'};
int int_test1 = 0, int_test2 = 0;

int n = 2100, n1 = 0, n2 = -21;
long int lg = 12345678912345, lg1 = -12345678912345;
short sh = 123, sh1 = -123;
float f = 21.21, f1 = -21.21;

char char_test1 = 'T', char_test2 = 'Z';
wchar_t str_test[10] = {'h', 'e', 'l', 'l', 'o'};

void free_array(char *arr1, char *arr2) {
  int Legth1 = sizeof(arr1);
  int Legth2 = sizeof(arr2);
  if (Legth1 < Legth2) Legth1 = Legth2;

  for (int i = 0; i < Legth1; i++) {
    arr1[i] = '\0';
    arr2[i] = '\0';
  }
}

START_TEST(sscanf_test_e_1) {
  float e1 = 0, e2 = 0;
  int Std_Lib = 0, Our_Lib = 0;

  Std_Lib = sscanf("123e34", "%e", &e1);
  Our_Lib = my_sscanf("123e34", "%e", &e2);
  ck_assert_msg(e1 == e2, "float not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("12e34", "%e", &e1);
  Our_Lib = my_sscanf("12e34", "%e", &e2);
  ck_assert_msg(e1 == e2, "float not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("123.345e-34", "%9e", &e1);
  Our_Lib = my_sscanf("123.345e-34", "%9e", &e2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
  ck_assert_float_eq(e1, e2);
  ck_assert_msg(e1 == e2, "float not equals");

  Std_Lib = sscanf("123.345e34", "%8e", &e1);
  Our_Lib = my_sscanf("123.345e34", "%8e", &e2);
  ck_assert_float_eq(e1, e2);
  ck_assert_msg(e1 == e2, "float not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_l_1) {
  int Std_Lib = 0, Our_Lib = 0;
  unsigned long lu1 = 0, lu2 = 0;
  long ld1 = 0, ld2 = 0;

  Std_Lib = sscanf("12345", "%lu", &lu1);
  Our_Lib = my_sscanf("12345", "%lu", &lu2);
  ck_assert_int_eq(lu1, lu2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("12345", "%ld", &ld1);
  Our_Lib = my_sscanf("12345", "%ld", &ld2);
  ck_assert_int_eq(ld1, ld2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_L_1) {
  int Std_Lib = 0, Our_Lib = 0;
  long double Lf1 = 0, Lf2 = 0;

  Std_Lib = sscanf("123.45", "%Lf", &Lf1);
  Our_Lib = my_sscanf("123.45", "%Lf", &Lf2);
  ck_assert_msg((int)Lf1 == (int)Lf2, "floats not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_u_1) {
  int Std_Lib = 0, Our_Lib = 0;
  unsigned u1 = 0, u2 = 0;

  Std_Lib = sscanf("", "%u", &u1);
  Our_Lib = my_sscanf("", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("0x12345", "%2u", &u1);
  Our_Lib = my_sscanf("0x12345", "%2u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("123.456", "%u", &u1);
  Our_Lib = my_sscanf("123.456", "%u", &u2);
  ck_assert_msg(u1 == u2, "floats not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_h_1) {
  int Std_Lib = 0, Our_Lib = 0;
  unsigned short hu1 = 0, hu2 = 0;

  Std_Lib = sscanf("12345", "%hu", &hu1);
  Our_Lib = my_sscanf("12345", "%hu", &hu2);
  ck_assert_int_eq(hu1, hu2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_s_1) {
  int Std_Lib = 0, Our_Lib = 0;
  char suite[100], s2[100];

  Std_Lib = sscanf("shrek amogus", "%*s%2s", suite);
  Our_Lib = my_sscanf("shrek amogus", "%*s%2s", s2);

  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_f_1) {
  int Std_Lib = 0, Our_Lib = 0;
  float f_1 = 0, f2 = 0;

  Std_Lib = sscanf("12e-3", "%f", &f_1);
  Our_Lib = my_sscanf("12e-3", "%f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("-123.45", "%f", &f_1);
  Our_Lib = my_sscanf("-123.45", "%f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("-12.345", "%5f", &f_1);
  Our_Lib = my_sscanf("-12.345", "%5f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("12.345", "%5f", &f_1);
  Our_Lib = my_sscanf("12.345", "%5f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_o_1) {
  int Std_Lib = 0, Our_Lib = 0;
  unsigned int o1 = 0, o2 = 0;
  char *A = "12345678";
  char *B = "12345678123456789";

  Std_Lib = sscanf(A, "%3o", &o1);
  Our_Lib = my_sscanf(A, "%3o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(B, "%9o", &o1);
  Our_Lib = my_sscanf(B, "%9o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(B, "%o", &o1);
  Our_Lib = my_sscanf(B, "%o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("123.456", "%o", &o1);
  Our_Lib = my_sscanf("123.456", "%o", &o2);
  ck_assert_uint_eq(o1, o2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_x_1) {
  int Std_Lib = 0, Our_Lib = 0;
  unsigned x1 = 5, x2 = 5;

  Std_Lib = sscanf("0x12345", "%2x", &x1);
  Our_Lib = my_sscanf("0x12345", "%2x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  x1 = 10, x2 = 10;
  Std_Lib = sscanf("AMOGUS", "%x", &x1);
  Our_Lib = my_sscanf("AMOGUS", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("amogus", "%x", &x1);
  Our_Lib = my_sscanf("amogus", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("0x123456789012345", "%x", &x1);
  Our_Lib = my_sscanf("0x123456789012345", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("0x123", "%x", &x1);
  Our_Lib = my_sscanf("0x123", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("123456", "%x", &x1);
  Our_Lib = my_sscanf("123456", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_i_1) {
  int Std_Lib = 0, Our_Lib = 0;
  int i1 = 0, i2 = 0;

  Std_Lib = sscanf("0123", "%i", &i1);
  Our_Lib = my_sscanf("0123", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("0x123", "%i", &i1);
  Our_Lib = my_sscanf("0x123", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_proc_1) {
  int Std_Lib = 0, Our_Lib = 0;
  char proc1[100] = {0}, proc2[100] = {0};

  Std_Lib = sscanf("123.456", "%%%9s", proc1);
  Our_Lib = my_sscanf("123.456", "%%%9s", proc2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_p_1) {
  int Std_Lib = 0, Our_Lib = 0;
  void *p1 = 0, *p2 = 0;

  Std_Lib = sscanf("0x123", "%4p", &p1);
  Our_Lib = my_sscanf("0x123", "%4p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("0x12345", "%p", &p1);
  Our_Lib = my_sscanf("0x12345", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("123.456", "%p", &p1);
  Our_Lib = my_sscanf("123.456", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_n_1) {
  int n_1 = 0, n_2 = 0, Std_Lib = 0, Our_Lib = 0;

  Std_Lib = sscanf("123.456", "%n", &n_1);
  Our_Lib = my_sscanf("123.456", "%n", &n_2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_d_1) {
  int Std_Lib = 0, Our_Lib = 0, d1 = 0, d2 = 0;

  Std_Lib = sscanf("123", "%002d", &d1);
  Our_Lib = my_sscanf("123", "%002d", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_all) {
  int d1 = 0, d2 = 0, i1 = 0, i2 = 0, n_1 = 0, n_2 = 0, Std_Lib = 0,
      Our_Lib = 0;
  float e1 = 0, e2 = 0, E1 = 0, E2 = 0, f_1 = 0, f2 = 0, g1 = 0, g2 = 0, G1 = 0,
        G2 = 0;
  unsigned o1 = 0, o2 = 0, u1 = 0, u2 = 0, x1 = 0, x2 = 0, X1 = 0, X2 = 0;
  void *p1 = 0, *p2 = 0;
  char suite[100], s2[100], c1 = '8', proc1[100] = {0}, proc2[100] = {0};
  short hi1 = 0, hi2 = 0, hd1 = 0, hd2 = 0;
  unsigned long lo1 = 0, lo2 = 0, lu1 = 0, lu2 = 0;
  long double Le1 = 0, Le2 = 0, LE1 = 0, LE2 = 0, Lg1 = 0, Lg2 = 0, LG1 = 0,
              LG2 = 0;
  char c2 = '9';
  Std_Lib = sscanf("123", "%d", &d1);
  Our_Lib = my_sscanf("123", "%d", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("123 amogus", "%d%9s", &d1, suite);
  Our_Lib = my_sscanf("123 amogus", "%d%9s", &d2, s2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("123 amogus q", "%d%9s%c", &d1, suite, &c1);
  Our_Lib = my_sscanf("123 amogus q", "%d%9s%c", &d2, s2, &c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("4 123 amogus q", "%i%d%9s%c", &i1, &d1, suite, &c1);
  Our_Lib = my_sscanf("4 123 amogus q", "%i%d%9s%c", &i2, &d2, s2, &c2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib =
      sscanf("4 123 amogus q 12e34", "%i%d%9s%c%e", &i1, &d1, suite, &c1, &e1);
  Our_Lib =
      my_sscanf("4 123 amogus q 12e34", "%i%d%9s%c%e", &i2, &d2, s2, &c2, &e2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("4 123 amogus q 12e34 43e21", "%i%d%9s%c%e%E", &i1, &d1,
                   suite, &c1, &e1, &E1);
  Our_Lib = my_sscanf("4 123 amogus q 12e34 43e21", "%i%d%9s%c%e%E", &i2, &d2,
                       s2, &c2, &e2, &E2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("4 123 amogus q 12e34 43e21 13.37", "%i%d%9s%c%e%E%f", &i1,
                   &d1, suite, &c1, &e1, &E1, &f_1);
  Our_Lib = my_sscanf("4 123 amogus q 12e34 43e21 13,37", "%i%d%9s%c%e%E%f",
                       &i2, &d2, s2, &c2, &e2, &E2, &f2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("4 123 amogus q 12e34 43e21 13.37 2.28", "%i%d%9s%c%e%E%f%g",
                   &i1, &d1, suite, &c1, &e1, &E1, &f_1, &g1);
  Our_Lib =
      my_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28", "%i%d%9s%c%e%E%f%g",
                 &i2, &d2, s2, &c2, &e2, &E2, &f2, &g2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228",
                   "%i%d%9s%c%e%E%f%g%G", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
                   &g1, &G1);
  Our_Lib = my_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228",
                       "%i%d%9s%c%e%E%f%g%G", &i2, &d2, s2, &c2, &e2, &E2, &f2,
                       &g2, &G2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228",
                   "%i%d%9s%c%e%E%f%g%G", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
                   &g1, &G1);
  Our_Lib = my_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228",
                       "%i%d%9s%c%e%E%f%g%G", &i2, &d2, s2, &c2, &e2, &E2, &f2,
                       &g2, &G2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101",
                   "%i%d%9s%c%e%E%f%g%G%o", &i1, &d1, suite, &c1, &e1, &E1,
                   &f_1, &g1, &G1, &o1);
  Our_Lib = my_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101",
                       "%i%d%9s%c%e%E%f%g%G%o", &i2, &d2, s2, &c2, &e2, &E2,
                       &f2, &g2, &G2, &o2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854",
                   "%i%d%9s%c%e%E%f%g%G%o%u", &i1, &d1, suite, &c1, &e1, &E1,
                   &f_1, &g1, &G1, &o1, &u1);
  Our_Lib =
      my_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854",
                 "%i%d%9s%c%e%E%f%g%G%o%u", &i2, &d2, s2, &c2, &e2, &E2, &f2,
                 &g2, &G2, &o2, &u2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib =
      sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab",
             "%i%d%9s%c%e%E%f%g%G%o%u%x", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
             &g1, &G1, &o1, &u1, &x1);
  Our_Lib =
      my_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab",
                 "%i%d%9s%c%e%E%f%g%G%o%u%x", &i2, &d2, s2, &c2, &e2, &E2, &f2,
                 &g2, &G2, &o2, &u2, &x2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(
      "4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X", &i1, &d1, suite, &c1, &e1, &E1, &f_1, &g1,
      &G1, &o1, &u1, &x1, &X1);
  Our_Lib = my_sscanf(
      "4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X", &i2, &d2, s2, &c2, &e2, &E2, &f2, &g2, &G2,
      &o2, &u2, &x2, &X2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(
      "4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p1", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
      &g1, &G1, &o1, &u1, &x1, &X1, &p1);
  Our_Lib = my_sscanf(
      "4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p2", &i2, &d2, s2, &c2, &e2, &E2, &f2, &g2,
      &G2, &o2, &u2, &x2, &X2, &p2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(
      "4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amogus is sus?",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%%", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
      &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1);
  Our_Lib = my_sscanf(
      "4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%%", &i2, &d2, s2, &c2, &e2, &E2, &f2,
      &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(
      "4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amogus is sus?",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%9s%%", &i1, &d1, suite, &c1, &e1, &E1,
      &f_1, &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1, proc1);
  Our_Lib = my_sscanf(
      "4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amogus is sus?",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%9s%%", &i2, &d2, s2, &c2, &e2, &E2, &f2,
      &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n2, proc2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = my_sscanf(
      "4 123 amogusq 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amogus is sus?",
      "%12i%4d%20s%c%3e%7E%1f%9g%5G%6o%12u%11x%2X%10p%n%21s%%", &i1, &d1, suite,
      &c1, &e1, &E1, &f_1, &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1, proc1);
  Our_Lib = my_sscanf(
      "4 123 amogusq 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amogus is sus?",
      "%12i%4d%20s%c%3e%7E%1f%9g%5G%6o%12u%11x%2X%10p%n%21s%%", &i2, &d2, s2,
      &c2, &e2, &E2, &f2, &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2, proc2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg((int)E1 == (int)E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(
      "4 123 amogusq 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amogus is sus?",
      "%*i%12i%4d%20s%c%3e%7E%*i%1f%9g%5G%6o%12u%*x%11x%2X%10p%n%21s%%", &i1,
      &d1, suite, &c1, &e1, &E1, &f_1, &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1,
      proc1);
  Our_Lib = my_sscanf(
      "4 123 amogusq 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amogus is sus?",
      "%*i%12i%4d%20s%c%3e%7E%*i%1f%9g%5G%6o%12u%*x%11x%2X%10p%n%21s%%", &i2,
      &d2, s2, &c2, &e2, &E2, &f2, &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2,
      proc2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(
      "4 123 amogusq 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amogus is sus?",
      "%*i%12hi%4hd%20s%c%3Le%7LE%*i%1f%9Lg%5LG%6lo%12lu%*x%11x%2X%10p%n%21s%%",
      &hi1, &hd1, suite, &c1, &Le1, &LE1, &f_1, &Lg1, &LG1, &lo1, &lu1, &x1,
      &X1, &p1, &n_1, proc1);
  Our_Lib = my_sscanf(
      "4 123 amogusq 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amogus is sus?",
      "%*i%12hi%4hd%20s%c%3Le%7LE%*i%1f%9Lg%5LG%6lo%12lu%*x%11x%2X%10p%n%21s%%",
      &hi2, &hd2, s2, &c2, &Le2, &LE2, &f2, &Lg2, &LG2, &lo2, &lu2, &x2, &X2,
      &p2, &n_2, proc2);
  ck_assert_int_eq(hi1, hi2);
  ck_assert_int_eq(hd1, hd2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(lo1, lo2);
  ck_assert_int_eq(lu1, lu2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_c_1) {
  char *empty_str = "";
  char c2;
  int Std_Lib, Our_Lib;
  char *stStd_Lib = " abc ";
  char c1 = '9';
  Std_Lib = sscanf(stStd_Lib, "%*c%*c%c", &c1);
  Our_Lib = my_sscanf(stStd_Lib, "%*c%*c%c", &c2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
  ck_assert_int_eq(c1, c2);

  Std_Lib = sscanf(empty_str, "%c", &c1);
  Our_Lib = my_sscanf(empty_str, "%c", &c2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_d_2) {
  char *empty_str = "";
  int nmb1 = 111, nmb2 = 111;
  int Std_Lib, Our_Lib;
  char *stOur_Lib = "  123   -123   567  32368  ";
  char wrong_stOur_Lib[] = " abc 324 ";
  Std_Lib = sscanf(stOur_Lib, "%*d%d%*d%*d", &nmb1);
  Our_Lib = my_sscanf(stOur_Lib, "%*d%d%*d%*d", &nmb2);
  ck_assert_int_eq(nmb1, nmb2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  nmb1 = 1, nmb2 = 1;
  Std_Lib = sscanf(empty_str, "%d", &nmb1);
  Our_Lib = my_sscanf(empty_str, "%d", &nmb2);
  ck_assert_int_eq(nmb1, nmb2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  nmb1 = 0, nmb2 = 0;
  Std_Lib = sscanf(wrong_stOur_Lib, "%d", &nmb1);
  Our_Lib = my_sscanf(wrong_stOur_Lib, "%d", &nmb2);
  ck_assert_int_eq(nmb1, nmb2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_i_2) {
  char *empty_str = "";
  int nmbX1 = 1, nmbX2 = 1;
  int nmbO1 = 1, nmbO2 = 1;
  int nmbD1 = 1, nmbD2 = 1;
  int Std_Lib, Our_Lib;
  char *str3 = "  0x3F5  0600 -12345 987";
  char *wrong_str3 = "  0000xFF5  ";

  Std_Lib = sscanf(str3, "%i%i%i%*i", &nmbX1, &nmbO1, &nmbD1);
  Our_Lib = my_sscanf(str3, "%i%i%i%*i", &nmbX2, &nmbO2, &nmbD2);
  ck_assert_int_eq(nmbX1, nmbX2);
  ck_assert_int_eq(nmbO1, nmbO2);
  ck_assert_int_eq(nmbD1, nmbD2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(empty_str, "%i", &nmbD1);
  Our_Lib = my_sscanf(empty_str, "%i", &nmbD2);
  ck_assert_int_eq(nmbD1, nmbD2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(wrong_str3, "%i", &nmbX1);
  Our_Lib = my_sscanf(wrong_str3, "%i", &nmbX2);
  ck_assert_uint_eq(nmbX1, nmbX2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  unsigned int octnmb1 = 1, octnmb2 = 2;

  Std_Lib = sscanf(str3, "%*x%o", &octnmb1);
  Our_Lib = my_sscanf(str3, "%*x%o", &octnmb2);
  ck_assert_uint_eq(octnmb1, octnmb2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_u_2) {
  char *empty_str = "";
  unsigned u1 = 1, u2 = 1, Std_Lib, Our_Lib;
  char *str4 = " 0    3147483647";
  char *wrong_str4 = "  Verter_Hi123456";

  Std_Lib = sscanf(str4, "%*u%u", &u1);
  Our_Lib = my_sscanf(str4, "%*u%u", &u2);
  ck_assert_uint_eq(u1, u2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(empty_str, "%u", &u1);
  Our_Lib = my_sscanf(empty_str, "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(wrong_str4, "%u", &u1);
  Our_Lib = my_sscanf(wrong_str4, "%u", &u2);
  ck_assert_uint_eq(u1, u2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_x_2) {
  unsigned u1 = 1, u2 = 2, u3 = 3, u4 = 4, Std_Lib, Our_Lib;
  char *str4 = " 123123  3147487 123 123";

  Std_Lib = sscanf(str4, "%*x%x%X%*X", &u1, &u3);
  Our_Lib = my_sscanf(str4, "%*x%x%X%*X", &u2, &u4);
  ck_assert_uint_eq(u1, u2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_double) {
  char *empty_str = "";
  int Std_Lib, Our_Lib;
  double fl1 = 1, fl2 = 2;
  double dbl1 = 1, dbl2 = 2;
  char *str5 = "  -876.214235  2145.93560734567  324.21427 ";
  char *wrong_str5 = "  Verter_Kek35634.34";

  Std_Lib = sscanf(str5, "%lf%lf%*f", &fl1, &dbl1);
  Our_Lib = my_sscanf(str5, "%lf%lf%*f", &fl2, &dbl2);

  ck_assert_double_eq_tol(fl1, fl2, 1e-6);
  ck_assert_double_eq_tol(dbl1, dbl2, 1e-6);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(empty_str, "%lf", &dbl1);
  Our_Lib = my_sscanf(empty_str, "%lf", &dbl2);

  ck_assert_double_eq_tol(dbl1, dbl2, 1e-6);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(wrong_str5, "%lf", &dbl1);
  Our_Lib = my_sscanf(wrong_str5, "%lf", &dbl2);
  ck_assert_float_eq(dbl1, dbl2);

  ck_assert_double_eq_tol(dbl1, dbl2, 1e-6);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_EeGg) {
  char *empty_str = "";
  int Std_Lib, Our_Lib;
  double e1 = -9, g1 = -9, g2 = -9;
  char *str6_u = "  0.08762147E+03  1446567457.024E-11 0E+02";

  char *wrong_str6 = "  Verter?35634E+02";
  Std_Lib = sscanf(str6_u, "%lE%lG%*e", &e1, &g1);
  double e2 = -9;

  Our_Lib = my_sscanf(str6_u, "%lE%lG%*e", &e2, &g2);
  ck_assert_double_eq_tol(e1, e2, 1e-6);
  ck_assert_double_eq_tol(g1, g2, 1e-6);
  ck_assert_int_eq(g1, g2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(empty_str, "%le", &e1);
  Our_Lib = my_sscanf(empty_str, "%le", &e2);
  ck_assert_int_eq(e1, e2);
  ck_assert_double_eq_tol(e1, e2, 1e-6);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(wrong_str6, "%lg", &g1);
  Our_Lib = my_sscanf(wrong_str6, "%lg", &g2);
  ck_assert_int_eq(g1, g2);
  ck_assert_double_eq_tol(e1, e2, 1e-6);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_s_2) {
  int Std_Lib, Our_Lib;
  char str_vaStd_Lib[30] = "", str_vaOur_Lib[30] = "";

  Std_Lib = sscanf(" this is random string", "%*s%*s%10s%*s", str_vaStd_Lib);
  Our_Lib =
      my_sscanf(" this is random string", "%*s%*s%10s%*s", str_vaOur_Lib);
  ck_assert_str_eq(str_vaStd_Lib, str_vaOur_Lib);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf("\0", "%10s", str_vaStd_Lib);
  Our_Lib = my_sscanf("\0", "%10s", str_vaOur_Lib);
  ck_assert_str_eq(str_vaStd_Lib, str_vaOur_Lib);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}

START_TEST(sscanf_test_ld) {
  char *empty_str = "";
  int Std_Lib, Our_Lib;
  long nm1 = 111, nm2 = 111;
  char *str5 = "  123   -5123123123   567  588  ";
  char wrong_str5[] = " abc 123 ";

  Std_Lib = sscanf(str5, "%*d%ld%*d%*d", &nm1);
  Our_Lib = my_sscanf(str5, "%*d%ld%*d%*d", &nm2);
  ck_assert_int_eq(nm1, nm2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(empty_str, "%ld", &nm1);
  Our_Lib = my_sscanf(empty_str, "%ld", &nm2);
  ck_assert_int_eq(nm1, nm2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(wrong_str5, " %ld", &nm1);
  Our_Lib = my_sscanf(wrong_str5, "% ld", &nm2);
  ck_assert_int_eq(nm1, nm2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_hd) {
  char *empty_str = "";
  int Std_Lib, Our_Lib;
  short nh1 = 111, nh2 = 111;
  char *str6 = "  123   -5123123123   567  588  ";
  char wrong_str6[] = " abc 123 ";

  Std_Lib = sscanf(str6, "%*d%hd%*d%*d", &nh1);
  Our_Lib = my_sscanf(str6, "%*d%hd%*d%*d", &nh2);
  ck_assert_int_eq(nh1, nh2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(empty_str, "%hd", &nh1);
  Our_Lib = my_sscanf(empty_str, "%hd", &nh2);
  ck_assert_int_eq(nh1, nh2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(wrong_str6, "%hd", &nh1);
  Our_Lib = my_sscanf(wrong_str6, "%hd", &nh2);
  ck_assert_int_eq(nh1, nh2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_lu) {
  char *empty_str = "";
  int Std_Lib, Our_Lib;
  unsigned long nu1 = 111, nu2 = 111;
  char *str7 = "  123   5123123123   567  588  ";
  char wrong_str7[] = " abc 123 ";

  Std_Lib = sscanf(str7, "%*d%lu%*d%*d", &nu1);
  Our_Lib = my_sscanf(str7, "%*d%lu%*d%*d", &nu2);
  ck_assert_int_eq(nu1, nu2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(empty_str, "%lu", &nu1);
  Our_Lib = my_sscanf(empty_str, "%lu", &nu2);
  ck_assert_int_eq(nu1, nu2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(wrong_str7, "%lu", &nu1);
  Our_Lib = my_sscanf(wrong_str7, "%lu", &nu2);
  ck_assert_int_eq(nu1, nu2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_hu) {
  char *empty_str = "";
  int Std_Lib, Our_Lib;
  unsigned short nuh1 = 111, nuh2 = 111;
  char *str5 = "  123   15000   567  588  ";
  char wrong_str5[] = " abc 123 ";

  Std_Lib = sscanf(str5, "%*d%hu%*d%*d", &nuh1);
  Our_Lib = my_sscanf(str5, "%*d%hu%*d%*d", &nuh2);
  ck_assert_int_eq(nuh1, nuh2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(empty_str, "%hu", &nuh1);
  Our_Lib = my_sscanf(empty_str, "%hu", &nuh2);
  ck_assert_int_eq(nuh1, nuh2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(wrong_str5, "%hu", &nuh1);
  Our_Lib = my_sscanf(wrong_str5, "%hu", &nuh2);
  ck_assert_int_eq(nuh1, nuh2);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

START_TEST(sscanf_test_ptr) {
  char *empty_str = "";
  int Std_Lib, Our_Lib;
  unsigned long p1 = 111, p2 = 111;
  unsigned long *ptStd_Lib = &p1;
  unsigned long *ptStd_Lib1 = &p1;
  unsigned long *ptOur_Lib = &p2;
  unsigned long *ptOur_Lib2 = &p2;
  char *str8 = "  123   5123123123   0x567  588  ";
  char wrong_str8[] = " abc 123 ";

  Std_Lib = sscanf(str8, "%*d%p%p%*p", &ptStd_Lib, &ptStd_Lib1);
  Our_Lib = my_sscanf(str8, "%*d%p%p%*p", &ptOur_Lib, &ptOur_Lib2);
  ck_assert_ptr_eq(ptStd_Lib, ptOur_Lib);
  ck_assert_ptr_eq(ptStd_Lib1, ptOur_Lib2);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(empty_str, "%p", &ptStd_Lib);
  Our_Lib = my_sscanf(empty_str, "%p", &ptOur_Lib);
  ck_assert_ptr_eq(ptStd_Lib, ptOur_Lib);
  ck_assert_int_eq(Std_Lib, Our_Lib);

  Std_Lib = sscanf(wrong_str8, "%p", &ptStd_Lib);
  Our_Lib = my_sscanf(wrong_str8, "%p", &ptOur_Lib);
  ck_assert_ptr_eq(ptStd_Lib, ptOur_Lib);
  ck_assert_int_eq(Std_Lib, Our_Lib);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("S21_Debuger");
  SRunner *srunner = srunner_create(suite);

  TCase *my_sscanf_e = tcase_create("Sscanf_e");
  suite_add_tcase(suite, my_sscanf_e);
  tcase_add_test(my_sscanf_e, sscanf_test_e_1);

  TCase *my_sscanf_EeGg = tcase_create("Sscanf_EeGg");
  suite_add_tcase(suite, my_sscanf_EeGg);
  tcase_add_test(my_sscanf_EeGg, sscanf_test_EeGg);

  TCase *my_sscanf_l_1 = tcase_create("Sscanf_l");
  suite_add_tcase(suite, my_sscanf_l_1);
  tcase_add_test(my_sscanf_l_1, sscanf_test_l_1);

  TCase *my_sscanf_L_1 = tcase_create("Sscanf_L");
  suite_add_tcase(suite, my_sscanf_L_1);
  tcase_add_test(my_sscanf_L_1, sscanf_test_L_1);

  TCase *my_sscanf_ld = tcase_create("Sscanf_ld");
  suite_add_tcase(suite, my_sscanf_ld);
  tcase_add_test(my_sscanf_ld, sscanf_test_ld);

  TCase *my_sscanf_hd = tcase_create("Sscanf_hd");
  suite_add_tcase(suite, my_sscanf_hd);
  tcase_add_test(my_sscanf_hd, sscanf_test_hd);

  TCase *my_sscanf_lu = tcase_create("Sscanf_lu");
  suite_add_tcase(suite, my_sscanf_lu);
  tcase_add_test(my_sscanf_lu, sscanf_test_lu);

  TCase *my_sscanf_hu = tcase_create("Sscanf_hu");
  suite_add_tcase(suite, my_sscanf_hu);
  tcase_add_test(my_sscanf_hu, sscanf_test_hu);

  TCase *my_sscanf_h_1 = tcase_create("Sscanf_h");
  suite_add_tcase(suite, my_sscanf_h_1);
  tcase_add_test(my_sscanf_h_1, sscanf_test_h_1);

  TCase *my_sscanf_d_1 = tcase_create("Sscanf_d");
  suite_add_tcase(suite, my_sscanf_d_1);
  tcase_add_test(my_sscanf_d_1, sscanf_test_d_1);

  TCase *my_sscanf_d_2 = tcase_create("Sscanf_d");
  suite_add_tcase(suite, my_sscanf_d_2);
  tcase_add_test(my_sscanf_d_2, sscanf_test_d_2);

  TCase *my_sscanf_u_1 = tcase_create("Sscanf_u");
  suite_add_tcase(suite, my_sscanf_u_1);
  tcase_add_test(my_sscanf_u_1, sscanf_test_u_1);

  TCase *my_sscanf_u_2 = tcase_create("Sscanf_u");
  suite_add_tcase(suite, my_sscanf_u_2);
  tcase_add_test(my_sscanf_u_2, sscanf_test_u_2);

  TCase *my_sscanf_ptr = tcase_create("Sscanf_ptr");
  suite_add_tcase(suite, my_sscanf_ptr);
  tcase_add_test(my_sscanf_ptr, sscanf_test_ptr);

  TCase *my_sscanf_proc = tcase_create("Sscanf_proc");
  suite_add_tcase(suite, my_sscanf_proc);
  tcase_add_test(my_sscanf_proc, sscanf_test_proc_1);

  TCase *my_sscanf_p_1 = tcase_create("my_sscanf_p");
  suite_add_tcase(suite, my_sscanf_p_1);
  tcase_add_test(my_sscanf_p_1, sscanf_test_p_1);

  TCase *my_sscanf_s_1 = tcase_create("Sscanf_s");
  suite_add_tcase(suite, my_sscanf_s_1);
  tcase_add_test(my_sscanf_s_1, sscanf_test_s_1);

  TCase *my_sscanf_s_2 = tcase_create("Sscanf_s");
  suite_add_tcase(suite, my_sscanf_s_2);
  tcase_add_test(my_sscanf_s_2, sscanf_test_s_2);

  TCase *my_sscanf_f_1 = tcase_create("Sscanf_f");
  suite_add_tcase(suite, my_sscanf_f_1);
  tcase_add_test(my_sscanf_f_1, sscanf_test_f_1);

  TCase *my_sscanf_o_1 = tcase_create("Sscanf_o");
  suite_add_tcase(suite, my_sscanf_o_1);
  tcase_add_test(my_sscanf_o_1, sscanf_test_o_1);

  TCase *my_sscanf_x_1 = tcase_create("Sscanf_x");
  suite_add_tcase(suite, my_sscanf_x_1);
  tcase_add_test(my_sscanf_x_1, sscanf_test_x_1);

  TCase *my_sscanf_x_2 = tcase_create("Sscanf_x");
  suite_add_tcase(suite, my_sscanf_x_2);
  tcase_add_test(my_sscanf_x_2, sscanf_test_x_2);

  TCase *my_sscanf_i_1 = tcase_create("Sscanf_i");
  suite_add_tcase(suite, my_sscanf_i_1);
  tcase_add_test(my_sscanf_i_1, sscanf_test_i_1);

  TCase *my_sscanf_i_2 = tcase_create("Sscanf_i");
  suite_add_tcase(suite, my_sscanf_i_2);
  tcase_add_test(my_sscanf_i_2, sscanf_test_i_2);

  TCase *my_sscanf_c_1 = tcase_create("Sscanf_c");
  suite_add_tcase(suite, my_sscanf_c_1);
  tcase_add_test(my_sscanf_c_1, sscanf_test_c_1);

  TCase *my_sscanf_n_1 = tcase_create("Sscanf_n");
  suite_add_tcase(suite, my_sscanf_n_1);
  tcase_add_test(my_sscanf_n_1, sscanf_test_n_1);

  TCase *my_sscanf_test_double = tcase_create("Sscanf_double");
  suite_add_tcase(suite, my_sscanf_test_double);
  tcase_add_test(my_sscanf_test_double, sscanf_test_double);

  TCase *my_sscanf_all = tcase_create("Sscanf_all");
  suite_add_tcase(suite, my_sscanf_all);
  tcase_add_test(my_sscanf_all, sscanf_test_all);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
