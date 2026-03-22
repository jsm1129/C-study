#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 두 수를 문자열로 이어붙여 더 큰 쪽이 앞에 오도록 비교
int compare(const void* a, const void* b) {
    char ab[10], ba[10];

    // a+b, b+a 형태 생성
    sprintf(ab, "%d%d", *(int*)a, *(int*)b);
    sprintf(ba, "%d%d", *(int*)b, *(int*)a);

    // 더 큰 조합이 앞으로 오도록 정렬 (내림차순)
    return strcmp(ba, ab);
}

char* solution(int numbers[], size_t numbers_len) {
    // 사용자 정의 기준으로 정렬
    qsort(numbers, numbers_len, sizeof(int), compare);

    // 가장 큰 값이 0이면 전체가 0
    if (numbers[0] == 0) {
        char* answer = (char*)malloc(2);
        strcpy(answer, "0");
        return answer;
    }

    // 결과 문자열 공간 할당 (각 숫자 최대 4자리)
    char* answer = (char*)malloc(numbers_len * 4 + 1);
    answer[0] = '\0';

    char temp[5];
    for (size_t i = 0; i < numbers_len; i++) {
        // 숫자를 문자열로 변환 후 이어붙이기
        sprintf(temp, "%d", numbers[i]);
        strcat(answer, temp);
    }

    return answer;
}