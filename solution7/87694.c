#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define MAX 102

typedef struct {
    int x;
    int y;
    int dist;
} Node;

int map[MAX][MAX];
int visited[MAX][MAX];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int solution(int** rectangle, size_t rectangle_rows, size_t rectangle_cols,
             int characterX, int characterY, int itemX, int itemY) {
    
    memset(map, 0, sizeof(map));
    memset(visited, 0, sizeof(visited));

    // 좌표 2배 확대
    characterX *= 2;
    characterY *= 2;
    itemX *= 2;
    itemY *= 2;

    // 1. 직사각형 전체 영역을 1로 칠함
    for (int i = 0; i < rectangle_rows; i++) {
        int x1 = rectangle[i][0] * 2;
        int y1 = rectangle[i][1] * 2;
        int x2 = rectangle[i][2] * 2;
        int y2 = rectangle[i][3] * 2;

        for (int y = y1; y <= y2; y++) {
            for (int x = x1; x <= x2; x++) {
                map[y][x] = 1;
            }
        }
    }

    // 2. 내부 영역은 다시 0으로 지움
    // 최종적으로 테두리만 1로 남게 됨
    for (int i = 0; i < rectangle_rows; i++) {
        int x1 = rectangle[i][0] * 2;
        int y1 = rectangle[i][1] * 2;
        int x2 = rectangle[i][2] * 2;
        int y2 = rectangle[i][3] * 2;

        for (int y = y1 + 1; y < y2; y++) {
            for (int x = x1 + 1; x < x2; x++) {
                map[y][x] = 0;
            }
        }
    }

    // BFS 큐
    Node queue[MAX * MAX];
    int front = 0;
    int rear = 0;

    queue[rear++] = (Node){characterX, characterY, 0};
    visited[characterY][characterX] = 1;

    while (front < rear) {
        Node cur = queue[front++];

        // 아이템 위치 도착
        if (cur.x == itemX && cur.y == itemY) {
            return cur.dist / 2;
        }

        // 상하좌우 탐색
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            // 범위 밖이면 제외
            if (nx < 0 || ny < 0 || nx >= MAX || ny >= MAX)
                continue;

            // 테두리이고 아직 방문하지 않은 곳만 이동
            if (map[ny][nx] == 1 && visited[ny][nx] == 0) {
                visited[ny][nx] = 1;
                queue[rear++] = (Node){nx, ny, cur.dist + 1};
            }
        }
    }

    return 0;
}