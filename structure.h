#include <stdio.h>
#include <stdlib.h>

#ifndef INC_256SS_256_STRUCTURE_H
#define INC_256SS_256_STRUCTURE_H

int _max(int x, int y); // Возвращает максимальное значение из чисел x и у

typedef struct
{
    int current_count; // текущее количество элементов
    int size; // реальный размер массива
    char negative; // 1 если число положительное, -1 если отрицательное
    unsigned char *mas; // массив данных
}number;

number init(); // инициализирует обьект структуры с пустым массивом и положительным negative

number copy(number *value); // возвращает структуру идентичную данной

number int_to_number(int value); // возвращает структуру, в которой записано данное число в диапазоне int

number normalize(number *value); // возвращает number-обьект без незначащих нулей

void add_element(number *object, unsigned char value); // добавляет char-элемент в конец массива структуры

void reverse(number *value); // разворачивает число в данном обьекте

void print_number(number *value); // печатает обьект с учетом знака

number minus(number *value1, number *value2); // вычитает одно число из другого, с учетом внутреннего знака данных на вход чисел, и возвращает результат типа number

number plus(number *value1, number *value2); // прибавляется одно число к другому, с учетом внутреннего знака данных на вход чисел, и возвращает результат типа number

number proizv(number *value1, number *value2); // умножает одно число на другое и возвращает результат типа number

number proizv_to_digit(number *value1, int value2); // умножает одно число на одну цифру и возвращает результат типа number

number degree(number *value1, number *value2); // возводит число в степень

number factorial(number *value); // возвращает факториал числа

#endif //INC_256SS_256_STRUCTURE_H