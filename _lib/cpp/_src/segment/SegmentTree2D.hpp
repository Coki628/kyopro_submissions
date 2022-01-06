#include "../base.hpp"

// 参考：http://algoogle.hadrori.jp/algorithm/2d-segment-tree.html
// 　　　https://qiita.com/tomato1997/items/83ccdfe0ce1f5548a42a
// 　　　https://ei1333.github.io/luzhiled/snippets/structure/segment-tree.html
// 2Dセグ木(非再帰、更新あり)
template<typename T, typename F>
struct SegmentTree2D {

    int H, W;
    vector<vector<T>> dat;
    const F f;
    const T M1;

    SegmentTree2D(const F f, const T &M1) : f(f), M1(M1) {}

    SegmentTree2D(int _H, int _W, const F f, const T &M1) : f(f), M1(M1) {
        H = W = 1;
        while(H < _H) H <<= 1;
        while(W < _W) W <<= 1;
        dat.assign(2*H,vector<T>(2*W, M1));
    }

    SegmentTree2D(vector<vector<T>> &grid, const F f, const T &M1) : f(f), M1(M1) {
        H = W = 1;
        while(H < (int)grid.size()) H <<= 1;
        while(W < (int)grid[0].size()) W <<= 1;
        dat.assign(2*H,vector<T>(2*W, M1));
        for (int i = 0; i < (int)grid.size(); i++)
            for (int j = 0; j < (int)grid[0].size(); j++)
                dat[H+i][W+j] = grid[i][j];
        build();
    }

    void set(int i, int j, T x) {
        dat[H+i][W+j] = x;
    }

    T get(int i, int j) {
        return dat[H+i][W+j];
    }

    void build() {
        for (int i = 2*H-1; i > H-1; i--)
            for (int j = W-1; j > 0; j--)
                dat[i][j] = f(dat[i][2*j], dat[i][2*j+1]);
        for (int i = H-1; i > 0; i--)
            for (int j = 1; j < 2*W; j++)
                dat[i][j] = f(dat[2*i][j], dat[2*i+1][j]);
    }

    T query(int Lx, int Ly, int Rx, int Ry) {
        T vLx = M1, vRx = M1;
        for (Lx += H, Rx += H; Lx < Rx; Lx >>= 1, Rx >>= 1) {
            if (Lx & 1) {
                T vLy = M1, vRy = M1;
                for (T Ly1 = Ly + W, Ry1 = Ry + W; Ly1 < Ry1; Ly1 >>= 1, Ry1 >>= 1) {
                    if (Ly1 & 1) vLy = f(vLy, dat[Lx][Ly1++]);
                    if (Ry1 & 1) vRy = f(dat[Lx][--Ry1], vRy);
                }
                vLx = f(vLx, f(vLy, vRy));
                Lx++;
            }
            if (Rx & 1) {
                Rx--;
                T vLy = M1, vRy = M1;
                for (T Ly1 = Ly + W, Ry1 = Ry + W; Ly1 < Ry1; Ly1 >>= 1, Ry1 >>= 1) {
                    if (Ly1 & 1) vLy = f(vLy, dat[Rx][Ly1++]);
                    if (Ry1 & 1) vRy = f(dat[Rx][--Ry1], vRy);
                }
                vRx = f(f(vLy, vRy), vRx);
            }
        }
        return f(vLx, vRx);
    }

    void update(int x, int y, int val) {
        int i = x + H;
        int j = y + W;
        dat[i][j] = val;
        while (j >>= 1) {
            dat[i][j] = f(dat[i][2*j], dat[i][2*j+1]);
        }
        while (i >>= 1) {
            j = y + W;
            dat[i][j] = f(dat[2*i][j], dat[2*i+1][j]);
            while (j >>= 1) {
                dat[i][j] = f(dat[i][2*j], dat[i][2*j+1]);
            }
        }
    }
};

template<typename T, typename F>
SegmentTree2D<T, F> get_segment_tree_2d(const F& f, const T& M1) {
    return {f, M1};
}

template<typename T, typename F>
SegmentTree2D<T, F> get_segment_tree_2d(int H, int W, const F& f, const T& M1) {
    return {H, W, f, M1};
}

template<typename T, typename F>
SegmentTree2D<T, F> get_segment_tree_2d(vector<vector<T>> &grid, const F& f, const T& M1) {
    return {grid, f, M1};
}
