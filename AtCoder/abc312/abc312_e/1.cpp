/*
参考：TL
・自力ならず。これは気付くべきだったか。。
・3次元、マスを全探索
・制約が小さいので、1*1*1のマス目を全探索できる。
・もし同じテーマが2次元グリッドで出たら自分含めみんな余裕で通すだろうけど、
　3次元空間になるだけで、見た目の見慣れなさもあって解けなくなるもんだな…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

const vector<array<int, 3>> dir3d = {
    {-1, 0, 0},
    {0, -1, 0},
    {0, 0, -1},
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
};

void solve() {
    ll N;
    cin >> N;
    vector<ll> X1(N), Y1(N), Z1(N), X2(N), Y2(N), Z2(N);
    rep(i, N) {
        cin >> X1[i] >> Y1[i] >> Z1[i] >> X2[i] >> Y2[i] >> Z2[i];
    }

    const int M = 100;
    auto grid = listnd(M, M, M, -1);
    rep(i, N) {
        rep(x, X1[i], X2[i]) {
            rep(y, Y1[i], Y2[i]) {
                rep(z, Z1[i], Z2[i]) {
                    grid[x][y][z] = i;
                }
            }
        }
    }

    vector<set<ll>> C(N);
    rep(i, N) {
        rep(x, X1[i], X2[i]) {
            rep(y, Y1[i], Y2[i]) {
                rep(z, Z1[i], Z2[i]) {
                    for (auto [dx, dy, dz] : dir3d) {
                        ll nx = x + dx;
                        ll ny = y + dy;
                        ll nz = z + dz;
                        if (
                            nx < 0 or ny < 0 or nz < 0 or
                            nx >= M or ny >= M or nz >= M
                        ) {
                            continue;
                        }
                        if (
                            grid[nx][ny][nz] != -1 and
                            grid[nx][ny][nz] != i
                        ) {
                            C[i].insert(grid[nx][ny][nz]);
                        }
                    }
                }
            }
        }
    }
    rep(i, N) {
        print(C[i].size());
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
