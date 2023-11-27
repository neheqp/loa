#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>

int main()
{
    setlocale(LC_ALL, "RUS");

    int num_vertices, count_size_graph = 0, count_edges = 0;

    // Ввод количества вершин графа
    printf("Введите количество вершин графа: ");
    scanf("%d", &num_vertices);

    // Расширение памяти для матрицы инцендентности 
    int** graph = (int**)malloc(num_vertices * sizeof(int*));
    for (int i = 0; i < num_vertices; i++)
    {
        graph[i] = (int*)malloc(num_vertices * sizeof(int));
    }

    int degree_dominant = num_vertices - 1; // Степень доминантной вершины

    srand(time(NULL));

    // Генерируем случайную матрицу смежности
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = i; j < num_vertices; j++)
        {
            if (i == j)
            {
                graph[i][j] = 0;
            }
            else
            {
                graph[i][j] = graph[j][i] = rand() % 2; 
            }
        }
    }

    printf("\nМатрица смежности:\n");

    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    // Определение размера графа по ребрам
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = i; j < num_vertices; j++) 
        {
            if (graph[i][j] == 1)
            {
                count_size_graph++;
            }
        }
    }
    printf("\nРазмер графa = %d\n", count_size_graph);

    // Изолированные вершины
    for (int i = 0; i < num_vertices; i++)
    {
        count_edges = 0; // Края
        for (int j = 0; j < num_vertices; j++)
        {
            if (graph[i][j] == 1) // Если есть ребро
            {
                count_edges++;
            }
        }
        if (count_edges == 0) // Изолированная
        {
            printf("\n%d-я вершина изолированая\n", i + 1);
        }
        if (count_edges == 1)
        {
            printf("\n%d-я вершина концевая\n", i + 1);
        }
        if (count_edges == degree_dominant)
        {
            printf("\n%d-я вершина доминирующая\n", i + 1);
        }
    }
    
    // Расширение памяти для матрицы инцидентности 
    int** Incident_matrix = (int**)malloc(num_vertices * sizeof(int*));
    for (int i = 0; i < num_vertices; i++)
    {
        Incident_matrix[i] = (int*)malloc(count_size_graph * sizeof(int));
    }
    // Инициализация матрицы инцидентности
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < count_size_graph; j++) {
            Incident_matrix[i][j] = 0;
        }
    }

    // Заполняем матрицу инцидентности
    int edge_index = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            if (graph[i][j] == 1) {
                Incident_matrix[i][edge_index] = 1;
                Incident_matrix[j][edge_index] = 1;
                edge_index++;
            }
        }
    }


   
    printf("\nМатрица инцидентности: \n");
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < count_size_graph; j++)
        {
            printf("%d ", *(*(Incident_matrix + i) + j));
        }
        printf("\n");
    }

    printf("\nРазмер графа = %d\n", count_size_graph);
    for (int i = 0; i < num_vertices; i++)
    {
        count_edges = 0; // Счетчик краев
        for (int j = 0; j < num_vertices; j++)
        {
            if (graph[i][j] == 1) // Если есть ребро
            {
                count_edges++;
            }
        }
        if (count_edges == 0) // Если ребер нет, то вершина изолирована
        {
            printf("\n%d-я вершина изолированная\n", i + 1);
        }
        if (count_edges == 1)
        {
            printf("\n%d-я вершина концевая\n", i + 1);
        }
        if (count_edges == degree_dominant)
        {
            printf("\n%d-я вершина доминирующая\n", i + 1);
        }
    }

    // Освобождаем память матрицы смежности
    for (int i = 0; i < num_vertices; i++) {
        free(graph[i]);
    }
    free(graph);

    // Освобождаем память матрицы инцидентов
    for (int i = 0; i < num_vertices; i++) {
        free(Incident_matrix[i]);
    }
    free(Incident_matrix);

    return 0;
}
