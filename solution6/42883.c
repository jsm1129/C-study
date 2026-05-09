#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// number_len은 입력 문자열 길이
char* solution(const char* number, int k) {

    int len = strlen(number);

    // 스택처럼 사용할 배열
    char* stack = (char*)malloc(len + 1);

    int top = -1;

    for (int i = 0; i < len; i++) {

        // 현재 숫자가 더 크면 이전 작은 숫자 제거
        while (top >= 0 && k > 0 && stack[top] < number[i]) {
            top--;
            k--;
        }

        stack[++top] = number[i];
    }

    // 아직 제거 못한 개수가 남아있으면 뒤에서 제거
    top -= k;

    // 결과 문자열 길이 설정
    stack[top + 1] = '\0';

    return stack;
}