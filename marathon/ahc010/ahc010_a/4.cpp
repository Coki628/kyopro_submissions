/*
・終了後、ある程度やろうとしていた方針を書き上げた。
・DFS、サイクルのパス復元
・パーツの形と入る向きによって、行ける方向は1通りか2通り。
　これを全部辿ってみて、サイクルを作れたらそのパスを取る。
　取れた全サイクルパスのうち、大きくて被ってない2つを使う。とした。
・みんな言ってたけど、DFSの実装は結構大変だった。
　マスと向きを両方気にしながら進んでいく必要があるし、
　パスの復元ではサイクル突入前の余計な部分を拾わないように工夫する、
　とか、色々気を付けるポイントがあったと思う。
・2通りの選択を多数やることを考えると、最悪時は計算量が爆発するかと思って、
　潜る深さに制限をかけてたんだけど、それ取っ払っても0.2秒くらいしかかからなかった。
　多分、同じマスに行った時点でその分岐が切れるから速いんだろうけど、
　方向も考えると状態数多そうだし、計算量読めない感じのやつ。
・これでまた1桁伸びて、124万点くらい。黄パフォ手前くらい相当。
　本番でここまで書けたら楽しかったなー。
・でもぱっと考えてるだけでもまだ伸び代があって、
　まずビジュアライザー見て思ったのは、1つのサイクルが大きくなり過ぎて、
　他方はとても小さくなっているので、領域を半分に分けてもいいと思う。
　それをやらなくても、多分サイクルのペア全探索はできると思うので、
　1番大きい2つじゃなくて、全ペア試して1番いいやつってできればそれでも伸びそう。
・全ペア試すのやってみた。やはりこれだけでもかなり伸びて、714万点くらい。
　ここまでできたら黄パフォ中位くらいで2ページ目にまでなる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "common/listnd.hpp"
#include "common/chmax.hpp"
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"

const int TL = 1900;
const int N = 30;
// 左上右下
const vector<int> di = {0, -1, 0, 1}, dj = {-1, 0, 1, 0};
const vvi to = {
    {1, 0, -1, -1},
    {3, -1, -1, 0},
    {-1, -1, 3, 2},
    {-1, 2, 1, -1},
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {2, -1, 0, -1},
    {-1, 3, -1, 1},
};
int used[N][N][4];

ld solve(int testcase=-1) {
    Timer timer;
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/"+zfill(tostr(testcase), 4)+".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/"+zfill(tostr(testcase), 4)+".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print(-1);
            exit(0);
        }
    #endif

    vvi tiles = list2d(N, N, 0);
    rep(i, N) {
        string S;
        cin >> S;
        rep(j, N) {
            tiles[i][j] = S[j] - '0';
        }
    }


    // (si, sj) のタイルに sd 方向のタイルから侵入した状態からスタートして環状線の長さを求める
    auto get_length = [&](int si, int sj, int sd) -> int {
        int i = si;
        int j = sj;
        int d = sd;
        int length = 0;
        while (1) {
            used[i][j][d] = true;
            int d2 = to[tiles[i][j]][d];
            if (d2 == -1) return 0;
            used[i][j][d2] = true;
            i += di[d2];
            j += dj[d2];
            if (i < 0 || i >= 30 || j < 0 || j >= 30) return 0;
            d = (d2 + 2) % 4;
            length += 1;
            if (i == si && j == sj && d == sd) return length;
        }
    };

    // スコア計算
    auto calc = [&]() -> ll {
        rep(i, N) rep(j, N) rep(d, 4) used[i][j][d] = false;
        vector<int> lens;
        rep(i, N) {
            rep(j, N) {
                rep(d, 4) {
                    if (not used[i][j][d]) {
                        lens.eb(get_length(i, j, d));
                    }
                }
            }
        }
        sort(lens.rbegin(), lens.rend());
        return lens[0] * lens[1];
    };

    auto rotate = [](int d, int r) {
        if (d < 4) {
            return (d+r) % 4;
        } elif (d == 4 or d == 6) {
            return d + (r%2);
        } else {
            return d - (r%2);
        }
    };

    vector<int> one = {2, 3, 0, 1};
    auto get_next = [&](int i, int j, int d) -> vector<ll> {
        // 左右
        if (d == 0 or d == 2) {
            if (tiles[i][j] < 6) {
                return {1, 3};
            } else {
                return {one[d]};
            }
        // 上下
        } else {
            if (tiles[i][j] < 6) {
                return {0, 2};
            } else {
                return {one[d]};
            }
        }
    };

    // 探索を打ち切る深さ
    const int MXDEP = 100;
    vector<pair<ll, vector<array<ll, 4>>>> paths;
    rep(si, N) {
        rep(sj, N) {
            rep(sd, 4) {
                vector<array<ll, 4>> res;
                bool done = false;
                ll ti = -1, tj = -1, td = -1;
                auto D = list2d(N, N, -1);
                auto dfs = [&](auto&& f, int i, int j, int d, int dep) {
                    // ある程度の深さで打ち切り
                    // if (dep == MXDEP) {
                    //     return false;
                    // }
                    if (D[i][j] != -1) {
                        // 同じ方向で入れたらサイクル成功
                        bool res = D[i][j] == d;
                        if (res) {
                            // サイクルの入り口を覚えておく
                            ti = i, tj = j, td = d;
                        }
                        return res;
                    }
                    D[i][j] = d;
                    for (auto nxd : get_next(i, j, d)) {
                        ll nxi = i + di[nxd];
                        ll nxj = j + dj[nxd];
                        if (nxi < 0 || nxi >= 30 || nxj < 0 || nxj >= 30) continue;
                        if (f(f, nxi, nxj, (nxd + 2) % 4, dep+1)) {
                            // 入り口までの経路を取る
                            if (not done) res.pb({i, j, d, nxd});
                            if (i == ti and j == tj and d == td) {
                                done = true;
                            }
                            return true;
                        }
                    }
                    return false;
                };
                if (dfs(dfs, si, sj, (sd + 2) % 4, 0)) {
                    reverse(ALL(res));
                    paths.eb(res.size(), res);
                }
            }
        }
    }

    ll M = paths.size();
    ll len = 0;
    string ans(N*N, '*');
    rep(i, M) {
        auto used2 = list2d(N, N, 0);
        for (auto [h, w, d, nxd] : paths[i].second) {
            used2[h][w] = true;
        }
        rep(j, M) {
            if (j == i) continue;
            bool ok = true;
            for (auto [h, w, d, nxd] : paths[j].second) {
                if (used2[h][w]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                if (chmax(len, paths[i].first*paths[j].first)) {
                    vector<int> cur(N*N);
                    for (auto [h, w, d, nxd] : paths[i].second) {
                        ll r = 0;
                        ll tile = tiles[h][w];
                        while (to[tile][d] != nxd) {
                            tile = rotate(tile, 1);
                            r++;
                        }
                        cur[h*N+w] = r;
                    }
                    for (auto [h, w, d, nxd] : paths[j].second) {
                        ll r = 0;
                        ll tile = tiles[h][w];
                        while (to[tile][d] != nxd) {
                            tile = rotate(tile, 1);
                            r++;
                        }
                        cur[h*N+w] = r;
                    }
                    rep(k, N*N) ans[k] = '0' + cur[k];
                }
            }
        }
    }
    print(ans);

    ll score = calc();
    return score;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        vector<ll> T = {
            0,
        };
        // 100件実施
        // vector<ll> T;
        // rep(i, 100) {
        //     T.eb(i);
        // }
        ll score = 0;
        for (ll t : T) {
            score += solve(t);
        }
        debug(score);
    #else
        solve();
    #endif

    return 0;
}
