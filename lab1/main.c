#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    struct Node *next;
} Node;

Node* append(Node *head, char c) {

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->ch = c;
    newNode->next = NULL;

    if (head == NULL)
        return newNode;

    Node *curr = head;

    while (curr->next != NULL)
        curr = curr->next;

    curr->next = newNode;

    return head;
}

void printList(Node *head) {

    Node *curr = head;

    while (curr != NULL) {

        if (curr->ch == '\n')
            printf("\\n");
        else if (curr->ch == '\t')
            printf("\\t");
        else
            printf("%c", curr->ch);

        if (curr->next != NULL)
            printf(",");

        curr = curr->next;
    }

    printf("\n");
}

int main() {

    FILE *fp = fopen("main.c", "r");

    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    Node *head = NULL;
    char c;

    while ((c = fgetc(fp)) != EOF) {
        head = append(head, c);
    }

    fclose(fp);

    printList(head);

    return 0;
}