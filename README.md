# lab4
## Файлы
*Note - "insetrionSort" написано с грамматической ошибкой.*
### main.c
```c
// C program for insertion sort
#include <math.h>
#include <stdio.h>
#include "insetrionSort.h"
#include "printArray.h"

/* Driver program to test insertion sort */
int main() {
    int arr[] = {12, 11, 13, 5, 5, 5, 5, -1, 0, 0, -999, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, n);
    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}

```
### printArray.h
```c
//
// Created by nx on 03.12.2023.
//

#ifndef LOWPROG4_PRINTARRAY_H
#define LOWPROG4_PRINTARRAY_H
#include <stdio.h>
void printArray(int arr[], int n);
#endif //LOWPROG4_PRINTARRAY_H

```
### insertionSort.h
```c
//
// Created by nx on 03.12.2023.
//
#include <stdlib.h>

#ifndef LOWPROG4_INSETRIONSORT_H
#define LOWPROG4_INSETRIONSORT_H

void insertionSort(int arr[], int n);

#endif //LOWPROG4_INSETRIONSORT_H
```
### printArray.c
```c
//
// Created by nx on 03.12.2023.
//
#include "printArray.h"

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}
```
### insertionSort.c
```c
#include "insetrionSort.h"
//
// Created by nx on 03.12.2023.
//
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
```

### makeLib
```make
CC=riscv64-unknown-elf-gcc
AR=riscv64-unknown-elf-ar
CFLAGS = -march=rv32i -mabi=ilp32 -O1
mainSort: lib

lib: insertionSort.o printArray.o
	$(AR) -rsc lib.a insertionSort.o printArray.o
	del -f *.o
insertionSort.o: insertionSort.c
	$(CC) $(CFLAGS) -c insertionSort.c -o insertionSort.o
printArray.o: printArray.c
	$(CC) $(CFLAGS) -c printArray.c -o printArray.o


```
### makeMain
```make
CC=riscv64-unknown-elf-gcc
AR=riscv64-unknown-elf-ar
MAKE=mingw32-make
CFLAGS = -march=rv32i -mabi=ilp32 -O1
mainApp: all

all:
	$(MAKE) -f makeLib
	$(CC) $(CFLAGS) main.c lib.a -o main.out
	del -f *.0 *.a

```


## Команды
#### Заходим в папку проекта
```bash
cd C:\Users\nx\Documents\lab4

```

#### Создаем файлы .c/.h/.make

#### Чекаем готовность riscv64-unknown-elf-gcc
```bash
 riscv64-unknown-elf-gcc --version
 
```
- Должно выдать такое
```output
riscv64-unknown-elf-gcc (GCC) 8.1.0
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

```
#### Препроцессим наши .c файлы
```bash
riscv64-unknown-elf-gcc -E main.c -o main.i -march=rv32i -mabi=ilp32 -O1 
riscv64-unknown-elf-gcc -E insertionSort.c -o insertionSort.i -march=rv32i -mabi=ilp32 -O1 
riscv64-unknown-elf-gcc -E printArray.c -o printArray.i -march=rv32i -mabi=ilp32 -O1

```
 - Чтобы посмотреть что что-то произошло введем ```dir``` или посмотрим через notepad все эти 10 тысяч строчек
 ```bash
 notepad main.i
 notepad insertionSort.i
 notepad printArray.i
 
```
#### Скомпилируем их (без ассемблирования и линковки компоновки)
```bash
riscv64-unknown-elf-gcc -S main.i -o main.s -march=rv32i -mabi=ilp32 -O1
riscv64-unknown-elf-gcc -S insertionSort.i -o insertionSort.s -march=rv32i -mabi=ilp32 -O1 
riscv64-unknown-elf-gcc -S printArray.i -o printArray.s -march=rv32i -mabi=ilp32 -O1

```
 - Чтобы посмотреть что что-то произошло введем ```dir``` или посмотрим через notepad что поменялось в строчках
 ```bash
 notepad main.s
 notepad insertionSort.s
 notepad printArray.s
 
```
#### Ассемблирование
```bash
riscv64-unknown-elf-gcc -c main.s -o main.o -march=rv32i -mabi=ilp32 -O1
riscv64-unknown-elf-gcc -c insertionSort.s -o insertionSort.o -march=rv32i -mabi=ilp32 -O1 
riscv64-unknown-elf-gcc -c printArray.s -o printArray.o -march=rv32i -mabi=ilp32 -O1

```
 - Чтобы посмотреть что что-то произошло введем ```dir``` или посмотрим через notepad все эти строчки
 ```bash
 notepad main.o
 notepad insertionSort.o
 notepad printArray.o
 
```
- И уже понимаем что в таком виде файл мы анализировать не можем. В объектном файле какая-то мешанина из символов [хотя некоторые ключевые слова мы еще можем различать]

- -> Поэтому воспользуемся утилитой `riscv64-unknown-elf-objdump` 
	- Для справки`riscv64-unknown-elf-objdump --help`
___
- Просмотрим заголовки секций каждого файла
```bash
riscv64-unknown-elf-objdump -h main.o
riscv64-unknown-elf-objdump -h insertionSort.o
riscv64-unknown-elf-objdump -h printArray.o

```
Секции:
> .text - скомпилированный машинный код;
> .data - секция инициализированных данных;
> .rodata - аналог .data для неизменяемых данных;
> .bss - секция данных, инициализированных нулями;
> .comment — информация о версии компилятора;
- рассмотрим секцию .text c помощью команды 
```bash
riscv64-unknown-elf-objdump -d -M no-aliases -j .text main.o
riscv64-unknown-elf-objdump -d -M no-aliases -j .text insertionSort.o
riscv64-unknown-elf-objdump -d -M no-aliases -j .text printArray.o

```
- (Опция “-d" инициирует процесс дизассемблирования, опция “-M no-aliases” требует использовать в выводе только инструкции системы команд (но не псевдоинструкции ассемблера)
___
- Рассмотрим таблицу символов и таблицу перемещений с помощью команд
```bash
riscv64-unknown-elf-objdump -t main.o insertionSort.o printArray.o > symbolTable
riscv64-unknown-elf-objdump -r main.o insertionSort.o printArray.o > relocationTable

```
- Откроем их через блокнот
```bash
notepad symbolTable
notepad relocationTable

```
#### Компоновка
```bash
riscv64-unknown-elf-gcc main.o insertionSort.o printArray.o -march=rv32i -mabi=ilp32

```
- Посмотрим что изменилось через `dir` (появился a.out в историю почему он так называется мы не будем вдаваться :) )
- А теперь посмотрим фрагмент исполняемого кода
```bash
riscv64-unknown-elf-objdump -j .text -d -M no-aliases a.out > a.ds
notepad a.ds

```

## Создание статической библиотеки
- Выделим функции insertionSort и printArray в отдельную библиотеку
- Для этого надо получить их объектные файлы и собрать их с помощью `riscv64-unknown-elf-ar` 
	- для справки см `riscv64-unknown-elf-ar --help`
```bash
# Создадим объектные файлы из исходников .c 
# (если их нет, чтобы удалить их можно сделать)
# del -f *.o
riscv64-unknown-elf-gcc -c insertionSort.s -o insertionSort.o -march=rv32i -mabi=ilp32 -O1 
riscv64-unknown-elf-gcc -c printArray.c -o printArray.o -march=rv32i -mabi=ilp32 -O1

# Cобирем их в библиотеку
riscv64-unknown-elf-ar -rsc lib.a insertionSort.o printArray.o

```
- Рассмотрим список символов библиотеки 
```bash
riscv64-unknown-elf-nm lib.a

```
- (В выводе утилиты “nm” кодом “T” обозначаются символы, определенные в соответствующем объектном файле)
- **СОЗДАДИМ ИСПОЛНЯЕМЫЙ ФАЙЛ**
```bash
riscv64-unknown-elf-gcc main.c lib.a -o main.out -march=rv32i -mabi=ilp32 -O1

```
- Чтобы убедиться, что в состав программы вошло содержание объектного файла insertionSort.o и printArray.o -> найдем их при помощи таблицы символов исполняемого файла 
```bash
riscv64-unknown-elf-objdump -t main.out > main.ds
notepad main.ds
riscv64-unknown-elf-objdump -j .text -d -M no-aliases -t main.out > mainMoreflags.ds
notepad mainMoreflags.ds

```
## Создание Make-файлов
- Процесс выполнения команд выше можно заменить make-файлами, которые произведут создание библиотеки и сборку программы 
---
### ФАЙЛЫ (ссылка на раздел выше)
### Выполнение make-файлов
- Теперь с помощью GNU make выполним сначала makeLib, а затем makeMain, для создания библиотеки
```bash 
mingw32-make -f makeLib # Эта команда служит дополнительной проверкой makeLib
dir
mingw32-make -f makeMain
dir

```

- Сравним с полученным результатом
```bash
riscv64-unknown-elf-objdump -t main.out > main.ds
notepad main.ds

```
___
> Мы видим, что исполняемый файл аналогичен созданному в терминале файлу


## Вывод
> В ходе лабораторной работы разработана программа сортировки вставками, а также изучена пошаговая компиляция программы на языке C. В дополнение была создана статическая библиотека и произведена сборка программы с помощью Makefile
