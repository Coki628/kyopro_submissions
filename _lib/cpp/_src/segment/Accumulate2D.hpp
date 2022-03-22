#include "../macros.hpp"

// 2次元累積和
template<typename T>
class Accumulate2D {
    int H;
    int W;
    vector<vector<T>> dat;

    void build(const vector<vector<T>> &grid) {
        rep(i, H) {
            rep(j, W) {
                dat[i+1][j+1] = grid[i][j];
            }
        }
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
public:
    Accumulate2D(const vector<vector<T>> &grid) {
        H = grid.size();
        W = grid[0].size();
        dat.resize(H+1, vector<T>(W+1, 0));
        build(grid);
    }

    Accumulate2D(int H, int W) : H(H), W(W) {
        dat.resize(H+1, vector<T>(W+1, 0));
    }

    void set(int h, int w, T x) {
        dat[h+1][w+1] = x;
    }

    void add(int h, int w, T x) {
        dat[h+1][w+1] += x;
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

    // [h1,h2),[w1,w2)の区間和
    T query(int h1, int w1, int h2, int w2) {
        if (h1 >= h2 or w1 >= w2) return (T)0;
        return dat[h1][w1] - dat[h1][w2] - dat[h2][w1] + dat[h2][w2];
    }
};
