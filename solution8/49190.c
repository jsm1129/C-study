#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 400009

// 방문한 정점 저장용 구조체
typedef struct Node {
    int x, y;
    struct Node* next;
} Node;

// 지나간 간선 저장용 구조체
typedef struct Edge {
    int x1, y1, x2, y2;
    struct Edge* next;
} Edge;

Node* visited[HASH_SIZE];
Edge* edges[HASH_SIZE];

// 0~7번 방향 이동값
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

// 정점 좌표를 해시값으로 변환
int hashNode(int x, int y) {
    long long h = (long long)(x + 200000) * 1000003 + (y + 200000);
    if (h < 0) h = -h;
    return h % HASH_SIZE;
}

// 간선 정보를 해시값으로 변환
int hashEdge(int x1, int y1, int x2, int y2) {
    long long h = (long long)(x1 + 200000) * 31
                + (long long)(y1 + 200000) * 37
                + (long long)(x2 + 200000) * 41
                + (long long)(y2 + 200000) * 43;

    if (h < 0) h = -h;
    return h % HASH_SIZE;
}

// 이미 방문한 정점인지 확인
int isVisited(int x, int y) {
    int h = hashNode(x, y);
    Node* cur = visited[h];

    // 같은 해시값에 여러 좌표가 있을 수 있으므로 연결 리스트 탐색
    while (cur) {
        if (cur->x == x && cur->y == y)
            return 1;

        cur = cur->next;
    }

    return 0;
}

// 방문한 정점 저장
void addVisited(int x, int y) {
    int h = hashNode(x, y);

    Node* node = (Node*)malloc(sizeof(Node));

    node->x = x;
    node->y = y;

    // 기존 리스트 앞에 새 노드 추가
    node->next = visited[h];
    visited[h] = node;
}

// 이미 지나간 간선인지 확인
int hasEdge(int x1, int y1, int x2, int y2) {
    int h = hashEdge(x1, y1, x2, y2);
    Edge* cur = edges[h];

    // 같은 해시값에 여러 간선이 있을 수 있으므로 연결 리스트 탐색
    while (cur) {
        if (cur->x1 == x1 && cur->y1 == y1 &&
            cur->x2 == x2 && cur->y2 == y2)
            return 1;

        cur = cur->next;
    }

    return 0;
}

// 지나간 간선 저장
void addEdge(int x1, int y1, int x2, int y2) {
    int h = hashEdge(x1, y1, x2, y2);

    Edge* edge = (Edge*)malloc(sizeof(Edge));

    edge->x1 = x1;
    edge->y1 = y1;
    edge->x2 = x2;
    edge->y2 = y2;

    // 기존 리스트 앞에 새 간선 추가
    edge->next = edges[h];
    edges[h] = edge;
}

int solution(int arrows[], size_t arrows_len) {
    int answer = 0;

    int x = 0;
    int y = 0;

    // 시작점은 이미 방문한 정점으로 처리
    addVisited(x, y);

    for (int i = 0; i < arrows_len; i++) {
        int dir = arrows[i];

        /*
            대각선끼리 교차하는 경우를 처리하기 위해
            한 번의 이동을 두 번으로 나누어 이동한다.
            이렇게 하면 중간 교차점도 정점으로 인식된다.
        */
        for (int step = 0; step < 2; step++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            /*
                이미 방문한 정점에 도착했는데,
                현재 간선이 처음 지나가는 간선이면
                새로운 닫힌 영역, 즉 방이 하나 생긴다.
            */
            if (isVisited(nx, ny)) {
                if (!hasEdge(x, y, nx, ny)) {
                    answer++;
                }
            } else {
                // 처음 도착한 정점이면 방문 처리만 한다
                addVisited(nx, ny);
            }

            /*
                간선은 양방향으로 저장한다.
                A -> B로 지나간 길은 B -> A로 다시 지나가도
                이미 지나간 같은 길로 봐야 하기 때문이다.
            */
            if (!hasEdge(x, y, nx, ny)) {
                addEdge(x, y, nx, ny);
                addEdge(nx, ny, x, y);
            }

            // 현재 위치를 다음 위치로 갱신
            x = nx;
            y = ny;
        }
    }

    return answer;
}