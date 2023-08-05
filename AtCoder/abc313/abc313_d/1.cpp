/*
参考：https://twitter.com/deuteridayodayo/status/1687822610581893122
・自力ならず。。悔しい。
・インタラクティブ、xorの性質
・偶奇の問題なんだけど、xorだと思って考えれば良かったと思う。
　1つ除いたやつのxorを全部合わせると全体xorになるってやつ。
　これさえ思い出せれば最初のK+1個が分かるからその先も求まった。
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

ll ask(vector<ll> &A) {
    A++;
    cout << "?";
    for (auto a : A) {
        cout << " " << a;
    }
    cout << endl;
    ll res;
    cin >> res;
    res--;
    return res;
}

void answer(vector<ll> &A) {
    A++;
    cout << "!";
    for (auto a : A) {
        cout << " " << a;
    }
    cout << endl;
}

void solve() {
    ll N, K;
    cin >> N >> K;

    // A[i] := [0,K+1)でi番目を除いたxor
    vector<ll> A(K + 1), ans(N);
    rep(i, K + 1) {
        vector<ll> cur;
        rep(j, K + 1) {
            if (i == j) continue;
            cur.eb(j);
        }
        A[i] = ask(cur);
    }
    // xorall := [0,K+1)の全xor
    ll xorall = 0;
    rep(i, K + 1) {
        xorall ^= A[i];
    }
    rep(i, K + 1) {
        ans[i] = A[i] ^ xorall;
    }
    // 先頭K-1個をK+1以降を求めるのに使う
    vector<ll> base(K - 1);
    ll xorbase = 0;
    rep(i, K - 1) {
        base[i] = i;
        xorbase ^= ans[i];
    }
    rep(i, K + 1, N) {
        auto cur = base;
        cur.eb(i);
        ll res = ask(cur);
        ans[i] = res ^ xorbase;
    }
    answer(ans);
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
