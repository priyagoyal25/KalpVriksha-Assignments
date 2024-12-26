#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
int evaluateExpression(const char* expr, int len);
int isValidExpression(const char* expr);
int precedence(char op);
int applyOperation(int a, int b, char op);

int main() {
    char input[100];
    printf("Enter an expression: ");
    fgets(input, sizeof(input), stdin);

    // Remove trailing newline if it exists
    int len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // Validate the input expression
    if (!isValidExpression(input)) {
        printf("Error: Invalid expression.\n");
        return 0;
    }

    int result = evaluateExpression(input, len);

    if (result == 1) {
        printf("Error: Division by zero.\n");
    } else {
        printf("Result: %d\n", result);
    }

    return 0;
}

// Check if the expression is valid
int isValidExpression(const char* expr) {
    for (int i = 0; expr[i] != '\0'; i++) {
        // if the char is not digit, space or any operator then invalid character
        if (!isdigit(expr[i]) && !isspace(expr[i]) && expr[i] != '+' &&
            expr[i] != '-' && expr[i] != '*' && expr[i] != '/') {
            return 0; // Invalid character
        }
    }
    return 1; // Valid expression
}

// Determine operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Apply an operation to two operands
int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : -1; // Return -1 for division by zero
    }
    return 0;
}

// Evaluate the mathematical expression
int evaluateExpression(const char* expr, int len) {
    int values[100]; // Stack for numbers
    char ops[100];   // Stack for operators
    int valTop = -1; // Values stack pointer
    int opsTop = -1; // Operators stack pointer

    for (int i = 0; expr[i] != '\0'; i++) {
        // Skip whitespaces
        if (isspace(expr[i])) continue;

        // If the current character is a number
        if (isdigit(expr[i])) {
            int val = 0;

            // Extract the full number
            while (i < len && isdigit(expr[i])) {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            i--; // Step back since the loop advances an extra time
            values[++valTop] = val;
        }
        // If the current character is an operator
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (opsTop != -1 && precedence(ops[opsTop]) >= precedence(expr[i])) {
                int b = values[valTop--];
                int a = values[valTop--];
                char op = ops[opsTop--];

                if (op == '/' && b == 0) {
                    return 1; // Division by zero error
                }

                values[++valTop] = applyOperation(a, b, op);
            }
            ops[++opsTop] = expr[i];
        } 
    }

    // Apply remaining operators to remaining values
    while (opsTop != -1) {
        int b = values[valTop--];
        int a = values[valTop--];
        char op = ops[opsTop--];

        if (op == '/' && b == 0) {
            return 1; // Division by zero error
        }

        values[++valTop] = applyOperation(a, b, op);
    }

    return values[valTop]; // The final result
}
