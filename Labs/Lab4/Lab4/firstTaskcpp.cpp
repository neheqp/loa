#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data; // ������ ������
    struct Node* left; // ����� ����
    struct Node* right; // ������ ����
};

// ������� �������� ������
struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) // ���� ������ �����
    {
        root = (struct Node*)malloc(sizeof(struct Node)); // ���������� ������
        if (root == NULL) // ���� ��������� ������ ����������
        {
            printf("������ ��������� ������");
            exit(0); // ���������� ������
        }
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
        
    }
    // ���� ������� ������ ��� �������� �������� ����
    if (data > root->data) {
        // ����������� ����� � ������ �����
        root->right = CreateTree(root->right, data);
    }
    else {
        // ����������� ����� � ����� �����
        root->left = CreateTree(root->left, data);
    }
    return root; // ������� ����
}

// ������� ������ ��������� ������
void print_tree(struct Node* root, int l) {
    // ���� ������ ������
    if (root == NULL) {
        return; // �� �����
    }
    // ����� ������ ���������
    print_tree(root->left, l + 1);

    for (int i = 0; i < l; i++) {
        printf("\t");
    }

    printf("%d\n", root->data);
    // ����� ������� ���������
    print_tree(root->right, l + 1);
}

// ������� ������ �������� � �������� ������
struct Node* Search(struct Node* root, int target) {
    if (root == NULL || root->data == target) // ���� ������ ������ ��� ������� ������� ����� ��������
    {
        return root; // ��������� �� ������� ����
    }
    if (target < root->data) // ���� ������� ������� ������ ��������
    {
        return Search(root->left, target); // ����� �� ������ ���������
    }
    else {
        return Search(root->right, target); // ����� ����� �� ������� ���������
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    int D, target, start = 1;
    struct Node* root = NULL;

    printf("\t\t\t\t\t\t Enter -1 to stop building the tree: \n");
    while (start) {
        printf("Enter number (Please enter int value): ");
        scanf("%d", &D); // ���������� ������

        if (D == -1) // ���� ����� ������� ����� -10, ���������� ������ �����������
        {
            printf("Build finished \n\n");
            start = 0;
        }
        else
            root = CreateTree(root, D); // ����� ������������ ���������� ������
    }

    print_tree(root, 0); // ����� � ������� ��������� ������

    printf("\n Which number to check for presence in the tree?: ");
    scanf("%d", &target); // ���� ����� ��� �������� �� �������������� ������

    // ����� � ����������\���������� �������� �������� � ������
    struct Node* result = Search(root, target);
    if (result != NULL) {
        printf("\n Number %d in a tree \n", target);
    }
    else {
        printf("\n Number %d isn't in a tree \n", target);
    }
    return 0;
}
