#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inputFileName[] = "queue.txt";
char outputFileName[] = "queue.txt";

struct node {
    char inf[256];      // данные
    int priority;       // приоритет
    struct node* next;  // указатель на следующий элемент
};

struct node* head = NULL, *last = NULL, *f = NULL; // указатели на первый и последний элементы

struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];
    int priority;

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {  // выделяем память под новый элемент
        printf("Memory allocation error\n");
        exit(1);
    }

    printf("Enter object name: \n");   // вводим данные
    scanf("%s", s);
    if (*s == 0) {
        printf("No recording was made\n");
        return NULL;
    }
    strcpy(p->inf, s);

    printf("Enter object priority: \n");   // вводим приоритет
    scanf("%d", &priority);
    p->priority = priority;

    p->next = NULL;

    return p;       // возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в соответствии с приоритетом) */
void spstore(void) {
    struct node* p = NULL;
    p = get_struct();
    if (head == NULL && p != NULL) {    // если списка нет, то устанавливаем голову списка
        head = p;
        last = p;
    }
    else if (head != NULL && p != NULL) { // список уже есть, то вставляем в соответствии с приоритетом
        struct node* current = head;
        struct node* prev = NULL;

        while (current != NULL && p->priority >= current->priority) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            // Вставляем в начало списка
            p->next = head;
            head = p;
        }
        else {
            // Вставляем между prev и current
            prev->next = p;
            p->next = current;
            if (current == NULL) {
                last = p; // Если p вставлен в конец списка, обновляем last
            }
        }
    }
}

/* Просмотр содержимого списка. */
void review(void) {
    struct node* struc = head;
    if (head == NULL) {
        printf("List is empty\n");
    }
    while (struc) {

        printf("Name - %s, Priority - %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }
}

/* Поиск элемента по содержимому. */
struct node* find(char* name) {
    struct node* struc = head;
    if (head == NULL) {
        printf("List is empty\n");
    }
    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            return struc;
        }
        struc = struc->next;
    }
    printf("Element not found\n");
    return NULL;
}

/* Удаление элемента по содержимому. */
void del(char* name) {
    struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
    struct node* prev = NULL;  // указатель на предшествующий удаляемому элементу
    int flag = 0;             // индикатор отсутствия удаляемого элемента в списке

    if (head == NULL) // если голова списка равна NULL, то список пуст
    {
        printf("List is empty\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
    {
        flag = 1;
        head = struc->next; // устанавливаем голову на следующий элемент
        free(struc);  // удаляем первый элемент
        struc = head; // устанавливаем указатель для продолжения поиска
    }
    else {
        prev = struc;
        struc = struc->next;
    }

    while (struc) // проход по списку и поиск удаляемого элемента
    {
        if (strcmp(name, struc->inf) == 0) // если нашли, то
        {
            flag = 1;         // выставляем индикатор
            if (struc->next)  // если найденный элемент не последний в списке
            {
                prev->next = struc->next; // меняем указатели
                free(struc);        // удаляем  элемент
                struc = prev->next; // устанавливаем указатель для продолжения поиска
            }
            else            // если найденный элемент последний в списке
            {
                prev->next = NULL; // обнуляем указатель предшествующего элемента
                free(struc);    // удаляем  элемент
                last = prev;    // обновляем last
                return;
            }
        }
        else    // если не нашли, то
        {
            prev = struc; // устанавливаем указатели для продолжения поиска
            struc = struc->next;
        }
    }

    if (flag == 0) // если флаг = 0, значит нужный элемент не найден
    {
        printf("Element not found\n");
        return;
    }
}

void saveListToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Open file error\n");
        return;
    }

    struct node* struc = head;
    while (struc) {
        fprintf(file, "%s %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }

    fclose(file);
    printf("List was successfully saved %s\n", filename);
}

void loadListFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Open file error\n");
        return;
    }

    struct node* current = head;
    while (current != NULL) {
        struct node* next = current->next;
        free(current);
        current = next;
    }
    head = last = NULL;

    char inf[256];
    int priority;
    while (fscanf(file, "%s %d", inf, &priority) != EOF) {
        struct node* p = (struct node*)malloc(sizeof(struct node));
        if (p == NULL) {
            printf("Memory allocation error\n");
            fclose(file);
            exit(1);
        }
        strcpy(p->inf, inf);
        p->priority = priority;
        p->next = NULL;

        // Вставка элемента в отсортированый список
        if (head == NULL || priority < head->priority) {
            // Вставка в начало
            p->next = head;
            head = p;
        }
        else {
            struct node* current = head;
            struct node* prev = NULL;
            while (current != NULL && priority >= current->priority) {
                prev = current;
                current = current->next;
            }
            // Вставка между prev и current
            prev->next = p;
            p->next = current;
            if (current == NULL) {
                last = p; // Обновление last, если p вставлен в конец
            }
        }
    }

    fclose(file);
    printf("List was successfully upload %s\n", filename);
}


int main() {
    int choice;
    char name[256];
    struct node* found = NULL;

    while (1) {
        printf("\n1. Add element\n");
        printf("2. View list\n");
        printf("3. Find element\n");
        printf("4. Delete element\n");
        printf("5. Save list\n");
        printf("6. Load list\n");
        printf("7. Exit\n");
        printf("Enter operation: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                spstore();
                break;
            case 2:
                review();
                break;
            case 3:
                printf("Enter the name of the object to search for: ");
                scanf("%s", name);
                found = find(name);
                if (found != NULL) {
                    printf("Element: Name - %s, Priority - %d\n", found->inf, found->priority);
                }
                break;
            case 4:
                printf("Enter the name of the object to delete: ");
                scanf("%s", name);
                del(name);
                break;
            case 5:
                saveListToFile(outputFileName); // Function to save the queue to a file
                break;
            case 6:
                loadListFromFile(inputFileName); // Function to load the queue from a file
                break;
            case 7:
                exit(0);
            default:
                printf("Wrong choice. Please select again.\n");
        }
    }
}
