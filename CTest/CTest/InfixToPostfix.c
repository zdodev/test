#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ListBaseStack.h"

int getOpPrec(char op) {
    switch (op) {
        case '*':
        case '/':
            return 5;
        case '+':
        case '-':
            return 3;
    }
    
    return -1;
}

int whoPrecOp(char op1, char op2) {
    int op1Prec = getOpPrec(op1);
    int op2Prec = getOpPrec(op2);
    
    if (op1Prec > op2Prec)
        return 1;
    else if (op1Prec < op2Prec)
        return -1;
    else
        return 0;
}

void convToRPNExp(char exp[]) {
    // exp는 수식
    Stack stack;
    int expLen = strlen(exp);
    char *convExp = (char *)malloc(expLen + 1);
    
    int i, idx = 0;
    char tok, popOp;
    
    memset(convExp, 0, sizeof(char)*expLen + 1);
    StackInit(&stack);
    
    for (i = 0; i < expLen; i++) {
        tok = exp[i]; // exp로 전달된 수식을 한 문자씩 tok에 저장
        
        if (isdigit(tok)) {
            convExp[idx++] = tok;
        } else {
            switch (tok) {
                case '+':
                case '-':
                case '*':
                case '/':
                    // 스택이 비어있지 않고 스택에 저장된 연산자 우선순위가 같거나 높으면 꺼내어 저장
                    while (!SIsEmpty(&stack) && whoPrecOp(SPeek(&stack), tok) >= 0)
                        convExp[idx++] = SPop(&stack);
                    // 아니면 연산자 스택에 저장
                    SPush(&stack, tok);
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    while (!SIsEmpty(&stack)) {
        convExp[idx++] = SPop(&stack);
    }
    
    strcpy(exp, convExp);
    free(convExp);
}
