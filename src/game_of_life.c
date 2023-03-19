#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 25
#define WIDTH 80

void init_board(int (*board)[WIDTH]);
void print(int (*board)[WIDTH]);
int count_neighbors(int i, int j, int (*board)[WIDTH]);
void update_board(int (*board)[WIDTH]);
int cycle(int (*board)[WIDTH]);

int main() {
    int board[HEIGHT][WIDTH];
    init_board(board);
    FILE *drugoe = freopen("/dev/tty", "r", stdin);
    if (drugoe == NULL) printf("Fatal");
    int n;
    scanf("%d", &n);
    while (cycle(board) == 0) {
        print(board);
        update_board(board);
        usleep(n);
    }

    return 0;
}

void init_board(int (*data)[WIDTH]) {
    char ch;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            scanf("%c", &ch);
            if (ch == '*')
                data[i][j] = 1;
            else if (ch == '.')
                data[i][j] = 0;
            else
                --j;
        }
    }
}

void print(int (*board)[WIDTH]) {
    system("clear");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j] == 1 ? '*' : ' ');
        }
        printf("\n");
    }
}

int count_neighbors(int i, int j, int (*board)[WIDTH]) {
    int count = 0;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue;
            int neighbor_x = i + x;
            int neighbor_y = j + y;
            if (neighbor_x >= 0 && neighbor_x < HEIGHT && neighbor_y >= 0 && neighbor_y < WIDTH) {
                count += board[neighbor_x][neighbor_y];
            } else {
                if (neighbor_x == HEIGHT) neighbor_x = 0;
                if (neighbor_x == -1) neighbor_x = HEIGHT - 1;
                if (neighbor_y == WIDTH) neighbor_y = 0;
                if (neighbor_y == -1) neighbor_y = WIDTH - 1;
                count += board[neighbor_x][neighbor_y];
            }
        }
    }
    return count;
}

void update_board(int (*board)[WIDTH]) {
    int new_board[HEIGHT][WIDTH];
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            int state = board[i][j];
            int neighbors = count_neighbors(i, j, board);
            if (state == 0 && neighbors == 3) {
                new_board[i][j] = 1;
            } else if (state == 1 && (neighbors < 2 || neighbors > 3)) {
                new_board[i][j] = 0;
            } else {
                new_board[i][j] = state;
            }
        }
    }
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            board[i][j] = new_board[i][j];
        }
    }
}

int cycle(int board[][WIDTH]) {
    int t = 0;
    for (int i = 0; i < HEIGHT && !t; i++) {
        for (int j = 0; j < WIDTH && !t; j++) {
            if (board[i][j] == '*') {
                t = 1;
            }
        }
    }
    return t;
}
