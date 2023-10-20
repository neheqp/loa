#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256];     // Полезная информация
    struct node* next; // Ссылка на следующий элемент
};

struct node* top = NULL; // Указатель на вершину стека

void push(void);
void pop(void);
void display(void);
void saveToFile(void);
void loadFromFile(void);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) // Выделяем память под новый элемент стека
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    printf("Enter object name: \n"); // Вводим данные
    scanf("%s", s);
    if (*s == 0)
    {
        printf("The recording was not completed\n");
        return NULL;
    }
    strcpy(p->inf, s);

    p->next = NULL;

    return p; // Возвращаем указатель на созданный элемент
}

/* Добавление элемента в стек */
void push(void)
{
    struct node* p = NULL;
    p = get_struct();
    if (p != NULL)
    {
        p->next = top;
        top = p;
    }
}

/* Удаление элемента из стека (с вершины) */
void pop(void)
{
    if (top == NULL)
    {
        printf("Stack is empty\n");
        return;
    }

    struct node* temp = top;
    top = top->next;
    free(temp);
}

/* Просмотр содержимого стека */
void display(void)
{
    struct node* struc = top;
    if (top == NULL)
    {
        printf("Stack is empty\n");
    }
    while (struc)
    {
        printf("%s \n", struc->inf);
        struc = struc->next;
    }
}

/* Сохранение данных стека в файл */
void saveToFile(void)
{
    FILE* file;
    struct node* struc = top;

    if (top == NULL)
    {
        printf("Stack is empty, no data to save\n");
        return;
    }

    file = fopen("stack.txt", "w");
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
    printf("Stack data was successfully save\n");
}

void loadFromFile(void)
{
    FILE* file;
    char s[256];

    file = fopen("stack.txt", "r");
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
            printf("File allocation error\n");
            exit(1);
        }
        strcpy(p->inf, s);
        p->next = top;
        top = p;
    }

    fclose(file);
    printf("Data was successfully loaded\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\nStack operation:\n");
        printf("1. Add element\n");
        printf("2. Delete element\n");
        printf("3. View stack\n");
        printf("5. Save data\n");
        printf("6. Exit\n");
        printf("Enter operation: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                push();
                break;
            case 2:
                pop();
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
                printf("Wrong choice\n");
        }
    }
}
