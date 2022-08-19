/*
・焼きなまし
・教科書通りに整えたら、やばいくらいスコア下がった…。。。
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
#include "graph/UnionFind.hpp"

int calc_score(int K2, const vector<array<ll, 4>> &cas, const vvi &mp) {

    UnionFind uf(K2);
    for (auto ca : cas) {
        int u = mp[ca[0]][ca[1]];
        int v = mp[ca[2]][ca[3]];
        uf.merge(u, v);
    }

    int score = 0;
    for (auto r : uf.get_roots()) {
        int sz = uf.size(r);
        score += sz * (sz-1) / 2;
    }

    return score;
}

const int TL = 2800;
// 一回の遷移で動きうるスコア幅の最大値程度
const ld T0 = 30;
// 一回の遷移で動きうるスコア幅の最小値程度
const ld T1 = 1;

// 焼きなましに使う温度の計算
ld calc_temp(int elapsed) {
    ld t = elapsed / (ld)TL;
    if (t >= 1) {
        return -1;
    }
    // return T0 + (T1-T0)*t;
    return pow(T0, (1-t))*pow(T1, t);
}

// 焼きなましを踏まえた採用確率の計算
bool calc_prob(ld score, ld temp) {
    if (score > 0) {
        return 1;
    }
    auto prob = exp(score/temp);
    return prob*100 >= randrange(0, 100);
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
        if (h1 > h2) swap(h1, h2);
        if (w1 > w2) swap(w1, w2);
        // 接続済
        if (find(ALL(cas), array<ll, 4>{h1, w1, h2, w2}) != cas.end()) {
            return false;
        }
        if (h1 == h2) {
            rep(w, w1+1, w2) {
                if (used[h1][w].size() or colors[h1][w] > 0) {
                    return false;
                }
            }
            return true;
        } elif (w1 == w2) {
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
        if (h1 > h2) swap(h1, h2);
        if (w1 > w2) swap(w1, w2);
        if (h1 == h2) {
            rep(w, w1+1, w2) {
                used[h1][w] = {h1, w1, h2, w2};
                colors[h1][w] = colors[h1][w1];
            }
        } elif (w1 == w2) {
            rep(h, h1+1, h2) {
                used[h][w1] = {h1, w1, h2, w2};
                colors[h][w1] = colors[h1][w1];
            }
        } else {
            assert(0);
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
        if (h1 > h2) swap(h1, h2);
        if (w1 > w2) swap(w1, w2);
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
        cas.erase(find(ALL(cas), array<ll, 4>{h1, w1, h2, w2}));
    };
    // 四方を見て接続
    auto connect_around = [&](int ch, int cw) -> void {
        rep(nh, ch+1, N) {
            if (grid[nh][cw] > 0) {
                if (can_connect(ch, cw, nh, cw)) {
                    connect(ch, cw, nh, cw);
                }
                break;
            }
        }
        rep(nh, ch-1, -1, -1) {
            if (grid[nh][cw] > 0) {
                if (can_connect(ch, cw, nh, cw)) {
                    connect(ch, cw, nh, cw);
                }
                break;
            }
        }
        rep(nw, cw+1, N) {
            if (grid[ch][nw] > 0) {
                if (can_connect(ch, cw, ch, nw)) {
                    connect(ch, cw, ch, nw);
                }
                break;
            }
        }
        rep(nw, cw-1, -1, -1) {
            if (grid[ch][nw] > 0) {
                if (can_connect(ch, cw, ch, nw)) {
                    connect(ch, cw, ch, nw);
                }
                break;
            }
        }
    };

    // 初期解
    rep(i, N) {
        rep(j, N) {
            if (grid[i][j]) {
                connect_around(i, j);
            }
        }
    }
    int score = calc_score(K2, cas, mp);
    while (cas.size() >= K2) {
        cas.pop_back();
    }

    // (ch,cw)にあるやつを(nh,nw)に移動
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
        connect_around(nh, nw);
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

    auto elapsed = timer.get_elapse();
    auto temp = calc_temp(elapsed);
    int opcnt = 0, opcnt2 = 0;
    while (1) {
        // 温度の更新
        if (opcnt%10 == 0) {
            elapsed = timer.get_elapse();
            temp = calc_temp(elapsed);
            if (temp == -1) break;
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
        if (cas.size() + mas.size() <= K2) {
            int nxscore = calc_score(K2, cas, mp);
            if (calc_prob(nxscore-score, temp)) {
                score = nxscore;
                updated = true;
            }
        }
        if (not updated) {
            swap(nh, nw, ch, cw);
            mas.pop_back();
        }
    }
    // 状態戻しても辺が増えてしまっているケースに対応
    while (cas.size() + mas.size() > K2) {
        cas.pop_back();
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

    score = calc_score(K2, cas, mp);
    return score;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        // vector<ll> T = {
        //     4,
        // };

        // 0からn件実施
        int n = 10;
        vector<ll> T;
        rep(i, n) {
            T.eb(i);
        }

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
