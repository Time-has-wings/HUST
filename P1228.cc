#include <iostream>

using namespace std;
int K, X, Y;

// 原理:将一个[2^k, 2^k]的方格视为四个[2^(k-1), 2^(k-1)]的方格，此时由题意，必有一个小方格中出现一个点被占据，
// 故而我们需要为其他三个小方格也制造一个被占据的点，由此将一个问题转化为四个子问题
void solve(pair<int, int>LeftTop, pair<int, int>occupy, int power) {
    // 以LeftTop为左上角，occupy为已经占据的位置，power为2的幂次方
    if (power == 0) return; // 递归边界
    int RowMid = LeftTop.first + (1 << (power - 1)), ColMid = LeftTop.second + (1 << (power - 1));
    if (occupy.first < RowMid && occupy.second < ColMid) { // 原先occupy在左上方格
        cout << RowMid << " " << ColMid << " 1" << endl;
        solve(LeftTop, occupy, power - 1);
        solve({RowMid, LeftTop.second}, {RowMid, ColMid - 1}, power - 1);
        solve({LeftTop.first, ColMid}, {RowMid - 1, ColMid}, power - 1);
        solve({RowMid, ColMid}, {RowMid, ColMid}, power - 1);
    }
    else if (occupy.first >= RowMid && occupy.second < ColMid) { // 原先occupy在右上方格
        cout << RowMid - 1 << " " << ColMid << " 3" << endl;
        solve(LeftTop, {RowMid - 1, ColMid - 1}, power - 1);
        solve({RowMid, LeftTop.second}, occupy, power - 1);
        solve({LeftTop.first, ColMid}, {RowMid - 1, ColMid}, power - 1);
        solve({RowMid, ColMid}, {RowMid, ColMid}, power - 1);
    }
    else if (occupy.first < RowMid && occupy.second >= ColMid) { // 原先occupy在左下方格
        cout << RowMid << " " << ColMid - 1 << " 2" << endl;
        solve(LeftTop, {RowMid - 1, ColMid - 1}, power - 1);
        solve({RowMid, LeftTop.second}, {RowMid, ColMid - 1}, power - 1);
        solve({LeftTop.first, ColMid}, occupy, power - 1);
        solve({RowMid, ColMid}, {RowMid, ColMid}, power - 1);
    }
    else { // 原先occupy在右下方格
        cout << RowMid - 1 << " " << ColMid - 1 << " 4" << endl;
        solve(LeftTop, {RowMid - 1, ColMid - 1}, power - 1);
        solve({RowMid, LeftTop.second}, {RowMid, ColMid - 1}, power - 1);
        solve({LeftTop.first, ColMid}, {RowMid - 1, ColMid}, power - 1);
        solve({RowMid, ColMid}, occupy, power - 1);
    }
}

int main() {
    cin >> K >> X >> Y;
    solve({1, 1}, {X, Y}, K);
    return 0;
}