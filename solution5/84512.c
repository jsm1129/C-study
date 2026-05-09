#include <stdio.h>
#include <string.h>

char words[5] = {'A', 'E', 'I', 'O', 'U'};
int answer = 0;
int count = 0;

// DFS로 모든 단어 탐색
void dfs(char* current, char* target, int depth) {

    // 현재 단어가 target이면 종료
    if (strcmp(current, target) == 0) {
        answer = count;
        return;
    }

    // 길이가 5면 더 이상 탐색 X
    if (depth == 5) return;

    // A, E, I, O, U 붙이기
    for (int i = 0; i < 5; i++) {

        current[depth] = words[i];
        current[depth + 1] = '\0';

        count++;

        dfs(current, target, depth + 1);

        // 이미 찾았으면 종료
        if (answer != 0) return;
    }
}

int solution(const char* word) {

    char current[6] = "";

    dfs(current, (char*)word, 0);

    return answer;
}