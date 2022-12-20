#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_

#define s21_NULL (void *)0

typedef unsigned long long s21_size_t;

typedef struct {
  int isMinus;
  long long int width;
  long long int d;
  long double ld;
  s21_size_t strLen;
  s21_size_t formatLen;
  s21_size_t strIndex;
  int noRead;
  int isSpec;
  int isLong;
  int isShort;
  int isLongDouble;
  int skipWrite;
  int res;
  int haveSpec;
  int go;
  int haveSpace;
  int specCount;
  char *lineS;
  const char *str;
  const char *format;

} flags;

int s21_sscanf(const char *str, const char *format, ...);

int checkEmpty(const char *str);
void writeDI(flags *f, va_list *list);
void writeUOX(flags *f, va_list *list);
void writeAEFG(flags *f, va_list *list);
void writeP(flags *f, va_list *list);
void writeCS(flags *f, char c, va_list *list);
void parseAndRead(flags *f, va_list *list, const char *str, const char *format);
void writeSpec(flags *f, va_list *list, char spec);
void writeN(flags *f, va_list *list);
long long int readHexOctDec(flags *f, const char *str);
long long octToLL(flags *f, const char *str);
long long hexToLL(flags *f, const char *str);
void readE(flags *f, const char *str, int *eCount, int *countRead, int *good,
           int *isNeg, unsigned long int *power);
int isNanOrInf(flags *f, const char *str, long double *lf, int *good_to_go);
long double readFloat(const char *str, flags *f);
char *readS(const char *str, flags *f);
char *readC(const char *str, flags *f);
void readPercent(const char *str, flags *f);
long long int readDec(const char *str, flags *f);
void readSpec(flags *f, const char *str, char spec);
int compareLetter(char need, char check);
int charToDigit(char c);
int isDigit(char c);
void readInfo(flags *f, const char *format, s21_size_t *i);
void addEl(char **line, s21_size_t *size, char add, flags *f);
int hexToDigit(char c);
void readSign(flags *f, const char *str, char c);

#endif  // SRC_S21_SSCANF_H_
