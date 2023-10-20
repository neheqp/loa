#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256];     // Полезная информация
    struct node* next; // Ссылка на следующий элемент
};

struct node* front = NULL, * rear = NULL; // Указатели на начало и конец очереди

void enqueue(void); // Добавление элемента в очередь
int dequeue(char* name); // Удаление элемента из очереди
void display(void); // Просмотр содержимого очереди
void saveToFile(void); // Сохранение данных очереди в файл
void loadFromFile(void); // Загрузка данных очереди из файла

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) // Выделяем память под новый элемент очереди
    {
        printf("Memory allocation mistake\n");
        exit(1);
    }

    printf("Enter object name: \n"); // Вводим данные
    scanf("%s", s);
    if (*s == 0)
    {
        printf("Recording wasn't completed\n");
        return NULL;
    }
    strcpy(p->inf, s);

    p->next = NULL;

    return p; // Возвращаем указатель на созданный элемент
}

/* Добавление элемента в очередь */
void enqueue(void)
{
    struct node* p = NULL;
    p = get_struct();
    if (rear == NULL && p != NULL) // Если очередь пуста, то устанавливаем начало и конец очереди
    {
        front = p;
        rear = p;
    }
    else if (rear != NULL && p != NULL) // В очереди уже есть элементы, добавляем в конец
    {
        rear->next = p;
        rear = p;
    }
    return;
}

/* Удаление элемента из очереди (из начала) */
int dequeue(char* name)
{
    struct node* temp = front;
    struct node* prev = NULL;
    int flag = 0;

    if (front == NULL) // Если начало очереди равно NULL, то очередь пуста
    {
        printf("Queue is empty\n");
        return 0;
    }
    if (strcmp(name, temp->inf) == 0)
    {
        flag = 1;
        front = temp->next; // мб тумп заменить на фронт
        free(temp);
    }
    else {
        prev = temp;
        temp = temp->next;
    }

    while (temp)
    {
        if (strcmp(name, temp->inf) == 0)
        {
            flag = 1;
            if (temp->next)
            {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
            else
            {
                prev->next = NULL;
                free(temp);
                return 0;
            }
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }

    if (flag == 0)
    {
        printf("Object not found");
        return 0;
    }
}

/* Просмотр содержимого очереди */
void display(void)
{
    struct node* struc = front;
    if (front == NULL)
    {
        printf("Queue is empty\n");
    }
    while (struc)
    {
        printf("%s \n", struc->inf);
        struc = struc->next;
    }
    return;
}

/* Сохранение данных очереди в файл */
void saveToFile(void)
{
    FILE* file;
    struct node* struc = front;

    if (front == NULL)
    {
        printf("Queue is empty, no data to save\n");
        return;
    }

    file = fopen("queue.txt", "w");
    if (file == NULL)
    {
        printf("Open file error\n");
        return;
    }

    while (struc)
    {
        fprintf(file, "%s\n", struc->inf);
        struc = struc->next;
    }

    fclose(file);
    printf("Data was successfully saved\n");
}

/* Загрузка данных очереди из файла */
void loadFromFile(void)
{
    FILE* file;
    char s[256];

    file = fopen("queue.txt", "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    while (fscanf(file, "%s", s) != EOF)
    {
        struct node* p = (struct node*)malloc(sizeof(struct node));
        if (p == NULL)
        {
            printf("Memory allocation error\n");
            exit(1);
        }
        strcpy(p->inf, s);
        p->next = NULL;

        if (rear == NULL)
        {
            front = p;
            rear = p;
        }
        else
        {
            rear->next = p;
            rear = p;
        }
    }

    fclose(file);
    printf("Data was successfully loaded\n");
}

int main()
{
    int choice;
    char name[256];

    while (1)
    {
        printf("\n Queue operations:\n");
        printf("1. Add object \n");
        printf("2. Remove object \n");
        printf("3. View queue \n");
        printf("4. Save data \n");
        printf("5. Load data \n");
        printf("6. Exit \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enqueue();
                break;
            case 2:
                printf("Which element you want remove?: ");
                scanf("%s", &name);
                dequeue(name);
                break;
            case 3:
                display();
                break;
            case 4:
                saveToFile();
                break;
            case 5:
                loadFromFile();
                break;
            case 6:
                exit(0);
            default:
                printf("Wrong choice \n");
        }
    }
}
