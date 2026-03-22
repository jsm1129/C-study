#include <stdbool.h>
#include <stdlib.h>

bool solution(const char* s) {
    int balance = 0;  // 열린 괄호 개수 추적

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            balance++;   // '(' 만나면 증가
        } else {
            balance--;   // ')' 만나면 감소
        }

        // 닫는 괄호가 더 많아지는 순간 올바르지 않음
        if (balance < 0) {
            return false;
        }
    }

    // 모든 괄호가 짝을 이뤄야 함
    return (balance == 0);
}