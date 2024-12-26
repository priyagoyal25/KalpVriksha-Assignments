#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LEN 50

int get_precedence(char operator_symbol) {
    if (operator_symbol == '+' || operator_symbol == '-') return 1;
    if (operator_symbol == '*' || operator_symbol == '/') return 2;
    return 0;
}

int apply_operation(int first_number, int second_number, char operator_symbol) {
    switch (operator_symbol) {
        case '+': return first_number + second_number;
        case '-': return first_number - second_number;
        case '*': return first_number * second_number;
        case '/':
            if (second_number == 0) {
                printf("Error: Division by zero\n");
                return 0;
            }
            return first_number / second_number;
        default: return 0;
    }
}


int evaluate_expression(const char *expression, int *error_flag) {
    int numbers[LEN], numbers_top = -1;
    char operators[LEN], operators_top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        char current = expression[i];

        if (isspace(current)) continue;

        if (current == '-' && (i == 0 || strchr("+-*/", expression[i - 1]) != NULL)) {
            i++;
            if (!isdigit(expression[i])) {
                *error_flag = 2;
                return 0;
            }
            int number = 0;
            while (isdigit(expression[i])) {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            numbers[++numbers_top] = -number;
            continue;
        }

        if (isdigit(current)) {
            int number = 0;
            while (isdigit(expression[i])) {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            numbers[++numbers_top] = number;
            continue;
        }

        if (current == '+' || current == '-' || current == '*' || current == '/') {
            while (operators_top >= 0 && get_precedence(operators[operators_top]) >= get_precedence(current)) {
                char op = operators[operators_top--];
                int num2 = numbers[numbers_top--];
                int num1 = numbers[numbers_top--];

                if (op == '/' && num2 == 0) {
                    *error_flag = 1;
                    return 0;
                }

                numbers[++numbers_top] = apply_operation(num1, num2, op);
            }
            operators[++operators_top] = current;
            continue;
        }

        *error_flag = 2;
        return 0;
    }

    while (operators_top >= 0) {
        char op = operators[operators_top--];
        int num2 = numbers[numbers_top--];
        int num1 = numbers[numbers_top--];

        if (op == '/' && num2 == 0) {
            *error_flag = 1;
            return 0;
        }

        numbers[++numbers_top] = apply_operation(num1, num2, op);
    }

    return numbers[numbers_top];
}

int main() {
    char expression[LEN];
    printf("Enter a mathematical expression: ");
    fgets(expression, LEN, stdin);

    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }

    int error_flag = 0;
    int result = evaluate_expression(expression, &error_flag);

    if (error_flag == 1) {
        printf("Error: Division by zero.\n");
    } else if (error_flag == 2) {
        printf("Error: Invalid expression.\n");
    } else {
        printf("Result: %d\n", result);
    }

    return 0;
}
