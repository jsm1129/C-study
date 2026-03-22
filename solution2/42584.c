#include <stdio.h>
#include <stdlib.h>

// prices_len은 배열 prices의 길이
int* solution(int prices[], size_t prices_len) {
    int* answer = (int*)malloc(sizeof(int) * prices_len);
    int* stack = (int*)malloc(sizeof(int) * prices_len);  // 인덱스 저장용 스택
    int top = -1;

    for (int i = 0; i < prices_len; i++) {
        // 현재 가격이 더 작으면 가격이 떨어진 시점 처리
        while (top >= 0 && prices[stack[top]] > prices[i]) {
            int idx = stack[top--];
            answer[idx] = i - idx;
        }

        // 현재 인덱스를 스택에 저장
        stack[++top] = i;
    }

    // 끝까지 가격이 안 떨어진 경우 처리
    while (top >= 0) {
        int idx = stack[top--];
        answer[idx] = prices_len - 1 - idx;
    }

    free(stack);
    return answer;
}