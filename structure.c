#include "structure.h"
#include "stdlib.h"

int _max(int x, int y) {
    return (x > y) ? x : y;
}

number empty()
{
    number n;
    n.current_count = -1;

    return n;
}

number init() {
    number result = {0, 1, 1};
    result.mas = (unsigned char *) realloc(result.mas, sizeof(unsigned char));
    return result;
}

number copy(number *value) {
    number result = init();
    for (int i = 0; i < value->current_count; i++)
        add_element(&result, value->mas[i]);
    result.negative = value->negative;
    return result;
}

number normalize(number *value) {
    number result = init();
    int end = value->current_count - 1;
    for (int i = value->current_count - 1; i >= 0; i--) {
        end = i;
        if (value->mas[i] != 0) {
            break;
        }
    }
    for (int i = 0; i <= end; i++) {
        add_element(&result, value->mas[i]);
    }
    result.negative = value->negative;
    return result;
}

void reverse(number *value)
{
    number prom = init();
    for(int i = value->current_count-1; i >= 0; i--)
    {
        add_element(&prom,value->mas[i]);
    }
    for(int i = 0; i < prom.current_count; i++)
    {
        value->mas[i] = prom.mas[i];
    }
}

void print_number(number *value) {
    if (value->negative == -1)
        printf("-");
    for (int i = value->current_count - 1; i >= 0; i--)
        printf("%d", value->mas[i]);
    printf("\n");
}

void print_number_d(number *value) {
    if (value->negative == -1)
        printf("-");
    for (int i = value->current_count - 1; i >= 0; i--)
        printf("%d", value->mas[i]);
    printf("\n");
}

void add_element(number *object, unsigned char value) {
    if (object->current_count < object->size) {
        object->mas[object->current_count] = value;
        object->current_count += 1;
    } else {
        object->mas = (unsigned char *) realloc(object->mas, sizeof(unsigned char) * (object->size) * 2);     // Увеличение размера массива в 2 раза с сохранением содержимого
        object->mas[object->current_count] = value;
        object->current_count += 1;
        object->size *= 2;
    }
}

number plus(number *value1, number *value2) {
    number a, b;
    number result = init();

    if (value1->negative == 1 && value2->negative == -1) {
        b = copy(value2);
        b.negative = 1;
        result = minus(value1, &b);
        return result;
    } else if (value1->negative == -1 && value2->negative == 1) {
        b = copy(value1);
        b.negative = 1;
        result = minus(value2, &b);
        return result;
    } else if (value1->negative == -1 && value2->negative == -1) {
        a = copy(value1);
        a.negative = 1;
        b = copy(value2);
        b.negative = 1;
        result = plus(&a, &b);
        result.negative = -1;
        return result;
    }

    if ((value1->current_count) >= (value2->current_count)) {
        a = copy(value1);
        b = copy(value2);
    } else {
        a = copy(value2);
        b = copy(value1);
    }

    char razr = 0;
    for (int i = 0; i < a.current_count; i++) {
        if (i < b.current_count) {
            if (a.mas[i] + b.mas[i] + razr > 9) {
                add_element(&result, a.mas[i] + b.mas[i] + razr - 10);
                razr = 1;
            } else {
                add_element(&result, a.mas[i] + b.mas[i] + razr);
                razr = 0;
            }
        } else {
            if (razr == 1) {
                if (a.mas[i] + razr > 9) {
                    add_element(&result, a.mas[i] + razr - 10);
                    razr = 1;
                } else {
                    add_element(&result, a.mas[i] + razr);
                    razr = 0;
                }
            } else {
                add_element(&result, a.mas[i]);
            }
        }
    }
    if (razr == 1) {
        add_element(&result, razr);
        razr = 0;
    }
    // _print(&result);

    result = normalize(&result);
    return result;
}

number minus(number *value1, number *value2) {
    number a, b;
    number result = init();

    if (value1->negative == 1 && value2->negative == -1) {
        b = copy(value2);
        b.negative = 1;
        result = plus(value1, &b);
        return result;
    } else if (value1->negative == -1 && value2->negative == 1) {
        b = copy(value1);
        b.negative = 1;
        result = plus(value2, &b);
        result.negative = -1;
        return result;
    } else if (value1->negative == -1 && value2->negative == -1) {
        a = copy(value1);
        a.negative = 1;
        b = copy(value2);
        b.negative = 1;
        result = minus(&b, &a);
        result.negative = 1;
        return result;
    }

    if ((value1->current_count) >= (value2->current_count)) {
        a = copy(value1);
        b = copy(value2);
    } else {
        result.negative *= -1;
        a = copy(value2);
        b = copy(value1);
    }

    char razr = 0;
    for (int i = 0; i < a.current_count; i++) {
        if (i < b.current_count) {
            if (a.mas[i] - b.mas[i] - razr < 0) {
                add_element(&result, a.mas[i] - b.mas[i] - razr + 10);
                razr = 1;
            } else {
                add_element(&result, a.mas[i] - b.mas[i] - razr);
                razr = 0;
            }
        } else {
            if (razr == 1) {
                if (a.mas[i] - razr < 0) {
                    add_element(&result, a.mas[i] - razr + 10);
                    razr = 1;
                } else {
                    add_element(&result, a.mas[i] - razr);
                    razr = 0;
                }
            } else {
                add_element(&result, a.mas[i]);
            }
        }
    }

    if (razr == 1) {
        number new = init();
        for (int i = 0; i < result.current_count; i++)
            add_element(&new, 0);
        add_element(&new, 1);
        result = minus(&new, &result);
        result.negative *= -1;
        razr = 0;
    }
    result = normalize(&result);
    return result;
}

number proizv_to_digit(number *value1, int value2) {
    number sum = init();
    int count = 0;
    for(int i = 0; i < value1->current_count; i++)
    {
        int prom = (int)(value1->mas[i]);
        prom *= value2;
        number pr = int_to_number(prom);
        pr = normalize(&pr);
        number res = init();
        for (int j = 0; j < count; ++j) {
            add_element(&res,0);
        }
        for (int j = 0; j < pr.current_count; ++j) {
            add_element(&res, (int)pr.mas[j]);
        }
        sum = plus(&sum, &res);
        ++count;
    }
    return sum;
}

number proizv(number *value1, number *value2) {
    number sum = init();
    int count = 0;
    for(int i = 0; i < value2->current_count; i++)
    {
        int pr = (int)(value2->mas[i]);
        number prom = proizv_to_digit(value1, pr);

        number res = init();
        for (int j = 0; j < count; ++j) {
            add_element(&res,0);
        }
        for (int j = 0; j < prom.current_count; ++j) {
            add_element(&res, (int)prom.mas[j]);
        }
        sum = plus(&sum, &res);
        ++count;
    }
    if (value1->negative == 1 && value2->negative == 1) {
        return sum;
    }
    else if (value1->negative == 1 && value2->negative == -1) {
        sum.negative = -1;
        return sum;
    } else if (value1->negative == -1 && value2->negative == 1) {
        sum.negative = -1;
        return sum;
    } else if (value1->negative == -1 && value2->negative == -1) {
        return sum;
    }
}

number int_to_number(int value) {
    number result = init();
    int ostatok;
    while (value > 0) {
        ostatok = value % 10;
        add_element(&result, ostatok);
        value /= 10;
    }
    if (result.current_count == 0)
        add_element(&result, 0);
    return result;
}

number degree(number *value1, number *value2)
{
    number result = init();
    add_element(&result, 1);
    number prom = init();
    add_element(&prom, 1);
    number iter = copy(value2);

    while(!(iter.current_count == 1 && iter.mas[0]==0))
    {
        iter = minus(&iter,&prom);
        normalize(&iter);
        result = proizv(&result, value1);
    }
    return result;
}

number factorial(number *value)
{
    number result = init();
    add_element(&result, 1);
    number prom = init();
    add_element(&prom, 1);
    number prom2 = init();
    add_element(&prom2, 0);
    number iter = copy(value);

    while(!(iter.current_count == 1 && iter.mas[0]==0))
    {
        iter = minus(&iter,&prom);
        prom2 = plus(&prom2,&prom);
        normalize(&iter);
        result = proizv(&result, &prom2);
    }
    return result;
}