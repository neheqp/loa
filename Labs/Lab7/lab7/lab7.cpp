#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <stack>

using namespace std;

struct Node
{
    int data;
    Node* next;
};

void print_adjacency_list(Node** adjacencyList, int num_vertices)
{
    Node* current;
    for (int i = 0; i < num_vertices; i++)
    {
        printf("Вершина %d примыкает к: ", i);
        current = adjacencyList[i];
        while (current != NULL)
        {
            printf("%d ", (current->data));
            current = current->next;
        }
        printf("\n");
    }
}

// Функция для преобразования матрицы смежности в список смежности с обратным порядком соседних вершин
Node** adjacency_matrix_to_adjacency_list(int** matrix, int num_vertices)
{
    Node** adjacencyList = new Node * [num_vertices];
    for (int i = 0; i < num_vertices; i++)
    {
        adjacencyList[i] = nullptr;  // Инициализируем список для вершины i

        for (int j = num_vertices - 1; j >= 0; j--) // Обходим в обратном порядке для добавления соседних вершин в обратном порядке
        {
            if (matrix[i][j] == 1)
            {
                Node* newNode = new Node;
                newNode->data = j;
                newNode->next = adjacencyList[i];
                adjacencyList[i] = newNode;
            }
        }
    }

    print_adjacency_list(adjacencyList, num_vertices);

    return adjacencyList;
}

void free_adjacency_list(Node** adjacencyList, int num_vertices)
{
    for (int i = 0; i < num_vertices; i++)
    {
        Node* current = adjacencyList[i];
        while (current != NULL)
        {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(adjacencyList);
}

// Функция поиска в глубину на основе матрицы смежности
void DFS(int vertex, int num_vertices, bool* viseted, int** graph, int& current_index)
{
    viseted[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < num_vertices; i++)
    {
        if (graph[vertex][i] == 1 && viseted[i] == false)
        {
            DFS(i, num_vertices, viseted, graph, current_index);
        }
    }
}

// Функция для обхода графа в глубину (DFS) на основе списков смежности
void DFS_list(Node** adjacencyList, int vertex, bool* visited, int* result, int currentIndex)
{
    visited[vertex] = true; // Помечаем вершину как посещенную
    result[currentIndex++] = vertex;

    // Перебираем соседние вершины, представленные в списке смежности
    Node* current = adjacencyList[vertex];
    while (current != nullptr) {
        int neighbor = current->data;
        if (!visited[neighbor])
        {
            DFS_list(adjacencyList, neighbor, visited, result, currentIndex); // Рекурсивно обходим соседнюю вершину
        }
        current = current->next;
    }
}

// Функция для нерекурсивного обхода графа в глубину (DFS)
int* nonRecursiveDFS(int** graph, int num_vertices, int startVertex)
{
    bool* visited = new bool[num_vertices];
    for (int i = 0; i < num_vertices; i++)
    {
        visited[i] = false;
    }

    int* result = new int[num_vertices];
    int currentIndex = 0;

    stack<int> vertexStack;
    vertexStack.push(startVertex);

    while (!vertexStack.empty())
    {
        int currentVertex = vertexStack.top();
        vertexStack.pop();

        if (!visited[currentVertex])
        {
            visited[currentVertex] = true;
            result[currentIndex++] = currentVertex;

            for (int i = num_vertices - 1; i >= 0; i--)
            {
                if (graph[currentVertex][i] == 1 && !visited[i])
                {
                    vertexStack.push(i);
                }
            }
        }
    }
    delete[] visited;
    return result;
}

// Основная функция
int main()
{
    setlocale(LC_ALL, "RUS");

    int num_vertices;

    // Ввод количества вершин графа
    printf("Введите количество вершин графа(Пожалуйста введите целое число): ");

    if (scanf("%d", &num_vertices) != 1)
    {
        printf("Ошибка");
        return 0;
    }

    // Расширение памяти для матрицы смежности 
    int** graph = (int**)malloc(num_vertices * sizeof(int*));
    for (int i = 0; i < num_vertices; i++)
    {
        graph[i] = (int*)malloc(num_vertices * sizeof(int));
    }

    bool* viseted = new bool[num_vertices];

    srand(time(NULL));

    // Генерируем случайную матрицу смежности
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = i; j < num_vertices; j++)
        {
            if (i == j)
            {
                graph[i][j] = 0; // Заполняем обратную диагональ 0
            }
            else
            {
                graph[i][j] = graph[j][i] = rand() % 2; // Случайным образом присваиваем 0 или 1
            }
        }
    }

    // Выводим матрицу смежности
    printf("\nМатрица смежности:\n");

    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    // Инициализируем посещенный массив
    for (int i = 0; i < num_vertices; i++)
    {
        viseted[i] = false;
    }

    int vertex;
    printf("Введите начальный узел для обхода DFS: ");
    scanf("%d", &vertex);

    printf("\nСписок смежности:\n");
    Node** adjacencyList = adjacency_matrix_to_adjacency_list(graph, num_vertices);

    int* dfsResult = new int[num_vertices];
    int currentIndex = 0;

    int* dfsResult2 = new int[num_vertices];
    int currentIndex2 = 0;

    printf("\nОбход поиска в глубину по матрице смежности: ");
    clock_t start = clock();
    DFS(vertex, num_vertices, viseted, graph, currentIndex);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf(" Время выполнения: %f \n", seconds);

    
    clock_t start1 = clock();
    DFS_list(adjacencyList, vertex, viseted, dfsResult2, currentIndex2);
    clock_t end1 = clock();
    printf("\nОбход в глубину по спискам смежности: ");

    clock_t start2 = clock();
    int* dfsResult1 = nonRecursiveDFS(graph, num_vertices, vertex);
    clock_t end2 = clock();

    for (int i = 0; i < num_vertices; i++)
    {
        printf("%d ", dfsResult1[i]);
    }

    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf(" Время выполнения: %f \n", seconds1);

    printf("\nРезультат нерекурсивного обхода в глубину: ");
    for (int i = 0; i < num_vertices; i++)
    {
        printf("%d ", dfsResult1[i]);
    }

    double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf(" Время выполнения: %f \n", seconds2);

    // Освобождаем память матрицы смежности
    for (int i = 0; i < num_vertices; i++)
    {
        free(graph[i]);
    }
    free(graph);

    delete[] viseted;

    return 0;
}
