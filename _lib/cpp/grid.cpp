/*
・ライブラリ：グリッド
*/

#include "_tpl.cpp"


// 4方向
const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
// グリッド⇔列変換
ll gridtoid(ll i, ll j, ll W) { return i*W+j; }
pll idtogrid(ll id, ll W) { return divmod(id, W); }


// グリッド転置
template<typename T>
vector<vector<T>> transpose(const vector<vector<T>> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    auto res = list2d(W, H, (T)0);
    rep(i, 0, H) {
        rep(j, 0, W) {
            res[j][i] = grid[i][j];
        }
    }
    return res;
}
vector<string> transpose(const vector<string> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    vector<string> res(W, string(H, '*'));
    rep(i, 0, H) {
        rep(j, 0, W) {
            res[j][i] = grid[i][j];
        }
    }
    return res;
}


// グリッドを時計回りに90度回転
vector<string> rot90(const vector<string> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    vector<string> res(W, string(H, '*'));
    rep(i, 0, H) {
        rep(j, 0, W) {
            res[j][H-i-1] = grid[i][j];
        }
    }
    return res;
}










////////// end template included here //////////











// 8方向
const vector<pii> directions8 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};


// グリッドBFS
vvl bfs(const vector<string> &grid, const vector<pii> &src, char invalid='#') {

    int H = grid.size();
    int W = grid[0].size();
    auto res = list2d(H, W, INF);
    const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    queue<pii> que;
    for (auto [h, w] : src) {
        que.push({h, w});
        res[h][w] = 0;
    }
    while (!que.empty()) {
        auto [h, w] = que.front(); que.pop();
        for (auto [dh, dw] : directions) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (grid[nh][nw] == invalid) continue;
            if (res[nh][nw] == INF) {
                res[nh][nw] = res[h][w] + 1;
                que.push({nh, nw});
            }
        }
    }
    return res;
}


// グリッド斜めのループ(いつもぱっと出ないでもたつくので。。)
// rep(k, -N, N) {
//     rep(i, N) {
//         if (0 <= i+k and i+k < N) {
//             // do something
//             // grid[i][i+k];
//         }
//     }
// }


// 余白付きグリッドを構築
vector<string> build_grid(int H, int W, char intv, int offset=1) {

    vector<string> res(H+offset*2);
    rep(h, 0, offset) res[h] = string(W+offset*2, intv);
    rep(h, offset, H+offset) {
        string s;
        cin >> s;
        res[h] = string(offset, intv) + s + string(offset, intv);
    }
    rep(h, H+offset, H+offset*2) res[h] = string(W+offset*2, intv);
    return res;
}


// グリッドダイクストラ(H*Wグリッド, 始点{h, w}) 
using P = tuple<ll, int, int>;
vvl dijkstra(const vvl &grid, pii src, ll invalid=-1) {

    int H = grid.size();
    int W = grid[0].size();
    auto res = list2d(H, W, INF);
    const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    priority_queue<P, vector<P>, greater<P>> que;
    auto [sh, sw] = src;
    que.push({0, sh, sw});
    res[sh][sw] = 0;

    while (!que.empty()) {
        auto [dist, h, w] = que.top(); que.pop();
        if (res[h][w] < dist) continue;
        for (auto [dh, dw] : directions) {
            int nh = h+dh;
            int nw = w+dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (grid[nh][nw] == invalid) continue;
            ll cost = grid[nh][nw];
            if (dist+cost < res[nh][nw]) {
                res[nh][nw] = dist+cost;
                que.push({dist+cost, nh, nw});
            }
        }
    }
    return res;
}
