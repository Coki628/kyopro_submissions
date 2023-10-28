/*
・なんとか自力AC。
・グリッド、実装、再帰全探索
・条件通りのチェックをしながら、枝刈りしながら、
　適切に全探索していけばOK。なんだけどまあ大変。
・「ABC..」の順列全探索をベースにする解法だと大分楽だった模様。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    string R, C;
    cin >> R >> C;

    vector<string> ans(N, string(N, '.'));
    auto check = [&](bool is_done = false) {
        vector<ll> rok(N), cok(N);
        auto rcnt = listnd(N, 3, 0);
        auto ccnt = listnd(N, 3, 0);
        rep(h, N) {
            rep(w, N) {
                if (ans[h][w] != '.') {
                    rcnt[h][ans[h][w] - 'A']++;
                    ccnt[w][ans[h][w] - 'A']++;
                    if (rcnt[h][ans[h][w] - 'A'] >= 2) {
                        return false;
                    }
                    if (ccnt[w][ans[h][w] - 'A'] >= 2) {
                        return false;
                    }
                }
                if (not rok[h] and ans[h][w] != '.') {
                    if (R[h] == ans[h][w]) {
                        rok[h] = 1;
                    } else {
                        return false;
                    }
                }
                if (not cok[w] and ans[h][w] != '.') {
                    if (C[w] == ans[h][w]) {
                        cok[w] = 1;
                    } else {
                        return false;
                    }
                }
            }
        }
        if (is_done) {
            rep(i, N) {
                if (count(ALL(rcnt[i]), 1) != 3) {
                    return false;
                }
                if (count(ALL(ccnt[i]), 1) != 3) {
                    return false;
                }
            }
        }
        return true;
    };
    auto rec = [&](auto&& f, ll h, ll w) {
        if (h == N) {
            if (check(true)) {
                Yes();
                print(ans, '\n');
                exit(0);
            } else {
                return;
            }
        }
        for (auto c : string("ABC.")) {
            ans[h][w] = c;
            if (check()) {
                if (w + 1 < N) {
                    f(f, h, w + 1);
                } else {
                    f(f, h + 1, 0);
                }
            }
            ans[h][w] = '.';
        }
    };
    rec(rec, 0, 0);
    No();
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
