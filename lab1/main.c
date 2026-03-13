#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    struct Node *next;
} Node;

Node* find(Node *head, char c) {
    Node *cur = head;

    while (cur != NULL) {
        if (cur->ch == c)
            return cur;

        cur = cur->next;
    }

    return NULL;
}

Node* insert(Node *head, char c) {

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->ch = c;
    newNode->next = NULL;

    if (head == NULL)
        return newNode;

    Node *cur = head;

    while (cur->next != NULL)
        cur = cur->next;

    cur->next = newNode;

    return head;
}

int main() {

    FILE *fp = fopen(__FILE__, "r");

    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    Node *head = NULL;
    char c;

    while ((c = fgetc(fp)) != EOF) {

        Node *node = find(head, c);

        if (node == NULL) {
            head = insert(head, c);
        }
    }

    fclose(fp);

    Node *cur = head;

    while (cur != NULL) {

        if (cur->ch == '\n')
            printf("\\n");
        else if (cur->ch == '\t')
            printf("\\t");
        else
            printf("%c", cur->ch);

        if (cur->next != NULL)
            printf(",");

        cur = cur->next;
    }

    printf("\n");

    return 0;
}