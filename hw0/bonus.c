#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ch;
    int count;
    struct Node *next;
} Node;

int main() {

    FILE *fp = fopen(__FILE__, "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    Node *head = NULL;
    Node *tail = NULL;

    Node *table[256] = {NULL};

    char c;

    while ((c = fgetc(fp)) != EOF) {

        if (c == ' ' || c == '\n')
            continue;

        Node *node = table[(unsigned char)c];

        if (node != NULL) {

            node->count++;

        } else {

            node = (Node*)malloc(sizeof(Node));
            node->ch = c;
            node->count = 1;
            node->next = NULL;

            table[(unsigned char)c] = node;

            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
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
// This implementation uses a hash table to store the counts of characters, which allows for O(1) average time complexity for lookups and insertions. The linked list is used to maintain the order of characters as they appear in the file.