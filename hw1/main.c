#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 判斷是否為字母或底線 (用於 ID 的開頭)
int is_start_id(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

// 判斷是否為字母、數字或底線 (用於 ID 的後續部分)
int is_id_body(char c) {
    return is_start_id(c) || (c >= '0' && c <= '9');
}

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

// 關鍵字比對邏輯
void print_token(char *s) {
    if (strcmp(s, "int") == 0) printf("%s: TYPE_TOKEN\n", s);
    else if (strcmp(s, "main") == 0) printf("%s: MAIN_TOKEN\n", s);
    else if (strcmp(s, "if") == 0) printf("%s: IF_TOKEN\n", s);
    else if (strcmp(s, "else") == 0) printf("%s: ELSE_TOKEN\n", s);
    else if (strcmp(s, "while") == 0) printf("%s: WHILE_TOKEN\n", s);
    else printf("%s: ID_TOKEN\n", s);
}

int main() {
    
    FILE *fp = fopen(__FILE__, "r"); 
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int c;
    while ((c = fgetc(fp)) != EOF) {
        // 1. 忽略空白、換行與定位符
        if (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            continue;
        }

        // 2. 處理標識符 (ID) 與關鍵字 (Keywords)
        // 邏輯：首字不能是數字
        if (is_start_id(c)) {
            char buf[128];
            int i = 0;
            buf[i++] = (char)c;
            while ((c = fgetc(fp)) != EOF && is_id_body(c)) {
                if (i < 127) buf[i++] = (char)c;
            }
            buf[i] = '\0';
            ungetc(c, fp); // 將多讀的字元退回
            print_token(buf);
        }

        // 3. 處理數字 (Number)
        else if (is_digit(c)) {
            char buf[128];
            int i = 0;
            buf[i++] = (char)c;
            while ((c = fgetc(fp)) != EOF && is_digit(c)) {
                if (i < 127) buf[i++] = (char)c;
            }
            buf[i] = '\0';
            ungetc(c, fp);
            printf("%s: LITERAL_TOKEN\n", buf);
        }

        // 4. 處理關係運算子 (Relop) 與指派 (=)
        else if (c == '=') {
            int next = fgetc(fp);
            if (next == '=') printf("==: EQUAL_TOKEN\n");
            else {
                ungetc(next, fp);
                printf("=: ASSIGN_TOKEN\n");
            }
        }
        else if (c == '>') {
            int next = fgetc(fp);
            if (next == '=') printf(">=: GREATEREQUAL_TOKEN\n");
            else {
                ungetc(next, fp);
                printf(">: GREATER_TOKEN\n");
            }
        }
        else if (c == '<') {
            int next = fgetc(fp);
            if (next == '=') printf("<=: LESSEQUAL_TOKEN\n");
            else {
                ungetc(next, fp);
                printf("<: LESS_TOKEN\n");
            }
        }

        // 5. 處理單一字元符號
        else if (c == '+') printf("+: PLUS_TOKEN\n");
        else if (c == '-') printf("-: MINUS_TOKEN\n");
        else if (c == '(') printf("(: LEFTPAREN_TOKEN\n");
        else if (c == ')') printf("): REFTPAREN_TOKEN\n");
        else if (c == '{') printf("{: LEFTBRACE_TOKEN\n");
        else if (c == '}') printf("}: REFTBRACE_TOKEN\n");
        else if (c == ';') printf(";: SEMICOLON_TOKEN\n");
        else if (c == ':') printf(":: COLON_TOKEN\n");
    }

    fclose(fp);
    return 0;
}