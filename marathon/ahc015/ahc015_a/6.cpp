/*
・切り替えて違う貪欲。欲しい種類が来る直前に左に寄せて、
　来たら右に寄せて、みたいにすると、1種類なら片側に寄せられる。
　これを一番個数の多い種類でやって、他2つは適当にそれぞれ上下に割り振った。
・これがかなり当たって伸びて、110M。
　時間ももうあまりないので、これをベースに微調整していく。
・同じ要領で2番目に多い種類を、今度は上下で割り振ってみる。
　ただし1番目の条件2つを最優先として、それがなかった場合にやる。
　両方なかった時は乱択で上下どっちか。これでまた伸びて125M。
・最後を乱択上下じゃなくて、下固定で試したら伸びた。これで133M。
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
    int mxval = P[2].second;
    vector<int> others = {P[0].second, P[1].second};
    vvi grid = listnd(H, W, 0);
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

    rep(t, N) {
        int p;
        cin >> p;
        p--;
        auto [h, w] = search_blank(p);
        grid[h][w] = F[t];

        if (t+1 < N) {
            char d = '.';
            if (F[t+1] == mxval) {
                d = 'L';
            } elif (F[t] == mxval) {
                d = 'R';
            } elif (F[t+1] == others[1]) {
                d = 'F';
            } elif (F[t] == others[1]) {
                d = 'B';
            } else {
                d = 'B';
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
        // auto T = gen_cases1({0});
        // sからn件実施
        auto T = gen_cases2(0, 100);
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
