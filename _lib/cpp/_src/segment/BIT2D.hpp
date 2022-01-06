#include "../base.hpp"

// 参考：https://ta7uw.hatenablog.com/entry/2019/09/29/162635
// ・他のライブラリと使い勝手を統一したいので、操作としては0-indexedで動かせるようにしてある。
// 2次元BIT
template<typename T>
class BIT2D {
    int H;
    int W;
    vector<vector<T>> data2d;
public:
    BIT2D(int H, int W) : H(H), W(W) {
        data2d.resize(H+1, vector<T>(W+1, 0));
    }

    // [0,h],[0,w]
    T sum(int h, int w) {
        T res = 0;
        h++, w++;
        for (int i = h; i > 0; i -= i & -i) {
            for (int j = w; j > 0; j -= j & -j) {
                res += data2d[i-1][j-1];
            }
        }
        return res;
    }

    // [h1,h2),[w1,w2)の区間和
    T query(int h1, int w1, int h2, int w2) {
        return sum(h2-1, w2-1) - sum(h1-1, w2-1) - sum(h2-1, w1-1) + sum(h1-1, w1-1);
    }

    T get(int h, int w) {
        return query(h, w, h+1, w+1);
    }

    void add(int h, int w, T x) {
        h++, w++;
        for (int i = h; i <= H; i += i & -i) {
            for (int j = w; j <= W; j += j & -j) {
                data2d[i-1][j-1] += x;
            }
        }
    }
};
