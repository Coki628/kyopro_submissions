/*
・ライブラリ：行列系
*/

#include "_tpl.cpp"


// 行列累乗
template<typename T>
struct MatPow {

    MatPow() {}

    vector<vector<T>> mat_dot(const vector<vector<T>> &A, const vector<vector<T>> &B) {
        int n1 = A.size();
        int n2 = A[0].size();
        int m2 = B[0].size();
        auto res = list2d(n1, m2, (T)0);
        rep(i, n1) {
            rep(k, n2) {
                if (A[i][k] == 0) continue;
                rep(j, m2) {
                    res[i][j] += A[i][k]*B[k][j];
                }
            }
        }
        return res;
    }

    vector<vector<T>> mat_pow(vector<vector<T>> mat, ll k) {
        int n = mat.size();
        auto res = list2d(n, n, (T)0);
        rep(i, n) {
            res[i][i] = 1;
        }
        while (k > 0) {
            if (k & 1) {
                res = mat_dot(res, mat);
            }
            mat = mat_dot(mat, mat);
            k >>= 1;
        }
        return res;
    }

    vector<T> solve(vector<vector<T>> mat, const vector<T> &_init, ll K) {
        int n = mat.size();
        auto init = list2d(n, 1, (T)0);
        rep(i, n) init[i][0] = _init[i];
        auto res = mat_pow(mat, K);
        res = mat_dot(res, init);
        vector<T> ret(n, 0);
        rep(i, n) ret[i] = res[i][0];
        return ret;
    }
};


// 掃き出し法 ※未verify
template<typename T>
vector<T> gauss_jordan(const vector<vector<T>> &A, const vector<T> &b) {
    int N = A.size();
    auto B = list2d<T>(N, N+1, 0);
    rep(i, N) {
        rep(j, N) {
            B[i][j] = A[i][j];
        }
    }
    // 行列Aの後ろにbを並べ同時に処理する
    rep(i, N) {
        B[i][N] = b[i];
    }

    rep(i, N) {
        // 注目している変数の係数の絶対値が大きい式をi番目に持ってくる
        int pivot = i;
        rep(j, i, N) {
            if (abs(B[j][i]) > abs(B[pivot][i])) {
                pivot = j;
            }
        }
        swap(B[i], B[pivot]);

        // 解がないか、一意でない
        if (abs(B[i][i]) < EPS) {
            return vector<T>();
        }
        // 注目している変数の係数を1にする
        rep(j, i+1, N+1) {
            B[i][j] /= B[i][i];
        }
        rep(j, N) {
            if (i != j) {
                // j番目の式からi番目の変数を消去
                rep(k, i+1, N+1) {
                    B[j][k] -= B[j][i] * B[i][k];
                }
            }
        }
    }

    vector<T> res(N);
    // 後ろに並べたbが解になる
    rep(i, N) {
        res[i] = B[i][N];
    }
    return res;
}

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
