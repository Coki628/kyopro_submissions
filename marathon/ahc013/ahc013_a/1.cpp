/*
・とりあえず初期解。右と下に適当に繋いで、
　スコア計算関数サンプルからパクってきて自分のコードに合うように調整した。
　これはサンプルとほぼ同じくらいで26000点くらい。
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

struct MoveAction {
    int before_row, before_col, after_row, after_col;
    MoveAction(int before_row, int before_col, int after_row, int after_col) : 
        before_row(before_row), before_col(before_col), after_row(after_row), after_col(after_col) {}
};
ostream &operator<<(ostream &os, const MoveAction &ma) {
    return os << ma.before_row << ' ' << ma.before_col << ' ' << ma.after_row << ' ' << ma.after_col;
}

struct ConnectAction {
    int c1_row, c1_col, c2_row, c2_col;
    ConnectAction(int c1_row, int c1_col, int c2_row, int c2_col) : 
        c1_row(c1_row), c1_col(c1_col), c2_row(c2_row), c2_col(c2_col) {}
};
ostream &operator<<(ostream &os, const ConnectAction &ca) {
    return os << ca.c1_row << ' ' << ca.c1_col << ' ' << ca.c2_row << ' ' << ca.c2_col;
}

struct Result {
    vector<MoveAction> move;
    vector<ConnectAction> connect;
    Result(const vector<MoveAction> &move, const vector<ConnectAction> &con) : move(move), connect(con) {}
};

struct UnionFind {
    map<pair<int,int>, pair<int, int>> parent;
    UnionFind() :parent() {}

    pair<int, int> find(pair<int, int> x)
    {
        if (parent.find(x) == parent.end()) {
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

int calc_score(int N, vvi field, const Result &res) {
    for (auto r : res.move) {
        assert(field[r.before_row][r.before_col] != 0);
        assert(field[r.after_row][r.after_col] == 0);
        swap(field[r.before_row][r.before_col], field[r.after_row][r.after_col]);
    }

    UnionFind uf;
    for (auto r : res.connect) {
        pair<int, int> p1(r.c1_row, r.c1_col), p2(r.c2_row, r.c2_col);
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
    rep(i, N) {
        string s;
        cin >> s;
        rep(j, N) {
            grid[i][j] = s[j] - '0';
        }
    }

    auto colors = grid;
    auto used = listnd(N, N, false);
    auto can_connect = [&](int h1, int w1, int h2, int w2) -> bool {
        if (grid[h1][w1] != grid[h2][w2]) {
            return false;
        }
        assert(h1 == h2 or w1 == w2);
        if (h1 == h2) {
            if (w1 > w2) swap(w1, w2);
            rep(w, w1+1, w2) {
                if (used[h1][w] or colors[h1][w] > 0) {
                    return false;
                }
            }
            return true;
        } elif (w1 == w2) {
            if (h1 > h2) swap(h1, h2);
            rep(h, h1+1, h2) {
                if (used[h][w1] or colors[h][w1] > 0) {
                    return false;
                }
            }
            return true;
        } else {
            assert(0);
        }
    };
    auto connect = [&](int h1, int w1, int h2, int w2) -> void {
        assert(grid[h1][w1] == grid[h2][w2]);
        assert(h1 == h2 or w1 == w2);
        if (h1 == h2) {
            if (w1 > w2) swap(w1, w2);
            rep(w, w1+1, w2) {
                used[h1][w] = true;
                colors[h1][w] = colors[h1][w1];
            }
        } elif (w1 == w2) {
            if (h1 > h2) swap(h1, h2);
            rep(h, h1+1, h2) {
                used[h][w1] = true;
                colors[h][w1] = colors[h1][w1];
            }
        } else {
            assert(0);
        }
    };

    vector<ConnectAction> edges;
    bool full = false;
    rep(i, N) {
        rep(j, N) {
            if (grid[i][j]) {
                rep(k, i+1, N) {
                    if (grid[k][j] > 0) {
                        if (can_connect(i, j, k, j)) {
                            connect(i, j, k, j);
                            edges.pb({i, j, k, j});
                        }
                        break;
                    }
                }
                if (edges.size() == K2) {
                    full = true;
                    break;
                }
                rep(k, j+1, N) {
                    if (grid[i][k] > 0) {
                        if (can_connect(i, k, i, j)) {
                            connect(i, j, i, k);
                            edges.pb({i, j, i, k});
                        }
                        break;
                    }
                }
                if (edges.size() == K2) {
                    full = true;
                    break;
                }
            }
        }
        if (full) break;
    }

    #ifdef __LOCAL
        ofs << 0 << endl;
        ofs << edges.size() << endl;
        for (auto& edge : edges) {
            ofs << edge << endl;
        }
    #else
        print(0);
        print(edges.size());
        print(edges, '\n');
    #endif

    Result res({{}, edges});
    ld score = calc_score(N, grid, res);
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
