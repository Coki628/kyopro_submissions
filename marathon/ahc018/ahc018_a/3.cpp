/*
・直前に壊したマスの強度を覚えておいて、それに近い値で最初に叩くようにした。
・ちょい上がりで手元362M。
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

#include "graph/UnionFind.hpp"
#include "grid/gridtoid.hpp"
#include "grid/idtogrid.hpp"
#include "geometry/Point.hpp"
#include "geometry/Segment.hpp"
#include "geometry/get_distance.hpp"

int grid[200][200];
const int TL = 4700;

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

    int N, W, K, C;
    cin >> N >> W >> K >> C;
    int done = 0;
    ll score = 0;
    UnionFind uf(N * N);
    vector<int> has_water(N * N), house_count(N * N);
    auto broken = listnd(N, N, 0);

    auto merge = [&uf, &has_water, &house_count, &done](int u, int v) -> int {
        int ru = uf.find(u);
        int rv = uf.find(v);
        if (ru == rv) {
            return ru;
        }

        int r = uf.merge(u, v);
        if (has_water[ru] and not has_water[rv]) {
            done += house_count[rv];
        } else if (not has_water[ru] and has_water[rv]) {
            done += house_count[ru];
        }
        has_water[r] = has_water[ru] | has_water[rv];
        house_count[r] = house_count[ru] + house_count[rv];
        return r;
    };

#ifdef __LOCAL
    rep(i, N) {
        rep(j, N) {
            cin >> grid[i][j];
        }
    }
    auto ask = [N, C, K, &done, &score, &broken, &ofs, merge](int i, int j, int p) -> int {
        assert(grid[i][j] > 0);
        assert(1 <= p and p <= 5000);

        score += C + p;
        ofs << i << ' ' << j << ' ' << p << endl;
        grid[i][j] -= p;
        if (grid[i][j] > 0) {
            return 0;
        }
        broken[i][j] = 1;
        // ここでは2かどうか判別できない
        return 1;
    };
#else
    auto ask = [C, &score, &broken](int i, int j, int p) -> int {
        score += C + p;
        cout << i << ' ' << j << ' ' << p << endl;
        int res;
        cin >> res;
        if (res == 0) {
            return 0;
        }
        broken[i][j] = 1;
        return res;
    };
#endif

    vector<pii> water(W), house(K);
    rep(i, W) {
        auto& [h, w] = water[i];
        cin >> h >> w;
        int u = gridtoid(h, w, N);
        has_water[u] = 1;
    }
    rep(i, K) {
        auto& [h, w] = house[i];
        cin >> h >> w;
        int u = gridtoid(h, w, N);
        house_count[u] = 1;
    }

    auto cost = listnd(N, N, 0);
    vector<int> reserved(N * N);
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> que;
    rep(i, W) {
        rep(j, K) {
            auto [y1, x1] = water[i];
            auto [y2, x2] = house[j];
            Segment<int> seg = {{x1, y1}, {x2, y2}};
            rep(y3, N) {
                rep(x3, N) {
                    // 水源 - 家 ペアを結ぶ線分からの距離をコストに
                    cost[y3][x3] += get_distance_SP(seg, {x3, y3});
                }
            }
        }
    }
    vector<int> is_water(N * N), is_house(N * N);
    rep(i, W) {
        auto [h, w] = water[i];
        int u = gridtoid(h, w, N);
        is_water[u] = 1;
        reserved[u] = 1;
        que.push({cost[h][w], u, -1});
    }
    rep(i, K) {
        auto [h, w] = house[i];
        int u = gridtoid(h, w, N);
        is_house[u] = 1;
        reserved[u] = 1;
        que.push({cost[h][w], u, -1});
    }

    // 破壊にどのくらいかかったか
    vector<int> need(N * N);
    const int BASE = 50;
    const int PENA = 500;
    while (done < K) {
        auto [c, u, prv] = que.top();
        que.pop();
        auto [ch, cw] = idtogrid(u, N);
        if (broken[ch][cw]) continue;
        int power = prv == -1 or u == prv ? BASE : max(need[prv] - BASE, BASE);
        int res = ask(ch, cw, power);
        need[u] = min(need[u] + power, 5000);
        if (res > 0) {
            for (auto [dh, dw] : dir4) {
                int nh = ch + dh;
                int nw = cw + dw;
                if (nh < 0 or nw < 0 or nh >= N or nw >= N) continue;
                int v = gridtoid(nh, nw, N);
                if (broken[nh][nw]) {
                    merge(u, v);
                } else if (not reserved[v]) {
                    reserved[v] = 1;
                    que.push({cost[nh][nw], v, u});
                }
            }
        } else {
            // 水源・家はコストを上げない
            cost[ch][cw] += is_water[u] or is_house[u] ? 0 : PENA;
            que.push({cost[ch][cw], u, u});
        }
    }

#ifdef __LOCAL
    debug(W);
    debug(K);
    debug(C);
#endif

    return score;
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
    auto T = gen_cases2(0, 50);
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
