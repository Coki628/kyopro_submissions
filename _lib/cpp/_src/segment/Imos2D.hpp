#include "../macros.hpp"

// 2次元いもす(未verify)
template<typename T>
class Imos2D {
    int H;
    int W;
    vector<vector<T>> dat;

public:
    Imos2D(int H, int W) : H(H), W(W) {
        dat.resize(H+1, vector<T>(W+1, 0));
    }

    // [h1,h2),[w1,w2)の区間加算
    void add(int h1, int w1, int h2, int w2, T x) {
        if (h1 >= h2 or w1 >= w2) return;
        dat[h1][w1] += x;
        dat[h1][w2] -= x;
        dat[h2][w1] -= x;
        dat[h2][w2] += x;
    }

    void build() {
        rep(i, H+1) {
            rep(j, W) {
                dat[i][j+1] += dat[i][j];
            }
        }
        rep(j, W+1) {
            rep(i, H) {
                dat[i+1][j] += dat[i][j];
            }
        }
    }

    // (h,w)の1点取得
    T get(int h, int w) {
        return dat[h][w];
    }
};
