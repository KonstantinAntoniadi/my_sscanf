#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list list;
  va_start(list, format);
  flags f = {0};
  f.go = 1;
  f.res = -1;
  if (str != s21_NULL && format != s21_NULL) {
    f.formatLen = strlen(format);
    f.strLen = strlen(str);
    parseAndRead(&f, &list, str, format);
  }
  va_end(list);
  return f.res;
}

void parseAndRead(flags *f, va_list *list, const char *str,
                  const char *format) {
  f->isSpec = 1;
  f->lineS = s21_NULL;
  f->specCount = 0;
  f->res = 0;
  for (s21_size_t i = 0; i < f->formatLen && f->isSpec && f->go; i++) {
    f->isLong = 0;
    f->isShort = 0;
    f->isLongDouble = 0;
    if (format[i] == ' ' || format[i] == '\t' || format[i] == '\n') {
      f->haveSpace++;
    } else if (format[i] != '%') {
      while (f->haveSpace && f->strIndex < f->strLen &&
             (str[f->strIndex] == ' ' || str[f->strIndex] == '\t' ||
              str[f->strIndex] == '\n')) {
        f->strIndex++;
      }
      f->strIndex++;
    } else if (format[i] == '%' && f->isSpec) {
      f->specCount += 1;
      if (f->go) readInfo(f, format, &i);
      char spec = format[i];
      if (f->go) readSpec(f, str, spec);
      if (f->isSpec && !f->skipWrite && f->go) writeSpec(f, list, format[i]);
      if (f->skipWrite && (spec == 'c' || spec == 's')) free(f->lineS);
      f->haveSpace = 0;
    }
  }

  if (checkEmpty(str) && checkEmpty(format))
    f->res = 0;
  else if (checkEmpty(str) || f->formatLen == 0 || format == s21_NULL ||
           str == s21_NULL)
    f->res = -1;
}

int checkEmpty(const char *str) {
  int count = 0;
  int len = (int)strlen(str);  // заменить на  свою
  for (int i = 0; i < len; i++) {
    if (str[i] == ' ') count++;
  }
  return count == len ? 1 : 0;
}

void writeDI(flags *f, va_list *list) {
  if (f->isShort == 1) {
    short int *p = va_arg(*list, short int *);
    *p = (short int)f->d;
  } else if (f->isShort > 1) {
    signed char *p = va_arg(*list, signed char *);
    *p = (signed char)f->d;
  } else if (f->isLong == 1) {
    long int *p = va_arg(*list, long int *);
    *p = (long int)f->d;
  } else if (f->isLong > 1) {
    long long int *p = va_arg(*list, long long int *);
    *p = f->d;
  } else {
    int *p = va_arg(*list, int *);
    *p = (int)f->d;
  }
}

void writeUOX(flags *f, va_list *list) {
  if (f->isShort == 1) {
    unsigned short int *p = va_arg(*list, unsigned short int *);
    *p = (unsigned short int)f->d;
  } else if (f->isShort > 1) {
    unsigned char *p = va_arg(*list, unsigned char *);
    *p = (signed char)f->d;
  } else if (f->isLong == 1) {
    unsigned long int *p = va_arg(*list, unsigned long int *);
    *p = (unsigned long int)f->d;
  } else if (f->isLong > 1) {
    unsigned long long int *p = va_arg(*list, unsigned long long int *);
    *p = (unsigned long long int)f->d;
  } else {
    unsigned int *p = va_arg(*list, unsigned int *);
    *p = (unsigned int)f->d;
  }
}

void writeAEFG(flags *f, va_list *list) {
  if (f->isLongDouble) {
    long double *p = va_arg(*list, long double *);
    *p = (long double)f->ld;
  } else if (f->isLong) {
    double *p = va_arg(*list, double *);
    *p = (double)f->ld;
  } else {
    float *p = va_arg(*list, float *);
    *p = (float)f->ld;
  }
}
void writeP(flags *f, va_list *list) {
  void **p = va_arg(*list, void **);
  *p = (void *)f->d;
}

void writeCS(flags *f, char c, va_list *list) {
  char *p = va_arg(*list, char *);
  if (c == 's')
    strcpy(p, f->lineS);
  else
    *p = f->lineS[0];

  free(f->lineS);
}

void writeN(flags *f, va_list *list) {
  unsigned int *p = va_arg(*list, unsigned int *);
  *p = f->strIndex;
}

void writeSpec(flags *f, va_list *list, char spec) {
  if (spec == 'd' || spec == 'i') {
    writeDI(f, list);
  } else if (spec == 'u' || spec == 'o' || compareLetter('x', spec)) {
    writeUOX(f, list);
  } else if (spec == 'f' || compareLetter('e', spec) ||
             compareLetter('g', spec) || compareLetter('a', spec)) {
    writeAEFG(f, list);
  } else if (spec == 'p') {
    writeP(f, list);
  } else if (spec == 'c' || spec == 's') {
    writeCS(f, spec, list);
  } else if (spec == 'n') {
    writeN(f, list);
  }
  if (spec != 'n') (f->res)++;
}

void readSpec(flags *f, const char *str, char spec) {
  readSign(f, str, spec);
  if (spec == '%') {
    readPercent(str, f);
  } else if (spec == 'd') {
    f->d = readDec(str, f);
  } else if (spec == 'c') {
    f->lineS = readC(str, f);
  } else if (spec == 's') {
    f->lineS = readS(str, f);
  } else if (spec == 'f' || compareLetter('e', spec) ||
             compareLetter('g', spec) || compareLetter('a', spec)) {
    f->ld = readFloat(str, f);
  } else if (spec == 'u') {
    f->d = readDec(str, f);
  } else if (compareLetter('x', spec)) {
    f->d = hexToLL(f, str);
  } else if (spec == 'o') {
    f->d = octToLL(f, str);
  } else if (spec == 'p') {
    f->d = hexToLL(f, str);
  } else if (spec == 'i') {
    f->d = readHexOctDec(f, str);
  } else if (spec == 'n') {
    while (f->haveSpace && f->strIndex < f->strLen && str[f->strIndex] == ' ')
      (f->strIndex)++;
  } else {
    f->go = 0;
  }
}

long long int readHexOctDec(flags *f, const char *str) {
  long long int d = 0;
  int countRead = 1;
  if (f->strIndex + 1 < f->strLen &&
      (f->width <= 0 || (f->width && countRead <= f->width))) {
    if (str[f->strIndex] == '0' && compareLetter('x', str[f->strIndex + 1])) {
      d = hexToLL(f, str);
    } else if (str[f->strIndex] == '0') {
      d = octToLL(f, str);
    } else {
      d = readDec(str, f);
    }
  } else {
    f->go = 0;
  }
  return d;
}

long long octToLL(flags *f, const char *str) {
  f->isSpec = 0;
  long long int lld = 0;
  int countRead = 1;
  while (f->go && f->strIndex < f->strLen &&
         (f->width <= 0 || (f->width && countRead <= f->width)) &&
         '0' <= str[f->strIndex] && str[f->strIndex] <= '7') {
    lld = lld * 8 + hexToDigit(str[f->strIndex]);
    (f->strIndex)++;
    f->isSpec = 1;
    if (f->width) countRead++;
  }

  if (f->isMinus) {
    lld *= -1;
  }
  return lld;
}

long long hexToLL(flags *f, const char *str) {
  f->isSpec = 0;
  int countRead = 1;
  long long int lld = 0;
  while (f->strIndex + 1 < f->strLen &&
         (f->width <= 0 || countRead + 2 <= f->width) &&
         charToDigit(str[f->strIndex]) == 0 &&
         compareLetter('x', str[f->strIndex + 1])) {
    f->strIndex += 2;
    if (f->width) countRead += 2;
    f->isSpec = 1;
  }
  while (f->go && f->strIndex < f->strLen &&
         (f->width <= 0 || (f->width && countRead <= f->width)) &&
         (('0' <= str[f->strIndex] && str[f->strIndex] <= '9') ||
          ('a' <= str[f->strIndex] && str[f->strIndex] <= 'f') ||
          ('A' <= str[f->strIndex] && str[f->strIndex] <= 'F'))) {
    lld = lld * 16 + hexToDigit(str[f->strIndex]);
    (f->strIndex)++;
    if (f->width) countRead++;
    f->isSpec = 1;
  }

  if (f->isMinus) {
    lld *= -1;
  }
  return lld;
}

long double readFloat(const char *str, flags *f) {
  f->isSpec = 0;
  int countRead = 1;
  long double lf = 0;
  int dotCount = 0;
  int multCount = 10;
  int eCount = 0;
  int good = 1;
  int isNeg = 0;
  unsigned long int power = 0;
  while (good && !f->noRead && f->strIndex < f->strLen &&
         (isDigit(str[f->strIndex]) || str[f->strIndex] == '.' ||
          compareLetter('e', str[f->strIndex]) ||
          compareLetter('i', str[f->strIndex]) ||
          compareLetter('n', str[f->strIndex])) &&
         (f->width <= 0 || (f->width && countRead <= f->width))) {
    if (!isNanOrInf(f, str, &lf, &good)) {
      if (isDigit(str[f->strIndex])) {
        if (!dotCount) lf = 10 * lf + charToDigit(str[f->strIndex]);
        if (dotCount) {
          lf += (1.0 * charToDigit(str[f->strIndex])) / (multCount);
          multCount *= 10;
        }
        (f->strIndex)++;
        countRead++;
        f->isSpec = 1;
      }
      if (str[f->strIndex] == '.') {
        dotCount++;
        (f->strIndex)++;
        countRead++;
        if (dotCount > 1) {
          good = 0;
          (f->strIndex)--;
          countRead--;
        }
      }
      if (good && compareLetter('e', str[f->strIndex])) {
        readE(f, str, &eCount, &countRead, &good, &isNeg, &power);
      }
    }
  }
  if (power) {
    for (s21_size_t i = 0; i < power; i++) {
      if (isNeg)
        lf /= 10;
      else
        lf *= 10;
    }
  }
  if (f->isMinus) lf *= -1;
  return lf;
}

void readE(flags *f, const char *str, int *eCount, int *countRead, int *good,
           int *isNeg, unsigned long int *power) {
  (*eCount)++;
  if (*eCount > 1)
    *good = 0;
  else {
    if (f->strIndex + 2 < f->strLen &&
        (str[f->strIndex + 1] == '+' || str[f->strIndex + 1] == '-') &&
        isDigit(str[f->strIndex + 2]) &&
        (f->width <= 0 || (f->width && (*countRead) + 1 <= f->width))) {
      if (str[f->strIndex + 1] == '-') *isNeg = 1;
      f->strIndex += 2;
      *countRead += 2;
      f->isSpec = 1;
    } else if (f->strIndex + 1 < f->strLen && isDigit(str[f->strIndex + 1]) &&
               (f->width <= 0 || (f->width && (*countRead) + 1 <= f->width))) {
      (f->strIndex)++;
    }
    while (f->strIndex < f->strLen && isDigit(str[f->strIndex]) &&
           (f->width <= 0 || (f->width && (*countRead + 1) <= f->width))) {
      (*power) = 10 * (*power) + charToDigit(str[f->strIndex]);
      (f->strIndex)++;
      (*countRead)++;
      *good = 0;
      f->isSpec = 1;
    }
  }
}

int isNanOrInf(flags *f, const char *str, long double *lf, int *good_to_go) {
  int result = 0;
  if (f->strIndex + 2 < f->strLen && compareLetter('n', str[f->strIndex]) &&
      compareLetter('a', str[f->strIndex + 1]) &&
      compareLetter('n', str[f->strIndex + 2])) {
    f->strIndex += 3;
    *lf = 0.0 / 0.0;
    *good_to_go = 0;
    f->isSpec = 1;
    result = 1;
  } else if ((f->strIndex + 1 < f->strLen) &&
             compareLetter('i', str[f->strIndex]) &&
             compareLetter('n', str[f->strIndex + 1]) &&
             compareLetter('f', str[f->strIndex + 2])) {
    (f->strIndex) += 3;
    *lf = 1.0 / 0.0;
    *good_to_go = 0;
    f->isSpec = 1;
    result = 1;
    if ((f->strIndex + 4 < f->strLen) && compareLetter('i', str[f->strIndex]) &&
        compareLetter('n', str[f->strIndex + 1]) &&
        compareLetter('i', str[f->strIndex + 2]) &&
        compareLetter('t', str[f->strIndex + 3]) &&
        compareLetter('y', str[f->strIndex + 4])) {
      f->strIndex += 5;
    }
  }
  return result;
}

void readPercent(const char *str, flags *f) {
  while (f->strIndex < f->strLen && str[f->strIndex] != '%') {
    f->strIndex++;
  }
  if (str[f->strIndex] == '%') {
    f->strIndex++;
    f->skipWrite = 1;
  } else {
    f->isSpec = 0;
  }
}

char *readS(const char *str, flags *f) {
  f->isSpec = 0;
  s21_size_t lineSize = 1;
  char *lineS = s21_NULL;
  int countRead = 1;
  while (f->strIndex < f->strLen &&
         (str[f->strIndex] == ' ' || str[f->strIndex] == '\t' ||
          str[f->strIndex] == '\n'))
    (f->strIndex)++;
  while (f->go && f->strIndex < f->strLen && str[f->strIndex] != ' ' &&
         str[f->strIndex] != '\t' &&
         (!f->width || (f->width && countRead <= f->width))) {
    f->isSpec = 1;
    addEl(&lineS, &lineSize, str[f->strIndex], f);
    (f->strIndex)++;
    if (f->width) countRead++;
  }

  return lineS;
}

char *readC(const char *str, flags *f) {
  f->isSpec = 0;
  s21_size_t lineSize = 1;
  char *lineS = s21_NULL;
  int countRead = 1;
  while (f->haveSpace && f->strIndex < f->strLen &&
         (str[f->strIndex] == ' ' || str[f->strIndex] == '\t' ||
          str[f->strIndex] == '\n'))
    (f->strIndex)++;
  while (
      f->go && f->strIndex < f->strLen &&
      ((!f->width && lineSize == 1) || (f->width && countRead <= f->width))) {
    f->isSpec = 1;
    addEl(&lineS, &lineSize, str[f->strIndex], f);
    (f->strIndex)++;
    if (f->width) countRead++;
  }

  return lineS;
}

long long int readDec(const char *str, flags *f) {
  f->isSpec = 0;
  long long int lld = 0;
  int countRead = 1;
  //  while (f->haveSpace && !f->noRead && f->strIndex < f->strLen &&
  //  !isDigit(str[f->strIndex]) && //возможно и не нужно, нужно посмотреть как
  //  работает на убунте
  //      (f->width <= 0 || (f->width && countRead <= f->width))) {
  //    f->strIndex++;
  //  }
  while (!f->noRead && f->strIndex < f->strLen && isDigit(str[f->strIndex]) &&
         (f->width <= 0 || (f->width && countRead <= f->width))) {
    f->isSpec = 1;

    lld = 10 * lld + (int)str[f->strIndex] - 48;
    (f->strIndex) += 1;
    if (f->width) countRead++;
  }
  if (f->isMinus) {
    lld *= -1;
  }

  return lld;
}

void readSign(flags *f, const char *str, char c) {
  int good = 0;
  char *spec = "dfeEgGaAxXopiu";
  for (s21_size_t i = 0; i < strlen(spec) && !good; i++) {
    if (c == spec[i]) good = 1;
  }
  if (good) {
    f->isMinus = 0;
    while (f->strIndex < f->strLen &&
           (str[f->strIndex] == ' ' || str[f->strIndex] == '\n' ||
            str[f->strIndex] == '\t') &&
           str[f->strIndex] != '+' && str[f->strIndex] != '-')
      (f->strIndex)++;
    if ((str[f->strIndex] == '+' || str[f->strIndex] == '-') &&
        (f->strIndex + 1) < f->strLen &&
        (isDigit(str[f->strIndex + 1]) ||
         compareLetter('i', str[f->strIndex + 1]) ||
         compareLetter('n', str[f->strIndex + 1]) ||
         ('a' <= str[f->strIndex + 1] && str[f->strIndex + 1] <= 'f') ||
         ('A' <= str[f->strIndex + 1] && str[f->strIndex + 1] <= 'F'))) {
      if (str[f->strIndex] == '-') {
        f->isMinus = 1;
        (f->width)--;
        if (f->width == 0) f->noRead = 1;
      }
      if (str[f->strIndex] == '+') {
        (f->width)--;
        if (f->width == 0) f->noRead = 1;
      }
      (f->strIndex)++;
    }
  }
}

void readInfo(flags *f, const char *format, s21_size_t *i) {
  f->width = 0;
  f->skipWrite = 0;
  (*i)++;
  if (*i < f->formatLen && format[*i] == '*') {
    f->skipWrite = 1;
    (*i)++;
  }
  while (*i < f->formatLen && isDigit(format[*i])) {
    f->width = f->width * 10 + charToDigit(format[*i]);
    (*i)++;
  }

  while (*i < f->formatLen &&
         (compareLetter(format[*i], 'l') || format[*i] == 'h')) {
    if (format[*i] == 'l')
      f->isLong++;
    else if (format[*i] == 'h')
      f->isShort++;
    else if (format[*i] == 'L')
      f->isLongDouble++;
    (*i)++;
  }
}

int isDigit(char c) { return '0' <= c && c <= '9' ? 1 : 0; }

int charToDigit(char c) { return (int)c - 48; }

int compareLetter(char need, char check) {
  int res = 0;
  if ((need == check) || (65 <= need && need <= 90 && (check - 32) == need) ||
      (97 <= need && need <= 122 && (check + 32) == need))
    res = 1;
  return res;
}

void addEl(char **line, s21_size_t *size, char add, flags *f) {
  f->go = 0;
  (*line) = realloc(*line, (*size + 1) * sizeof(char));
  if ((*line) != s21_NULL) {
    (*line)[*size - 1] = add;
    (*line)[*size] = '\0';
    (*size)++;
    f->go = 1;
  }
}

int hexToDigit(char c) {
  int res = 0;
  if ('a' <= c && c <= 'f')
    res = c - 87;
  else if ('A' <= c && c <= 'F')
    res = c - 55;
  else
    res = charToDigit(c);

  return res;
}