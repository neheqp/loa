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

    // ���� ���������� ������ �����
    printf("������� ���������� ������ �����: ");
    scanf("%d", &num_vertices);

    // ���������� ������ ��� ������� �������������� 
    int** graph = (int**)malloc(num_vertices * sizeof(int*));
    for (int i = 0; i < num_vertices; i++)
    {
        graph[i] = (int*)malloc(num_vertices * sizeof(int));
    }

    int degree_dominant = num_vertices - 1; // ������� ����������� �������

    srand(time(NULL));

    // ���������� ��������� ������� ���������
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

    printf("\n������� ���������:\n");

    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    // ����������� ������� ����� �� ������
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
    printf("\n������ ����a = %d\n", count_size_graph);

    // ������������� �������
    for (int i = 0; i < num_vertices; i++)
    {
        count_edges = 0; // ����
        for (int j = 0; j < num_vertices; j++)
        {
            if (graph[i][j] == 1) // ���� ���� �����
            {
                count_edges++;
            }
        }
        if (count_edges == 0) // �������������
        {
            printf("\n%d-� ������� ������������\n", i + 1);
        }
        if (count_edges == 1)
        {
            printf("\n%d-� ������� ��������\n", i + 1);
        }
        if (count_edges == degree_dominant)
        {
            printf("\n%d-� ������� ������������\n", i + 1);
        }
    }
    
    // ���������� ������ ��� ������� ������������� 
    int** Incident_matrix = (int**)malloc(num_vertices * sizeof(int*));
    for (int i = 0; i < num_vertices; i++)
    {
        Incident_matrix[i] = (int*)malloc(count_size_graph * sizeof(int));
    }
    // ������������� ������� �������������
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < count_size_graph; j++) {
            Incident_matrix[i][j] = 0;
        }
    }

    // ��������� ������� �������������
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


   
    printf("\n������� �������������: \n");
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < count_size_graph; j++)
        {
            printf("%d ", *(*(Incident_matrix + i) + j));
        }
        printf("\n");
    }

    printf("\n������ ����� = %d\n", count_size_graph);
    for (int i = 0; i < num_vertices; i++)
    {
        count_edges = 0; // ������� �����
        for (int j = 0; j < num_vertices; j++)
        {
            if (graph[i][j] == 1) // ���� ���� �����
            {
                count_edges++;
            }
        }
        if (count_edges == 0) // ���� ����� ���, �� ������� �����������
        {
            printf("\n%d-� ������� �������������\n", i + 1);
        }
        if (count_edges == 1)
        {
            printf("\n%d-� ������� ��������\n", i + 1);
        }
        if (count_edges == degree_dominant)
        {
            printf("\n%d-� ������� ������������\n", i + 1);
        }
    }

    // ����������� ������ ������� ���������
    for (int i = 0; i < num_vertices; i++) {
        free(graph[i]);
    }
    free(graph);

    // ����������� ������ ������� ����������
    for (int i = 0; i < num_vertices; i++) {
        free(Incident_matrix[i]);
    }
    free(Incident_matrix);

    return 0;
}
