#include "../macros.hpp"

// グリッドをK倍に拡大 
vector<string> scale(const vector<string> &grid, ll K) {
    int H = grid.size();
    int W = grid[0].size();
    vector<string> res(H*K, string(W*K, '*'));
    rep(i, H*K) {
        rep(j, W*K) {
            res[i][j] = grid[i/K][j/K];
        }
    }
    return res;
}
