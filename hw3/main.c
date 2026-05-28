#include <stdio.h>
#include <string.h>

typedef enum {
    TOKEN_NUM,
    TOKEN_PLUS,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_ERROR
} TokenType;

/* input buffer */

char input[1000];

/* current position */

int pos = 0;

/* lookahead token */

TokenType lookahead;

/* 判斷是否為數字 */

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

/* Scanner */

TokenType getNextToken() {

    /* skip whitespace */

    while (input[pos] == ' ' ||
           input[pos] == '\n' ||
           input[pos] == '\t') {
        pos++;
    }

    char c = input[pos];

    /* NUM */

    if (is_digit(c)) {

        while (is_digit(input[pos])) {
            pos++;
        }

        return TOKEN_NUM;
    }

    /* PLUS */

    if (c == '+') {
        pos++;
        return TOKEN_PLUS;
    }

    /* LEFT PAREN */

    if (c == '(') {
        pos++;
        return TOKEN_LPAREN;
    }

    /* RIGHT PAREN */

    if (c == ')') {
        pos++;
        return TOKEN_RPAREN;
    }

    /* END */

    if (c == '\0') {
        return TOKEN_END;
    }

    /* ERROR */

    pos++;

    return TOKEN_ERROR;
}

/* match function */

void match(TokenType expected) {

    if (lookahead == expected) {

        lookahead = getNextToken();
    }
    else {

        printf("Syntax Error\n");
    }
}

/*
Grammar

S  -> E S'
S' -> + S | epsilon
E  -> ( S ) | num
*/

void parse_S();
void parse_S_prime();
void parse_E();

/* S -> E S' */

void parse_S() {

    printf("S -> E S'\n");

    parse_E();

    parse_S_prime();
}

/* S' -> + S | epsilon */

void parse_S_prime() {

    if (lookahead == TOKEN_PLUS) {

        printf("S' -> + S\n");

        match(TOKEN_PLUS);

        parse_S();
    }
    else {

        printf("S' -> epsilon\n");
    }
}

/* E -> ( S ) | num */

void parse_E() {

    if (lookahead == TOKEN_LPAREN) {

        printf("E -> ( S )\n");

        match(TOKEN_LPAREN);

        parse_S();

        match(TOKEN_RPAREN);
    }

    else if (lookahead == TOKEN_NUM) {

        printf("E -> num\n");

        match(TOKEN_NUM);
    }

    else {

        printf("Syntax Error in E\n");
    }
}

int main() {

    printf("Input: ");

    scanf("%s", input);

    /* initialize lookahead */

    lookahead = getNextToken();

    /* start parsing */

    parse_S();

    /* check acceptance */

    if (lookahead == TOKEN_END) {

        printf("Accepted\n");
    }
    else {

        printf("Syntax Error\n");
    }

    return 0;
}