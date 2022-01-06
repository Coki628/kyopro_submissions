#include "../macros.hpp"

// メモ
// ・型は選べるようにしてあるけど、整数型入れると除算とかバグる。実数での仕様が前提。
// ・基本的に全部有理数のはずなので、Fractionクラス作ればよさそうだが面倒でやってない。

// 掃き出し法
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
