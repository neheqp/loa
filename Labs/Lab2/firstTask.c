#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(linker, "/STACK:146800640000")

int main(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int number = 800;

    time_t start, end; // объявляем переменные для определения времени выполнения

    int i = 0, j = 0, r;
    int a[number][number], b[number][number], c[number][number], elem_c;

    srand(time(NULL)); // инициализируем параметры генератора случайных чисел

    while (i < number)
    {
        j = 0;
        while (j < number)
        {
            a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
            j++;
        }
        i++;
    }

    srand(time(NULL)); // инициализируем параметры генератора случайных чисел
    i = 0;
    j = 0;
    while (i < number)
    {
        j = 0;
        while (j < number)
        {
            b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
            j++;
        }
        i++;
    }

    start = clock();

    for (i = 0; i < number; i++)
    {
        for (j = 0; j < number; j++)
        {
            elem_c = 0;
            for (r = 0; r < number; r++)
            {
                elem_c = elem_c + a[i][r] * b[r][j];
            }
            c[i][j] = elem_c; // Moved outside the innermost loop
        }
    }

    end = clock();
    double time = (end - start) / 1000.0;
    printf("Time: %lf", time);

    return 0;
}