#include <iostream>
#include <bitset>

using namespace std;
const int ROW = 9, COL = 9;

int sudoku[ROW][COL];
bool solved = false;
bitset<9> R[9], C[9], Grid[9]; // R[index].set(number)表示第index行已经填了number+1这个数字，C则表示第index列，Grid则表示第index个小9宫格

void set(int row, int col, int fill) {
    sudoku[row][col] = fill;
    R[row].set(fill - 1);
    C[col].set(fill - 1);
    Grid[row / 3 * 3 + col / 3].set(fill - 1);
}

void reset(int row, int col, int fill) {
    sudoku[row][col] = 0;
    R[row].reset(fill - 1);
    C[col].reset(fill - 1);
    Grid[row / 3 * 3 + col / 3].reset(fill - 1);
}

void init() {
    for (int row = 0; row < ROW; row ++)
        for (int col = 0; col < COL; col ++)
            if (sudoku[row][col] != 0)
                set(row, col, sudoku[row][col]);
}

void dfs(int row, int col) {
    // 递归边界
    if (row == ROW) {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                cout << sudoku[i][j] << ' ';
            }
            cout << endl;
        }
        solved = true;
        return;
    }
    else if (col == COL) { // 填充完这一行
        dfs(row + 1, 0);
    }
    else if (sudoku[row][col] != 0) { // 原先已经填充了数字
        dfs(row, col + 1);
    }
    else {
        bitset<9> consider = R[row] | C[col] | Grid[row / 3 * 3 + col / 3]; // 其中为0的位置即当前可以考虑填充的数
        for (int i = 0; i < 9; i++) {
            if (consider[i] == 0) {
                set(row, col, i + 1);
                dfs(row, col + 1);
                if (solved) return;
                reset(row, col, i + 1); // 恢复现场
            }
        }
    }
}

void solve() {
    init();
    dfs(0, 0);
}

int main() {
    for (int row = 0; row < ROW; row ++)
        for (int col = 0; col < COL; col ++)
            cin >> sudoku[row][col];
    solve();
    return 0;
}