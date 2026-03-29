#include <stdio.h>
#include <stdbool.h>

int maxCount = 0;     // 최대 탐험 가능한 던전 수
bool visited[8];      // 방문 여부 체크

// DFS로 모든 경우 탐색
void dfs(int k, int** dungeons, int n, int count) {
    
    // 현재까지 탐험한 개수로 최대값 갱신
    if (count > maxCount) {
        maxCount = count;
    }

    for (int i = 0; i < n; i++) {
        // 아직 방문 안했고, 최소 피로도 조건 만족
        if (!visited[i] && k >= dungeons[i][0]) {
            visited[i] = true;  // 방문 처리

            // 피로도 감소 후 다음 탐색
            dfs(k - dungeons[i][1], dungeons, n, count + 1);

            visited[i] = false; // 백트래킹 (다른 경우 위해 복구)
        }
    }
}

int solution(int k, int** dungeons, size_t dungeons_rows, size_t dungeons_cols) {
    
    dfs(k, dungeons, dungeons_rows, 0);

    return maxCount;
}