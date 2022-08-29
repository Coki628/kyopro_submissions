/*
・期待値DPのこと
・自己ループあり
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

void solve() {
    ll N = 4;
    vector<string> grid(N+2);
    grid[0] = string(N+2, '.');
    grid[N+1] = string(N+2, '.');
    rep(i, 1, N+1) {
        string s;
        cin >> s;
        grid[i] = '.' + s + '.';
    }
    N += 2;

    ll bit = 0;
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (grid[i][j] == '#') {
                ll id = gridtoid(i, j, N);
                bit |= 1LL<<id;
            }
        }
    }

    map<ll, ld> memo;
    auto rec = [&](auto&& f, ll bit) -> ld {
        if (memo.count(bit)) {
            return memo[bit];
        }
        // 的が全部なくなったら終了
        if (!bit) return 0;
        ld res = INF;
        ld total = 5;
        // 狙う対象にする位置を全部試す
        rep(i, 1, N-1) {
            rep(j, 1, N-1) {
                ll id = gridtoid(i, j, N);
                ld exp = 0, cost = 1;
                ll cnt = 0;
                // この場所に的があるか
                if (bit>>id & 1) {
                    // 次の遷移先にidを選んだ場合の (この先でかかる分+今回かかる分) * そうなる確率(1/5)
                    exp += (f(f, bit^1LL<<id)+cost) / total;
                    cnt++;
                }
                // 四方も見る
                for (auto [di, dj] : directions) {
                    ll ni = i + di;
                    ll nj = j + dj;
                    id = gridtoid(ni, nj, N);
                    if (bit>>id & 1) {
                        exp += (f(f, bit^1LL<<id)+cost) / total;
                        cnt++;
                    }
                }
                if (cnt) {
                    // 自己ループ分のコスト * そうなる確率
                    exp += cost * (total-cnt)/total;
                    // 自己ループ補正「1回の遷移の総数/自己ループにならずに遷移する数」を掛ける
                    exp *= total / cnt;
                    chmin(res, exp);
                }
            }
        }
        memo[bit] = res;
        return res;
    };
    ld res = rec(rec, bit);
    print(res);
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
