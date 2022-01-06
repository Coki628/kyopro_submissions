#include "../macros.hpp"

// メモ
// ・計算量：O(RC^2) これは行が10万あっても列がビットとか少ない時は通用するってこと。
// ・連立方程式の解ではない使い方もある。(zone2021_f) そういう時はextendedがfalseになる。

// 掃き出し法(2値用)
template<int BITLEN>
pair<int, vector<bitset<BITLEN>>> gauss_jordan(int N, int M, const vector<bitset<BITLEN>> &A, bool extended=true) {
    assert(N == A.size());
    auto res = A;
    int rank = 0;
    rep(col, M) {
        if (extended and col == M-1) break;
        int pivot = -1;
        rep(row, rank, N) {
            if (res[row][col]) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) continue;
        swap(res[rank], res[pivot]);
        rep(row, N) {
            if (row != rank and res[row][col]) {
                res[row] ^= res[rank];
            }
        }
        rank++;
    }
    // 解があるか確認
    rep(row, rank, N) {
        if (res[row][M-1]) {
            return {-1, vector<bitset<BITLEN>>()};
        }
    }
    return {rank, res};
}
