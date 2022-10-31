/*
参考：https://twitter.com/eijirou_kyopro/status/1586706200619466752
・モンテカルロ法
・自分でやろうとしたやつを元に、シミュの方法を一番良かったルールベース貪欲に変えて、
　バグってた所直して微調整。試行回数10回だと大したことなかったけど、
　回数増やすと手元実行でもスコアが明らかに改善された。
　ldをdoubleにしたりちょっと高速化して220回できるようにした。
・得点はなんと150M。もし本番にこれ出してたら全体6位で赤パフォ…やばいな。AHCは夢がある。
・試しにQCFium法を解放したら、やたら速くなった。一番深い所の処理(盤面動かすとこ)が
　単純なループだけなので、こういう系はやっぱ効きやすいんだな。
・これで回数は290回まで増やせて、得点は152M。全体4位になった。すごい。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

#include "graph/UnionFind.hpp"
#include "grid/gridtoid.hpp"
#include "grid/idtogrid.hpp"

auto solve(int testcase=-1) {
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

    array<char, 4> D = {'F', 'B', 'L', 'R'};
    map<char, int> dtoi = {{'F', 0}, {'B', 1}, {'L', 2}, {'R', 3}};
    vector<int> ids(4);
    iota(ALL(ids), 0);
    const int H = 10, W = 10;
    const int N = H * W;
    vector<int> F(N);
    cin >> F;
    vector<int> C(4);
    rep(i, N) {
        C[F[i]]++;
    }
    vector<pii> P;
    rep(i, 1, 4) {
        P.eb(C[i], i);
    }
    sort(ALL(P));
    vector<int> sorted = {P[0].second, P[1].second, P[2].second};
    array<array<int, H>, W> grid = {};
    // スコア計算
    auto calc = [&]() -> ld {
        UnionFind uf(N);
        array<int, 4> C = {};
        rep(h, H) {
            rep(w, W) {
                if (grid[h][w] == 0) continue;
                C[grid[h][w]]++;
                int u = gridtoid(h, w, W);
                for (auto [dh, dw] : dir4) {
                    int nh = h + dh;
                    int nw = w + dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (grid[nh][nw] == grid[h][w]) {
                        int v = gridtoid(nh, nw, W);
                        uf.merge(u, v);
                    }
                }
            }
        }
        ll sm1 = 0;
        for (auto r : uf.get_roots()) {
            auto [h, w] = idtogrid(r, W);
            if (grid[h][w] == 0) continue;
            sm1 += uf.size(r) * (ll)uf.size(r);
        }
        ll sm2 = 0;
        rep(c, 1, 4) {
            sm2 += C[c] * (ll)C[c];
        }
        return round(1e6 * sm1 / (ld)sm2);
    };
    // 置くマス確定
    auto search_blank = [&](int p) -> pii {
        int cnt = 0;
        rep(h, H) {
            rep(w, W) {
                if (grid[h][w] == 0) {
                    if (cnt == p) {
                        return {h, w};
                    } else {
                        cnt++;
                    }
                }
            }
        }
        assert(0);
    };
    // 動かす
    auto move_candies = [&](char d) -> void {
        if (d == 'F') {
            rep(w, W) {
                int nh = 0;
                rep(ch, H) {
                    if (grid[ch][w] != 0) {
                        grid[nh][w] = grid[ch][w];
                        if (ch != nh) {
                            grid[ch][w] = 0;
                        }
                        nh++;
                    }
                }
            }
        } elif (d == 'B') {
            rep(w, W) {
                int nh = H - 1;
                rep(ch, H-1, -1, -1) {
                    if (grid[ch][w] != 0) {
                        grid[nh][w] = grid[ch][w];
                        if (ch != nh) {
                            grid[ch][w] = 0;
                        }
                        nh--;
                    }
                }
            }
        } elif (d == 'L') {
            rep(h, H) {
                int nw = 0;
                rep(cw, W) {
                    if (grid[h][cw] != 0) {
                        grid[h][nw] = grid[h][cw];
                        if (cw != nw) {
                            grid[h][cw] = 0;
                        }
                        nw++;
                    }
                }
            }
        } else {
            rep(h, H) {
                int nw = W - 1;
                rep(cw, W-1, -1, -1) {
                    if (grid[h][cw] != 0) {
                        grid[h][nw] = grid[h][cw];
                        if (cw != nw) {
                            grid[h][cw] = 0;
                        }
                        nw--;
                    }
                }
            }
        }
    };
    // ターンxtが終わって、次にxdを選んだ時に、ターンxnで結果どうなるかシミュ
    auto predict = [&](int xt, int xn, char xd) {
        auto gridbk = grid;
        move_candies(xd);
        rep(t, xt+1, xn) {
            int p = randrange(0, xn-t);
            auto [h, w] = search_blank(p);
            grid[h][w] = F[t];

            // シミュには一番良かったルールベース貪欲を使用
            char d = '.';
            if (F[t+1] == sorted[2]) {
                d = 'L';
            } elif (F[t] == sorted[2]) {
                d = 'R';
            } elif (F[t+1] == sorted[1]) {
                d = 'B';
            } elif (F[t] == sorted[1]) {
                d = 'F';
            } else {
                d = 'F';
            }

            move_candies(d);
        }
        ld res = calc();
        grid = gridbk;
        return res;
    };

    rep(t, N) {
        int p;
        cin >> p;
        p--;
        auto [h, w] = search_blank(p);
        grid[h][w] = F[t];

        if (t+1 < N) {
            vector<double> prescores(4);
            const int OPCNT = 290;
            rep(_, OPCNT) {
                rep(i, 4) {
                    prescores[i] += predict(t, N-1, D[i]);
                }
            }
            double score = -INF;
            char d = '.';
            shuffle(ALL(ids), mt);
            rep(i, 4) {
                if (chmax(score, prescores[ids[i]])) {
                    d = D[ids[i]];
                }
            }
            #ifdef __LOCAL
                ofs << d << endl;
            #else
                cout << d << endl;
            #endif
            move_candies(d);
        }
    }

    ld mxscore = calc();

    return mxscore;
}

// テスト番号指定
vector<int> gen_cases1(const vector<int>& T) {
    return T;
}

// sからn件実施
vector<int> gen_cases2(int s, int n) {
    vector<int> T;
    rep(i, s, s+n) {
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
    return vector<int>(T.begin(), T.begin()+n);;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // テスト番号指定
        auto T = gen_cases1({0});
        // sからn件実施
        // auto T = gen_cases2(0, 100);
        // [s,t)を実施
        // auto T = gen_cases3(0, 100);
        // [s,t)の範囲でランダムにn件実施
        // auto T = gen_cases4(0, 100, 20);

        ld totalscore = 0;
        for (int t : T) {
            cout << "case #" << t << " start" << endl;
            auto score = solve(t);
            cout << "case #" << t << " ";
            debug(score);
            cout << endl;
            totalscore += score;
        }
        debug(totalscore);
    #else
        solve();
    #endif

    return 0;
}
