#include <stdio.h>
#include "stack.h"
#include "string.h"

#include "structure.h"

#include "stack.h"
#include "stack_signs.h"

number RES;

#ifdef NDEBUG
#define printf(...)
#define print_number(...)
#endif

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

int eval(number *number1, number *number2, char sign) // Вычисляет выражение
{
    if (sign == '^' && number2->negative == -1)
    {
        return -1;
    }
    switch (sign)
    {
        case '+':
            RES = plus(number1, number2);
            return 0;
        case '-':
            RES = minus(number1, number2);
            return 0;
        case '*':
             RES = proizv(number1, number2);
            return 0;
        case '^':
            RES = degree(number1, number2);
            return 0;
        default:
            printf("ERROR 1 %c!!!\n", sign);
            return -1;
    }
}

int calculate(char str[])
{
    struct stack_s *SGsigns = newStackS(1000); // Для знаков
    struct stack *STnums = newStack(1000); // Для чисел

    number n = init(); // Рабочее число
    long len = 0;
    for (int i = 0; i < strlen(str); ++i)
    {
        char ch = str[i];
        printf("=== %c ===\n", ch);

        if(ch == ')' && peekS(SGsigns) == '(')
        {
            printf("(x)!\n");
            char res = popS(SGsigns);
            if (res == '~')
                return -1;

            continue;
        }

        if (ch >= '0' && ch <= '9')
        {
            if (len == 0 && ch == '0')
                return -1;

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
                    if (n.negative == -1)
                    {
                        return -1;
                    }

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
                printf("Unary minus\n");
                if (i != 0)
                {
                    if (str[i - 1] == '(')
                    {
                        n.negative = -1;
                    }
                    else
                    {
                        printf("ERROR 2 !!!\n");
                        return -1;
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
                printf("ERROR 3 !!!\n");
                return -1;
            }

            if (ch == '\\' || ch == '\n' || ch == EOF)
            {
                continue;
            }

            char under = 'e';
            if (!isEmptyS(SGsigns))
                under = peekS(SGsigns);

            printf("A sign!\n");
            printf("-- %c %c\n", under, ch);

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

            else if (under != '(')
            {
                printf("Lower prior\n");
                number num1 = pop(STnums);
                number num2 = pop(STnums);

                if (num1.current_count == -1 || num2.current_count == -1)
                    return -1;

                print_number(&num1);
                print_number(&num2);

                char pop_res = popS(SGsigns);
                if (pop_res == '~')
                    return -1;

                int res = eval(&num2, &num1, pop_res);
                if (res == -1)
                {
                    printf("ERROR 4 !!!\n");
                }

                number result = RES;
                print_number(&result);
                push(STnums, result);

                number peekR = peek(STnums);
                print_number(&peekR);
                if (ch != ')')
                    pushS(SGsigns, ch);
                else
                {
                    i--;
                }
            }

            else
            {
                printf("Pushed ELSE %c\n", ch);
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
        char sg = popS(SGsigns);
        number num1 = pop(STnums);
        number num2 = pop(STnums);

        if(sg == '~' || num1.current_count == -1 || num2.current_count == -1)
            return -1;

        printf("%c\n", sg);

        printf("Got 1st num!\n");
        print_number(&num1);


        printf("Got 2nd num!\n");
        print_number(&num2);

        int res = eval(&num2, &num1, sg);

        if (res == -1)
        {
            printf("ERROR 5 !!!\n");
            return -1;
        }

        number result = RES;
        push(STnums, result);
    }

    number result = pop(STnums);

    if (result.current_count == -1)
        return -1;

    RES = result;
    return 0;
}

int main()
{
    FILE * fp;
    char * line = NULL;

    size_t len = 0;
    ssize_t read;

    fp = fopen("input", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int flag_end = 0;
    int count = 1;

    char *exp = (char *) malloc(1000000 * sizeof(char));
    while ((read = getline(&line, &len, fp)) != -1)
    {
        printf("\n===============\n%s\n===============\n", line);
        if (line[read - 2] == '\\')
        {
            strcat(exp, line);
//            flag_end = 1;
        }

        else
        {
            strcat(exp, line);
            int res = calculate(exp);
            fprintf(stdout, "Выражение %d. ", count);
            count++;

            if (res == 0)
            {
                fprintf(stdout, "Ответ: ");
                print_number_d(&RES);
            }

            else
            {
                fprintf(stdout, "Некорректно\n");
            }

            strcpy(exp, "");
        }
    }

    fclose(fp);
    if (line)
        free(line);
}
