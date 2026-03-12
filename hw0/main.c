#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ch;
    int count;
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
    newNode->count = 1;
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

    FILE *fp = fopen(__FILE__, "r"); //represents the current file
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    Node *head = NULL;
    char c;

    while ((c = fgetc(fp)) != EOF) {

        if (c == ' ' || c == '\n')   // skip spaces and newlines
            continue;

        Node *node = find(head, c);

        if (node != NULL) {
            node->count++;
        } else {
            head = insert(head, c);
        }
    }

    fclose(fp);

    Node *cur = head;
    while (cur != NULL) {
        printf("%c : %d\n", cur->ch, cur->count); 
        cur = cur->next;
    }

    return 0;
}