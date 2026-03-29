#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int** sizes, size_t sizes_rows, size_t sizes_cols) {
    int max_w = 0; // 가로 최대값
    int max_h = 0; // 세로 최대값
    
    for (int i = 0; i < sizes_rows; i++) {
        int w = sizes[i][0];
        int h = sizes[i][1];
        
        // 각 명함을 긴 변이 가로가 되도록 회전
        if (w < h) {
            int temp = w;
            w = h;
            h = temp;
        }
        
        // 전체 명함 중 가장 큰 가로, 세로 값 찾기
        if (w > max_w) max_w = w;
        if (h > max_h) max_h = h;
    }
    
    // 모든 명함을 담을 수 있는 최소 지갑 크기
    return max_w * max_h;
}