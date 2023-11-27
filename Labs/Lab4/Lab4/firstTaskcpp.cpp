#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data; // Данные дерева
    struct Node* left; // Левый узел
    struct Node* right; // Правый узел
};

// Функция создания дерева
struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) // Если дерево пусто
    {
        root = (struct Node*)malloc(sizeof(struct Node)); // Выделяется память
        if (root == NULL) // Если выделение памяти невозможно
        {
            printf("Ошибка выделения памяти");
            exit(0); // Завершение работы
        }
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
        
    }
    // Если элемент больше чем значение текущего узла
    if (data > root->data) {
        // Рекурсивный вызов с правым узлом
        root->right = CreateTree(root->right, data);
    }
    else {
        // Рекурсивный вызов с левым узлом
        root->left = CreateTree(root->left, data);
    }
    return root; // Возврат узла
}

// Функция вывода бинарного дерева
void print_tree(struct Node* root, int l) {
    // Если дерево пустое
    if (root == NULL) {
        return; // То конец
    }
    // Вывод левого поддерева
    print_tree(root->left, l + 1);

    for (int i = 0; i < l; i++) {
        printf("\t");
    }

    printf("%d\n", root->data);
    // Вывод правого поддерева
    print_tree(root->right, l + 1);
}

// Функции поиска элемента в бинарном дереве
struct Node* Search(struct Node* root, int target) {
    if (root == NULL || root->data == target) // Если дерево пустое или текущей элемент равен искомому
    {
        return root; // Указатель на текущей узел
    }
    if (target < root->data) // Если искомый элемент меньше текущего
    {
        return Search(root->left, target); // Поиск по левому поддереву
    }
    else {
        return Search(root->right, target); // Иначе поиск по правому поддереву
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    int D, target, start = 1;
    struct Node* root = NULL;

    printf("\t\t\t\t\t\t Enter -1 to stop building the tree: \n");
    while (start) {
        printf("Enter number (Please enter int value): ");
        scanf("%d", &D); // Заполнение дерева

        if (D == -1) // Если будет введено число -10, заполнение дерева прекратится
        {
            printf("Build finished \n\n");
            start = 0;
        }
        else
            root = CreateTree(root, D); // Иначе продолжается заполнение дерева
    }

    print_tree(root, 0); // Вывод в консоль элементов дерева

    printf("\n Which number to check for presence in the tree?: ");
    scanf("%d", &target); // Ввод числа для проверки на принадлежность дереву

    // Вывод о нахождение\отсутствие искомого элемента в дереве
    struct Node* result = Search(root, target);
    if (result != NULL) {
        printf("\n Number %d in a tree \n", target);
    }
    else {
        printf("\n Number %d isn't in a tree \n", target);
    }
    return 0;
}
