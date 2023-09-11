/*
・初期解。思うように適当に貪欲。スコアは296M。
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
#include "common/listnd.hpp"
#include "common/chmin.hpp"
#include "common/chmax.hpp"
#include "common/randrange.hpp"
#include "common/Timer.hpp"
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"
#include "string/number_format.hpp"

#include "grid/gridtoid.hpp"
#include "grid/idtogrid.hpp"

auto solve(int testcase = -1) {
    Timer timer;
#ifdef __LOCAL
#ifdef __DEBUG
    string basedir = "tools/";
#else
    string basedir = "../tools/";
#endif
    // 入力ファイル読み込み
    string filename = basedir + "in/" + zfill(tostr(testcase), 4) + ".txt";
    freopen(filename.c_str(), "r", stdin);
    // 出力ファイル準備
    filename = basedir + "out/" + zfill(tostr(testcase), 4) + ".txt";
    ofstream ofs(filename.c_str());
    if (!ofs) {
        print("error, please check if '" + basedir + "out/' dir exists");
        exit(0);
    }
#endif
    int T = 100, H = 20, W = 20;
    int sh, sw = 0;
    cin >> T >> H >> W >> sh;
    // int blocked[H][W][4] = {};
    auto blocked = listnd(H, W, 4, 0);
    // 下の境界
    rep(h, H - 1) {
        rep(w, W) {
            char tmp;
            cin >> tmp;
            blocked[h][w][1] = tmp - '0';
            blocked[h + 1][w][0] = tmp - '0';
        }
    }
    // 右の境界
    rep(h, H) {
        rep(w, W - 1) {
            char tmp;
            cin >> tmp;
            blocked[h][w][3] = tmp - '0';
            blocked[h][w + 1][2] = tmp - '0';
        }
    }
    rep(h, H) {
        blocked[h][0][2] = 1;
        blocked[h][W - 1][3] = 1;
    }
    rep(w, W) {
        blocked[0][w][0] = 1;
        blocked[H - 1][w][1] = 1;
    }
    int K;
    cin >> K;
    vector<ll> S(K), D(K);
    rep(k, K) {
        cin >> S[k] >> D[k];
    }

    // グリッドBFS：出口セルからの距離
    auto bfs = [&](const vector<pii> &src) {
        auto res = list2d(H, W, INF);
        queue<pii> que;
        for (auto [h, w] : src) {
            que.push({h, w});
            res[h][w] = 0;
        }
        while (!que.empty()) {
            ll h, w;
            tie(h, w) = que.front();
            que.pop();
            rep(d, 4) {
                int revd = d % 2 == 0 ? d + 1 : d - 1;
                auto [dh, dw] = dir4[d];
                int nh = h + dh;
                int nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                if (blocked[h][w][d]) continue;
                if (res[nh][nw] == INF) {
                    res[nh][nw] = res[h][w] + 1;
                    que.push({nh, nw});
                }
            }
        }
        return res;
    };
    auto dist = bfs({{sh, sw}});

    auto grid_used = listnd(H, W, 0);
    auto add_agri = [&](ll h, ll w) {
        rep(d, 4) {
            blocked[h][w][d]++;
        }
        grid_used[h][w] = 1;
    };
    auto remove_agri = [&](ll h, ll w) {
        rep(d, 4) {
            blocked[h][w][d]--;
        }
        grid_used[h][w] = 0;
    };
    // とりあえず雑だけど仮で全部繋がってるか見る
    auto is_connected = [&]() {
        auto res = bfs({{sh, sw}});
        ll cnt = 0;
        rep(h, H) {
            rep(w, W) {
                if (res[h][w] >= INF) {
                    return false;
                }
            }
        }
        return true;
    };
    auto calc = [&](vector<array<ll, 4>> ans) {
        ll sm = 0;
        for (auto [k, h, w, t] : ans) {
            k--;
            sm += D[k] - S[k] + 1;
        }
        return 1e6 * sm / (H * W * T);
    };

    auto get_wait = [blocked](int h, int w) {
        // 後で考える
        return 0;
    };
    // 未使用セル
    priority_queue<array<ll, 3>> que_unused;
    rep(h, H) {
        rep(w, W) {
            que_unused.push({get_wait(h, w), dist[h][w], gridtoid(h, w, W)});
        }
    }
    // 作物の優先度
    vector<array<ll, 2>> agris;
    rep(k, K) {
        agris.pb({D[k], k});
    }
    // 右端ソート
    sort(ALL(agris));

    // A[i] := K[i]をどこで使ってるか
    vector<int> A(K, -1);
    vvi adj(T + 1);
    rep(k, K) {
        adj[D[k]].eb(k);
    }

    vector<array<ll, 4>> ans;
    ll curk = 0;
    rep(t, 1, T + 1) {
        vector<array<ll, 3>> tmp;
        while (curk < K and que_unused.size()) {
            auto [wa, di, i] = que_unused.top();
            que_unused.pop();
            auto [h, w] = idtogrid(i, W);
            auto [_, k] = agris[curk];
            if (S[k] < t) {
                // もう間に合わない
                curk++;
                continue;
            }
            add_agri(h, w);
            if (is_connected()) {
                A[k] = i;
                ans.pb({k + 1, h, w, t});
                curk++;
            } else {
                remove_agri(h, w);
                // この日には使わない
                tmp.pb({wa, di, i});
            }
        }
        for (auto arr : tmp) {
            que_unused.push(arr);
        }
        // 収穫
        for (auto k : adj[t]) {
            if (A[k] != -1) {
                auto [h, w] = idtogrid(A[k], W);
                remove_agri(h, w);
                que_unused.push({get_wait(h, w), dist[h][w], A[k]});
                A[k] = -1;
            }
        }
    }

    ll mxscore = calc(ans);

#ifdef __LOCAL
    ofs << ans.size() << endl;
    for (auto [k, h, w, t] : ans) {
        ofs << k << ' ' << h << ' ' << w << ' ' << t << endl;
    }
#else
    print(ans.size());
    print(ans, '\n');
#endif

    return mxscore;
}

// テスト番号指定
vector<int> gen_cases1(const vector<int> &T) {
    return T;
}

// sからn件実施
vector<int> gen_cases2(int s, int n) {
    vector<int> T;
    rep(i, s, s + n) {
        T.eb(i);
    }
    return T;
}

// [s,t)を実施
vector<int> gen_cases3(int s, int t) {
    vector<int> T;
    rep(i, s, t) {
        T.eb(i);
    }
    return T;
}

// [s,t)の範囲でランダムにn件実施
vector<int> gen_cases4(int s, int t, int n) {
    vector<int> T;
    rep(i, s, t) {
        T.eb(i);
    }
    shuffle(ALL(T), mt);
    return vector<int>(T.begin(), T.begin() + n);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

#ifdef __LOCAL
    // テスト番号指定
    // auto T = gen_cases1({0});
    // sからn件実施
    auto T = gen_cases2(0, 20);
    // [s,t)を実施
    // auto T = gen_cases3(0, 100);
    // [s,t)の範囲でランダムにn件実施
    // auto T = gen_cases4(0, 100, 20);

    ll totalscore = 0;
    for (int t : T) {
        cout << "case #" << t << " start" << endl;
        auto score = solve(t);
        cout << "case #" << t << " score: ";
        print(number_format(score));
        cout << endl;
        totalscore += score;
    }
    cout << "total score: ";
    print(number_format(totalscore));
#else
    solve();
#endif

    return 0;
}
