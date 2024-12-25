#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VAR 26  


bool is_valid_expression(const char *expression) {
    int parentheses_count = 0;
    char last_char = '\0';

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        if (!(isalnum(ch) || ch == '(' || ch == ')' || ch == '&' || ch == '|' || ch == '~' || ch == '-' || ch == '>' || ch == ' ')) {
            return false;
        }

     
        if (ch == '(') parentheses_count++;
        if (ch == ')') parentheses_count--;

      
        if ((ch == '&' || ch == '|' || ch == '-' || ch == '>') && 
            (last_char == '\0' || last_char == '(' || last_char == '&' || last_char == '|' || last_char == '-' || last_char == '>')) {
            return false;
        }

        last_char = ch;
    }


    return parentheses_count == 0 && !(last_char == '&' || last_char == '|' || last_char == '-' || last_char == '>');
}

bool evaluate_expression(const char *expression, bool values[MAX_VAR]) {
    int stack[MAX_VAR];  
    int top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        if (ch == ' ') {
            continue;
        } else if (ch == '~') {
          
            bool operand = stack[top--];
            stack[++top] = !operand;
        } else if (ch == '&' || ch == '|') {
          
            bool right = stack[top--];
            bool left = stack[top--];
            if (ch == '&') {
                stack[++top] = left && right;
            } else if (ch == '|') {
                stack[++top] = left || right;
            }
        } else if (ch == '-' && expression[i + 1] == '>') {
            
            bool right = stack[top--];
            bool left = stack[top--];
            stack[++top] = !left || right;
            i++;  
        } else if (isalpha(ch)) {
         
            int index = ch - 'A';  
            stack[++top] = values[index];
        }
    }

    return stack[top];
}

int main() {
    char expression[256];
    bool values[MAX_VAR] = {false}; 
    char variables[MAX_VAR];         

  
    printf("Nhap bieu thuc logic (vd: (A & B) -> ~C): ");
    fgets(expression, sizeof(expression), stdin);

  
    expression[strcspn(expression, "\n")] = '\0';


    if (!is_valid_expression(expression)) {
        printf("Bieu thuc khong hop le!\n");
        return 1;
    }

    int var_count = 0;
    for (int i = 0; expression[i] != '\0'; i++) {
        if (isalpha(expression[i])) {
            char var = expression[i];
            int found = 0;

            for (int j = 0; j < var_count; j++) {
                if (variables[j] == var) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                variables[var_count++] = var;
            }
        }
    }

    printf("Nhap gia tri cho cac bien (True/False):\n");
    for (int i = 0; i < var_count; i++) {
        char input[10];
        while (1) {
            printf("%c = ", variables[i]);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';  

            if (strcmp(input, "True") == 0 || strcmp(input, "true") == 0) {
                values[variables[i] - 'A'] = true;
                break;
            } else if (strcmp(input, "False") == 0 || strcmp(input, "false") == 0) {
                values[variables[i] - 'A'] = false;
                break;
            } else {
                printf("Gia tri phai la True hoac False!\n");
            }
        }
    }

    bool result = evaluate_expression(expression, values);
    printf("Gia tri cua bieu thuc la: %s\n", result ? "True" : "False");

    return 0;
}

