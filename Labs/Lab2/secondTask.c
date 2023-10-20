#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int massiv5k[5000] = {}, massiv10k[10000] = {}, massiv15k[15000] = {}, massiv20k[20000] = {}, massiv25k[25000] = {}, massiv30k[30000] = {};
int compare(const void* arg1, const void* arg2)
{
    return *(int*)arg1 >= *(int*)arg2 ? 1 : -1;
}
void shell(int* items, int count) {
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) { //вызов функции: qs(items, 0, count-1);
    int i, j;
    int x, y;
    i = left; j = right;
    /* выбор компаранда */
    x = items[(left + right) / 2];
    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;
        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);
    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int main() {
    srand(time(NULL));
    char table_start[] = "+-------+---------------+---------------+---------------+---------------+\n"
                         "|%i\t|\t/\t|\t\\\t|      /\\\t|      Random\t|\n"
                         "+-------+---------------+---------------+---------------+---------------+\n";
    for (long long n = 5000; n != 35000; n+=5000) {
        int* current = NULL;
        clock_t start, end;
        double timers[4] = { 0 };
        switch (n) {
            case 5000:
                current = massiv5k;
                break;
            case 10000:
                current = massiv10k;
                break;
            case 15000:
                current = massiv15k;
                break;
            case 20000:
                current = massiv20k;
                break;
            case 25000:
                current = massiv25k;
                break;
            case 30000:
                current = massiv30k;
                break;
        }
        //Шелл
        //случайный массив
        for (int i = 0; i != n; i++) {
            *(current + i) = -1000 + rand() % (1000 + 1000 + 1);
        }
        //сортировка случайного массива
        start = clock();
        shell(current, n);
        end = clock();
        timers[0] = difftime(end, start) / 1000.0;
        int* tmp = current;
        //возрастающий массив
        for (int i = 0; i != n; i++) {
            *(current + i) = 2*i;
            tmp++;
        }
        //сортировка возрастающего массива
        start = clock();
        shell(current, n);
        end = clock();
        timers[1] = difftime(end, start) / 1000.0;
        //убывающий массив
        for (int i = 0; i != n; i++) {
            *(tmp - i) = 2 * i;
        }
        //сортировка убывающего массива
        start = clock();
        shell(current, n);
        end = clock();
        timers[2] = difftime(end, start) / 1000.0;
        //возрастающий и убывающий массив
        for (int i = 0; i != n; i++) {
            if (i < (n / 2))
                *(current + i) = 2 * i;
            else
                *(current + i) = *(current + i - 1) - 2;
        }
        //сортировка убывающего массива
        start = clock();
        shell(current, n);
        end = clock();
        timers[3] = difftime(end, start) / 1000.0;
        printf(table_start, n);
        printf("| Shell |%0.3f\t\t|%0.3f\t\t|%0.3f\t\t|%0.3f\t\t|\n+-------+---------------+---------------+---------------+---------------+\n", timers[1], timers[2], timers[3], timers[0]);
        //qs
        //случайный массив
        for (int i = 0; i != n; i++) {
            *(current + i) = -1000 + rand() % (1000 + 1000 + 1);
        }
        //сортировка случайного массива
        start = clock();
        qs(current, 0, n-1);
        end = clock();
        timers[0] = difftime(end, start) / 1000.0;
        tmp = current;
        //возрастающий массив
        for (int i = 0; i != n; i++) {
            *(current + i) = 2 * i;
            tmp++;
        }
        //сортировка возрастающего массива
        start = clock();
        qs(current, 0, n - 1);
        end = clock();
        timers[1] = difftime(end, start) / 1000.0;
        //убывающий массив
        for (int i = 0; i != n; i++) {
            *(tmp - i) = 2 * i;
        }
        //сортировка убывающего массива
        start = clock();
        qs(current, 0, n - 1);
        end = clock();
        timers[2] = difftime(end, start) / 1000.0;
        //возрастающий и убывающий массив
        for (int i = 0; i != n; i++) {
            if (i < (n / 2))
                *(current + i) = 2 * i;
            else
                *(current + i) = *(current + i - 1) - 2;
        }
        //сортировка убывающего массива
        start = clock();
        qs(current, 0, n - 1);
        end = clock();
        timers[3] = difftime(end, start) / 1000.0;
        printf("| qs    |%0.3f\t\t|%0.3f\t\t|%0.3f\t\t|%0.3f\t\t|\n+-------+---------------+---------------+---------------+---------------+\n", timers[1], timers[2], timers[3], timers[0]);
        //quicksort
        //случайный массив
        for (int i = 0; i != n; i++) {
            *(current + i) = -1000 + rand() % (1000 + 1000 + 1);
        }
        //сортировка случайного массива
        start = clock();
        qsort((void*)current, n, 4, compare);
        end = clock();
        timers[0] = difftime(end, start) / 1000.0;
        tmp = current;
        //возрастающий массив
        for (int i = 0; i != n; i++) {
            *(current + i) = 2 * i;
            tmp++;
        }
        //сортировка возрастающего массива
        start = clock();
        qsort((void*)current, n, 4, compare);
        end = clock();
        timers[1] = difftime(end, start) / 1000.0;
        //убывающий массив
        for (int i = 0; i != n; i++) {
            *(tmp - i) = 2 * i;
        }
        //сортировка убывающего массива
        start = clock();
        qsort((void*)current, n, 4, compare);
        end = clock();
        timers[2] = difftime(end, start) / 1000.0;
        //возрастающий и убывающий массив
        for (int i = 0; i != n; i++) {
            if (i < (n / 2))
                *(current + i) = 2 * i;
            else
                *(current + i) = *(current + i - 1) - 2;
        }
        //сортировка убывающего массива
        start = clock();
        qsort((void*)current, n, 4, compare);
        end = clock();
        timers[3] = difftime(end, start) / 1000.0;
        printf("| qsort |%0.3f\t\t|%0.3f\t\t|%0.3f\t\t|%0.3f\t\t|\n", timers[1], timers[2], timers[3], timers[0]);
    }
    return 0;
}