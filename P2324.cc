#include <iostream>

using namespace std;
const int dx[] = {1, 1, -1, -1, 2, 2, -2, -2}, dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
int T;
char input[5][5];

struct Chess {
    char state[5][5] = {
        {'1', '1', '1', '1', '1'},
        {'0', '1', '1', '1', '1'},
        {'0', '0', '*', '1', '1'},
        {'0', '0', '0', '0', '1'},
        {'0', '0', '0', '0', '0'}
    };
    int step = 0, X = 2, Y = 2;
    bool solved = false;

    int diff() {
        int cnt = 0;
        for (int i = 0; i < 5; i ++)
            for (int j = 0; j < 5; j++)
                if (state[i][j] != input[i][j] && state[i][j] != '*')
                    cnt ++;
        return cnt;
    }

    void Goto(int x, int y) {
        state[X][Y] = state[x][y], state[x][y] = '*';
        X = x, Y = y;
        step ++;
    }

    void GoBack(int x, int y) {
        state[X][Y] = state[x][y], state[x][y] = '*';
        X = x, Y = y;
        step --;
    }
} chess;

void DFS(int MAX) {
    if (chess.diff() == 0) {
        cout << chess.step << endl;
        chess.solved = true;
        return;
    }
    for (int i = 0; i < 8; i++) {
        int X = chess.X, Y = chess.Y;
        int x = X + dx[i], y = Y + dy[i];
        if (x < 0 || x > 4 || y < 0 || y > 4)
            continue;
        chess.Goto(x, y);
        if (chess.step + chess.diff() <= MAX) 
            DFS(MAX);
        chess.GoBack(X, Y); // 恢复现场
        if (chess.solved)
            return;
    }
}

int main() {
    cin >> T;
    while (T --) {
        chess.solved = false;
        for (int i = 0; i < 5; i++) 
            for (int j = 0; j < 5; j++)
                cin >> input[i][j];
        for (int depth = 0; depth <= 15; depth ++) {
            DFS(depth);
            if (chess.solved)
                break;
        }
        if (chess.solved == false)
            cout << -1 << endl;
    }
    return 0;
}