/*
・公式解の方針。やっぱ4乗は非想定だったわ。。
・隣接ペア削除、3乗の区間DP
・よく思い返すと、この両端から削除する遷移は隣接ペア削除の区間DPで定番だった。
　今までも多くの問題でこの遷移してる。
　久々だったとはいえ、ちゃんと反応できるようにならないとなー。
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
    int N;
    cin >> N;
    N *= 2;
    vector<int> A(N);
    cin >> A;

    auto memo = listnd(N + 1, N + 1, -1);
    auto rec = [&](auto &&f, int l, int r) -> int {
        int len = r - l;
        if (len == 0) return 0;
        if (len < 0 or len == 1) return MOD;
        if (len == 2) {
            return abs(A[l] - A[l + 1]);
        }
        if (memo[l][r] != -1) return memo[l][r];
        int res = MOD;
        rep(m, l + 1, r) {
            int lval = f(f, l, m);
            if (lval >= MOD) continue;
            int rval = f(f, m, r);
            if (rval >= MOD) continue;
            chmin(res, f(f, l, m) + f(f, m, r));
        }
        int mval = f(f, l + 1, r - 1);
        if (mval < MOD) {
            // 区間[l,r)で(l,r-1)ペアを最後に消す遷移
            chmin(res, mval + abs(A[l] - A[r - 1]));
        }
        return memo[l][r] = res;
    };
    int res = rec(rec, 0, N);
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
