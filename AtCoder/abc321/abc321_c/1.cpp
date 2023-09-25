/*
・自力AC！
・再帰全探索
・桁数毎にまとめて追加してく。各桁数でいくつあるかは再帰全探索した。
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
    ll K;
    cin >> K;

    ll cur = 0;
    rep(d, 1, 11) {
        vector<string> nums;
        string s;
        auto rec = [&](auto&& f, ll i, ll a) {
            if (i == d) {
                nums.eb(s);
                return;
            }
            rep(nxt, 10) {
                if (i == 0 and nxt == 0) continue;
                if (a <= nxt) continue;
                s.pb('0' + nxt);
                f(f, i + 1, nxt);
                s.pop_back();
            }
        };
        rec(rec, 0, INF);
        if (cur + nums.size() < K) {
            cur += nums.size();
        } else {
            sort(ALL(nums));
            rep(i, nums.size()) {
                cur++;
                if (cur == K) {
                    print(nums[i]);
                    return;
                }
            }
            assert(0);
        }
    }
    assert(0);
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
