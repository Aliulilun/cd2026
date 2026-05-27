#include <stdio.h>
#include <string.h>

typedef enum {
    TOKEN_ONE,
    TOKEN_PLUS,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_ERROR
} TokenType;

char input[1000];
int pos = 0;

TokenType lookahead;

/* Scanner */

TokenType getNextToken() {

    while (input[pos] == ' ' || input[pos] == '\n' || input[pos] == '\t') {
        pos++;
    }

    char c = input[pos++];

    if (c == '1')
        return TOKEN_ONE;

    if (c == '+')
        return TOKEN_PLUS;

    if (c == '(')
        return TOKEN_LPAREN;

    if (c == ')')
        return TOKEN_RPAREN;

    if (c == '\0')
        return TOKEN_END;

    return TOKEN_ERROR;
}

/* Match Function */

void match(TokenType expected) {

    if (lookahead == expected) {
        lookahead = getNextToken();
    }
    else {
        printf("Syntax Error\n");
    }
}

/*
Grammar:

S  -> E S'
S' -> + S | epsilon
E  -> ( S ) | 1
*/

/* Parser Functions */

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

/* E -> ( S ) | 1 */

void parse_E() {

    if (lookahead == TOKEN_LPAREN) {

        printf("E -> ( S )\n");

        match(TOKEN_LPAREN);

        parse_S();

        match(TOKEN_RPAREN);
    }

    else if (lookahead == TOKEN_ONE) {

        printf("E -> 1\n");

        match(TOKEN_ONE);
    }

    else {

        printf("Syntax Error in E\n");
    }
}

int main() {

    printf("Input: ");

    scanf("%s", input);

    lookahead = getNextToken();

    parse_S();

    if (lookahead == TOKEN_END) {
        printf("Accepted\n");
    }
    else {
        printf("Syntax Error\n");
    }

    return 0;
}