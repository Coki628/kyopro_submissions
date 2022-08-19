/*
・山登り
・初期解から1箇所移動で山登り。これで45000点くらい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"

#include "common/input.hpp"
#include "common/print.hpp"
#include "common/randrange.hpp"
#include "common/Timer.hpp"
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"

#include "common/listnd.hpp"
#include "common/HashMap.hpp"

struct UnionFind {
    HashMap<pair<int,int>, pair<int, int>> parent;
    UnionFind() :parent() {}

    pair<int, int> find(pair<int, int> x)
    {
        if (not parent.count(x)) {
            parent[x] = x;
            return x;
        } else if (parent[x] == x) {
            return x;
        } else {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void unite(pair<int, int> x, pair<int, int> y)
    {
        x = find(x);
        y = find(y);
        if (x != y) {
            parent[x] = y;
        }
    }
};

int calc_score(int N, vvi field, const vector<array<ll, 4>> cas) {

    UnionFind uf;
    for (auto ca : cas) {
        pair<int, int> p1(ca[0], ca[1]), p2(ca[2], ca[3]);
        uf.unite(p1, p2);
    }

    vector<pair<int, int>> computers;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (field[i][j] != 0) {
                computers.emplace_back(i, j);
            }
        }
    }

    int score = 0;
    for (int i = 0; i < (int)computers.size(); i++) {
        for (int j = i+1; j < (int)computers.size(); j++) {
            auto c1 = computers[i];
            auto c2 = computers[j];
            if (uf.find(c1) == uf.find(c2)) {
                score += (field[c1.first][c1.second] == field[c2.first][c2.second]) ? 1 : -1;
            }
        }
    }

    return max(score, 0);
}

ld solve(int testcase=-1) {
    Timer timer;
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/" + zfill(tostr(testcase), 4) + ".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/" + zfill(tostr(testcase), 4) + ".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print("error, please check if 'tools/out/' dir exists");
            exit(0);
        }
    #endif

    int N, K;
    cin >> N >> K;
    int K2 = K * 100;
    auto grid = listnd(N, N, 0);
    auto mp = listnd(N, N, -1);
    vector<pii> rev(K2);
    int k = 0;
    rep(i, N) {
        string s;
        cin >> s;
        rep(j, N) {
            grid[i][j] = s[j] - '0';
            if (grid[i][j] > 0) {
                mp[i][j] = k;
                rev[k] = {i, j};
                k++;
            }
        }
    }
    assert(k == K2);

    vvi nodes(K2);
    auto colors = grid;
    auto used = listnd(N, N, vector<ll>());
    vector<array<ll, 4>> mas;
    vector<array<ll, 4>> cas;
    // 接続チェック
    auto can_connect = [&](int h1, int w1, int h2, int w2) -> bool {
        if (grid[h1][w1] != grid[h2][w2]) {
            return false;
        }
        assert(h1 == h2 or w1 == w2);
        if (h1 == h2) {
            if (w1 > w2) swap(w1, w2);
            rep(w, w1+1, w2) {
                if (used[h1][w].size() or colors[h1][w] > 0) {
                    return false;
                }
            }
            return true;
        } elif (w1 == w2) {
            if (h1 > h2) swap(h1, h2);
            rep(h, h1+1, h2) {
                if (used[h][w1].size() or colors[h][w1] > 0) {
                    return false;
                }
            }
            return true;
        } else {
            assert(0);
        }
    };
    // 接続
    auto connect = [&](int h1, int w1, int h2, int w2) -> void {
        int u = mp[h1][w1];
        int v = mp[h2][w2];
        nodes[u].eb(v);
        nodes[v].eb(u);
        assert(grid[h1][w1] == grid[h2][w2]);
        assert(h1 == h2 or w1 == w2);
        if (h1 == h2) {
            if (w1 > w2) swap(w1, w2);
            rep(w, w1+1, w2) {
                used[h1][w] = {h1, w1, h2, w2};
                colors[h1][w] = colors[h1][w1];
            }
        } elif (w1 == w2) {
            if (h1 > h2) swap(h1, h2);
            rep(h, h1+1, h2) {
                used[h][w1] = {h1, w1, h2, w2};
                colors[h][w1] = colors[h1][w1];
            }
        } else {
            assert(0);
        }
        if (h1 > h2 or h1 == h2 and w1 > w2) {
            swap(h1, h2);
            swap(w1, w2);
        }
        cas.pb({h1, w1, h2, w2});
    };
    // 切断
    auto disconnect = [&](int h1, int w1, int h2, int w2) -> void {
        int u = mp[h1][w1];
        int v = mp[h2][w2];
        nodes[u].erase(find(ALL(nodes[u]), v));
        nodes[v].erase(find(ALL(nodes[v]), u));
        assert(grid[h1][w1] == grid[h2][w2]);
        assert(h1 == h2 or w1 == w2);
        if (h1 == h2) {
            if (w1 > w2) swap(w1, w2);
            rep(w, w1+1, w2) {
                used[h1][w] = {};
                colors[h1][w] = 0;
            }
        } elif (w1 == w2) {
            if (h1 > h2) swap(h1, h2);
            rep(h, h1+1, h2) {
                used[h][w1] = {};
                colors[h][w1] = 0;
            }
        } else {
            assert(0);
        }
        if (h1 > h2 or h1 == h2 and w1 > w2) {
            swap(h1, h2);
            swap(w1, w2);
        }
        cas.erase(find(ALL(cas), array<ll, 4>{h1, w1, h2, w2}));
    };

    bool full = false;
    rep(i, N) {
        rep(j, N) {
            if (grid[i][j]) {
                rep(k, i+1, N) {
                    if (grid[k][j] > 0) {
                        if (can_connect(i, j, k, j)) {
                            connect(i, j, k, j);
                        }
                        break;
                    }
                }
                if (cas.size() == K2) {
                    full = true;
                    break;
                }
                rep(k, j+1, N) {
                    if (grid[i][k] > 0) {
                        if (can_connect(i, k, i, j)) {
                            connect(i, j, i, k);
                        }
                        break;
                    }
                }
                if (cas.size() == K2) {
                    full = true;
                    break;
                }
            }
        }
        if (full) break;
    }
    int score = calc_score(N, grid, cas);

    auto swap = [&](int ch, int cw, int nh, int nw) -> void {
        assert(grid[ch][cw] > 0 and grid[nh][nw] == 0);
        assert(mp[ch][cw] != -1);
        assert(ch == nh or cw == nw);
        int u = mp[ch][cw];
        auto tmp = nodes[u];
        for (auto v : tmp) {
            auto [vh, vw] = rev[v];
            disconnect(ch, cw, vh, vw);
        }
        if (used[nh][nw].size()) {
            int ah = used[nh][nw][0];
            int aw = used[nh][nw][1];
            int bh = used[nh][nw][2];
            int bw = used[nh][nw][3];
            disconnect(ah, aw, bh, bw);
        }
        std::swap(grid[ch][cw], grid[nh][nw]);
        mp[ch][cw] = -1;
        mp[nh][nw] = u;
        rev[u] = {nh, nw};

        // nh,nwで四方の接続
        rep(kh, nh+1, N) {
            if (grid[kh][nw] > 0) {
                if (can_connect(nh, nw, kh, nw)) {
                    connect(nh, nw, kh, nw);
                }
                break;
            }
        }
        rep(kh, nh-1, -1, -1) {
            if (grid[kh][nw] > 0) {
                if (can_connect(nh, nw, kh, nw)) {
                    connect(nh, nw, kh, nw);
                }
                break;
            }
        }
        rep(kw, nw+1, N) {
            if (grid[nh][kw] > 0) {
                if (can_connect(nh, nw, nh, kw)) {
                    connect(nh, nw, nh, kw);
                }
                break;
            }
        }
        rep(kw, nw-1, -1, -1) {
            if (grid[nh][kw] > 0) {
                if (can_connect(nh, nw, nh, kw)) {
                    connect(nh, nw, nh, kw);
                }
                break;
            }
        }
        // ch,cwでその先の両側の接続
        if (ch == nh) {
            int ah = ch + 1;
            while (ah < N and grid[ah][cw] == 0) ah++;
            int bh = ch - 1;
            while (bh >= 0 and grid[bh][cw] == 0) bh--;
            if (ah < N and bh >= 0 and can_connect(ah, cw, bh, cw)) {
                connect(ah, cw, bh, cw);
            }
        } elif (cw == nw) {
            int aw = cw + 1;
            while (aw < N and grid[ch][aw] == 0) aw++;
            int bw = cw - 1;
            while (bw >= 0 and grid[ch][bw] == 0) bw--;
            if (aw < N and bw >= 0 and can_connect(ch, aw, ch, bw)) {
                connect(ch, aw, ch, bw);
            }
        }
    };

    const int TL = 2800;
    auto elapsed = timer.get_elapse();
    int opcnt = 0, opcnt2 = 0;
    while (1) {
        if (opcnt%1 == 0) {
            elapsed = timer.get_elapse();
            if (elapsed >= TL) break;
        }
        opcnt++;

        int x = randrange(0, K2);
        auto [ch, cw] = rev[x];
        int d = randrange(0, 4);
        auto [dh, dw] = dir4[d];
        int nh = ch + dh;
        int nw = cw + dw;
        if (nh < 0 or nw < 0 or nh >= N or nw >= N) continue;
        if (grid[nh][nw] > 0) continue;
        opcnt2++;

        swap(ch, cw, nh, nw);
        mas.pb({ch, cw, nh, nw});
        bool updated = false;
        if (cas.size() + mas.size() < K2) {
            int nxscore = calc_score(N, grid, cas);
            if (nxscore > score) {
                score = nxscore;
                updated = true;
            }
        }
        if (not updated) {
            swap(nh, nw, ch, cw);
            mas.pop_back();
        }
    }

    #ifdef __LOCAL
        debug(opcnt);
        debug(opcnt2);
        ofs << mas.size() << endl;
        for (auto& ma : mas) {
            ofs << ma << endl;
        }
        ofs << cas.size() << endl;
        for (auto& ca : cas) {
            ofs << ca << endl;
        }
    #else
        print(mas.size());
        print(mas, '\n');
        print(cas.size());
        print(cas, '\n');
    #endif

    score = calc_score(N, grid, cas);
    return score;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        vector<ll> T = {
            1,
        };

        // 0からn件実施
        // int n = 10;
        // vector<ll> T;
        // rep(i, n) {
        //     T.eb(i);
        // }

        ld totalscore = 0;
        for (ll t : T) {
            ld score = solve(t);
            cout << "case #" << t << " ";
            debug(score);
            totalscore += score;
        }
        debug(totalscore);
    #else
        solve();
    #endif

    return 0;
}
