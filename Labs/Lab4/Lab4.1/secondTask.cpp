#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) {
        root = (struct Node*)malloc(sizeof(struct Node));
        if (root == NULL) {
            printf("Memory allocation error");
            exit(0);
        }
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

    if (data > root->data) {
        root->right = CreateTree(root->right, data);
    }
    else {
        root->left = CreateTree(root->left, data);
    }
    return root;
}

void print_tree(struct Node* root, int l) {
    if (root == NULL) {
        return;
    }

    print_tree(root->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf("\");
    }

    printf("%d\n", root->data);
    print_tree(root->left, l + 1);
}

// Функция подсчета количества входов определенного числа в дерево
int CountOccurrences(struct Node* root, int target) {
    // Если в дереве нет нужного элемента
    if (root == NULL) {
        return 0; // Возврат 0
    }

    if (root->data == target) // Если нужный элемент найден
    {
        // Увеличиваем счётчик и проходимся по правому и левому поддереву
        return 1 + CountOccurrences(root->left, target) + CountOccurrences(root->right, target);
    }
    else if (target < root->data) // Если искомый элемент меньше текущего
    {
        return CountOccurrences(root->left, target); // То ищем его в левом поддереве
    }
    else // Иначе
    {
        return CountOccurrences(root->right, target); // Ищем его в правом поддереве
    }
}

int main() {
    int D, start = 1;

    struct Node* root = NULL;
    printf("\t\t\t\t\t\t Enter -1 to stop building the tree: \n");
    while (start) {
        printf("Enter number (Please enter int number): ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Build was finished\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, D);
    }

    print_tree(root, 0);

    printf("\nEnter a value for counting occurrences: ");
    scanf("%d", &D); // Ввод искомого числа

    int count = CountOccurrences(root, D); // Счетчик

    printf("\nNumber %d meets in a tree %d times\n", D, count);

    return 0;
}
