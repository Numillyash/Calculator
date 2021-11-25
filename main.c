#include <stdio.h>
#include "stack.h"
#include "string.h"

#include "structure.h"

#include "stack.h"
#include "stack_signs.h"

int priority(char ch)
{
    switch (ch)
    {
        case ')':
            return 0;
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '^':
            return 3;
        case '!':
            return 4;
        case '(':
            return 5;
        default:
            return -1;
    }
}

number eval(number *number1, number *number2, char sign) // Вычисляет выражение
{
    switch (sign)
    {
        case '+':
            return plus(number1, number2);
        case '-':
            return minus(number1, number2);
        case '*':
            return proizv(number1, number2);
        case '^':
            return degree(number1, number2);
        default:
            return init();
    }
}

number calculate(char str[])
{
    struct stack_s *SGsigns = newStackS(1000); // Для знаков
    struct stack *STnums = newStack(1000); // Для чисел

    number n = init(); // Рабочее число
    long len = 0;
    for (int i = 0; i < strlen(str); ++i)
    {
        char ch = str[i];
        printf("=== %c ===\n", ch);
        if (ch >= '0' && ch <= '9')
        {
            add_element(&n, ch - '0');
            len++;
            printf("Add %d\n", ch - '0');
        }

        else
        {
            if (i != 0 && len != 0)
            {
                int flag = 0; // flag to catch factorial operation

                reverse(&n);
                if (ch == '!')
                {
                    n = factorial(&n);
                    printf("FACTORIAL!\n >>");
                    print_number(&n);
                    flag = 1;
                }

                print_number(&n);
                printf("PUSH!\n");
                push(STnums, n);

                if (flag)
                {
                    n = init();
                    len = 0;
                    continue;
                }
            }

            else if ((len == 0 && ch == '-'))
            {
                if (i != 0)
                {
                    if (str[i - 1] == '(')
                    {
                        n.negative = -1;
                    }
                    else
                    {
                        printf("\nERROR !!!\n");
                        return init();
                    }
                }
                else
                {
                    n.negative = -1;
                }
                continue;
            }

            // Почистить N
            n = init();
            len = 0;

            if (ch == ' ')
            {
                printf("ERROR\n");
                return init();
            }

            printf("A sign!\n");

            if(ch == '(' && peekS(SGsigns) == ')')
            {
                popS(SGsigns);
                continue;
            }

            int iPriority;
            if (isEmptyS(SGsigns))
                iPriority = -1;
            else
                iPriority = priority(peekS(SGsigns));


            if (priority(ch) > iPriority)
            {
                printf("Higher prior\n");
                pushS(SGsigns, ch);
                continue;
            }

            else
            {
                printf("Lower prior\n");
                number num1 = pop(STnums);
                number num2 = pop(STnums);
                print_number(&num1);
                print_number(&num2);

                number result = eval(&num2, &num1, popS(SGsigns));
                print_number(&result);
                push(STnums, result);

                number peekR = peek(STnums);
                print_number(&peekR);

                pushS(SGsigns, ch);
            }
        }
    }

    if (len != 0)
    {
        reverse(&n);
        print_number(&n);
        printf("PUSH!\n");
        push(STnums, n);
    }

    printf("\nString is parsed!\n");

    while (!isEmptyS(SGsigns))
    {
        number num1 = pop(STnums);
        printf("Got 1st num!\n");
        print_number(&num1);

        number num2 = pop(STnums);
        printf("Got 2nd num!\n");
        print_number(&num2);

        number result = eval(&num2, &num1, popS(SGsigns));
        push(STnums, result);
    }

    number result = pop(STnums);
//    print_number(&result);
    return result;
}

int main()
{
    char str[] = "-1 + 2"; // Исходная строка
    number result = calculate(str);
    print_number(&result);
}
