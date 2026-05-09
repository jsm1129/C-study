#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int graph[101][101];
bool visited[101];

// DFS로 연결된 송전탑 개수 구하기
int dfs(int node, int n) {
    visited[node] = true;
    int count = 1;

    for (int i = 1; i <= n; i++) {

        // 연결되어 있고 아직 방문 안 했다면 탐색
        if (graph[node][i] && !visited[i]) {
            count += dfs(i, n);
        }
    }

    return count;
}

int solution(int n, int** wires, size_t wires_rows, size_t wires_cols) {

    int answer = n;

    // 전선을 하나씩 끊어보기
    for (int cut = 0; cut < wires_rows; cut++) {

        // 그래프와 방문 배열 초기화
        for (int i = 1; i <= n; i++) {

            visited[i] = false;

            for (int j = 1; j <= n; j++) {
                graph[i][j] = 0;
            }
        }

        // cut번째 전선을 제외하고 연결
        for (int i = 0; i < wires_rows; i++) {

            if (i == cut) continue;

            int a = wires[i][0];
            int b = wires[i][1];

            graph[a][b] = 1;
            graph[b][a] = 1;
        }

        // 한쪽 전력망 크기 계산
        int cnt1 = dfs(1, n);

        // 나머지 전력망 크기
        int cnt2 = n - cnt1;

        // 두 전력망 차이
        int diff = abs(cnt1 - cnt2);

        // 최소값 갱신
        if (diff < answer) {
            answer = diff;
        }
    }

    return answer;
}