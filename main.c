#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <assert.h>
#include <math.h>

double stack[256];
unsigned char stack_index = 0;

void            stack_reset() { stack_index = 0; }
unsigned char   stack_size()  { return stack_index; }
double          stack_peek()  { return stack[stack_index]; }

void stack_push(double val) {
    assert(stack_index < 255);
    stack[++stack_index] = val;
}
double stack_pop() {
    assert(stack_index > 0);
    return stack[stack_index--];
}

int main(int argc, char** argv) {

    char buf[256];
    regex_t regex_value, regex_operation;
    regcomp(&regex_value, "[0-9]+\\.?[0-9]*", REG_EXTENDED | REG_NOSUB);
    regcomp(&regex_operation, "[\\+\\-\\*\\/\\^]", REG_EXTENDED | REG_NOSUB);

    while(1) {
        stack_reset();
        putchar('>');
        fgets(buf, 256, stdin);

        for(char* token = strtok(buf, " "); token != NULL; token = strtok(NULL, " ")) {
            if(regexec(&regex_value, token, 0, NULL, 0) == 0) {
                stack_push(strtod(token, NULL));
            } else if(regexec(&regex_operation, token, 0, NULL, 0) == 0) {
                double rhs = stack_pop();
                double lhs = stack_pop();
                switch(token[0]) {
                    case '+': stack_push(lhs+rhs); break;
                    case '-': stack_push(lhs-rhs); break;
                    case '*': stack_push(lhs*rhs); break;
                    case '/': stack_push(lhs/rhs); break;
                    case '^': stack_push(pow(lhs,rhs)); break;
                }
            } else {
                printf("Giving Up: Unrecognised input: %s\n", token);
                stack_reset();
                break;
            }
        }
        if(stack_size() > 0) {
            printf(">> %f\n", stack_pop());
        }
    }
    return 0;
}
