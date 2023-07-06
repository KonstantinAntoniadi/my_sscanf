## Реализация функции sscanf на языке Си

### Сборка библиотеки
`make my_sscanf.a`

### Запуск тестирования
`make test`

### Пример использования

```C
int d;
char str[512] = {"\0"};
float f;
unsigned int u;
int count;

my_sscanf("124 text 1.231 0xA1", "%d %s %f %u %n", &d, str, &f, &u, &count);
```

