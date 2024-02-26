/*
・なんとか自力AC！結構手こずった。。
・三角形の条件、bitDP、数え上げ、重複度で割る
・再帰全探索しようとしたらうまく作れず、
　順列全探索したら12!はでかすぎてTLE、
　直前2回何を選んだか状態に持ってbitDPしてやっと通った。。
　なお、これは順序違いを全部数えてしまっているので、
　重複度で割って最終的に正しい答えにしている。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "combinatorics/factorial.hpp"
#include "combinatorics/ModInt64.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N * 3);
    cin >> A;

    const ull MOD = (1ull << 61ull) - 1;
    using mint = ModInt64<MOD>;
    ll L = N * 3;
    auto dp = listnd(L + 1, L + 1, 1LL << L, (mint)0);
    dp[L][L][0] = 1;
    rep(bit, 1LL << L) {
        rep(i, L + 1) {
            if (i != L and !(bit >> i & 1)) continue;
            rep(j, L + 1) {
                if (j != L and !(bit >> j & 1)) continue;
                if (dp[i][j][bit] == 0) continue;
                rep(k, L) {
                    if (bit >> k & 1) continue;
                    if (popcount(bit) % 3 == 2) {
                        vector<ll> vec = {A[i], A[j], A[k]};
                        sort(ALL(vec));
                        if (vec[0] + vec[1] > vec[2]) {
                            dp[j][k][bit | (1LL << k)] += dp[i][j][bit];
                        }
                    } else {
                        dp[j][k][bit | (1LL << k)] += dp[i][j][bit];
                    }
                }
            }
        }
    }
    mint ans = 0;
    rep(i, L) {
        rep(j, L) {
            ans += dp[i][j][(1LL << L) - 1];
        }
    }
    ans /= pow(factorial<ll>(3), N) * factorial<ll>(N);
    print(ans);
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
