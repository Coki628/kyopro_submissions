#include "../macros.hpp"

// 縦反転
vector<string> flip_h(const vector<string> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    vector<string> res(W, string(H, '*'));
    rep(j, W) {
        rep(i, H) {
            res[i][j] = grid[H-i-1][j];
        }
    }
    return res;
}

// 横反転
vector<string> flip_w(const vector<string> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    vector<string> res(W, string(H, '*'));
    rep(i, H) {
        rep(j, W) {
            res[i][j] = grid[i][W-j-1];
        }
    }
    return res;
}
