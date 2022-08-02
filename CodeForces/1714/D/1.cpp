/*
・きっちり自力AC！
・DP復元
・こどふぉっぽいDP復元。部分文字列は短いので、切り出しや遷移は愚直でOK。
・なんか貪欲でもいけたらしい。。
　でもその貪欲を正しく思いつける保証もないし、
　このDPでほぼ詰まらずに書けたのでOK。
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
    string S;
    cin >> S;
    ll N = S.size();
    ll M;
    cin >> M;
    vector<string> T(M);
    vvpll nxt(N);
    rep(i, M) {
        cin >> T[i];
        rep(j, N) {
            if (S.substr(j, T[i].size()) == T[i]) {
                nxt[j].eb(i, T[i].size());
            }
        }
    }

    vector<ll> dp(N+1, INF);
    vector<pll> prv(N+1, {-1, -1});
    dp[0] = 0;
    rep(i, N) {
        for (auto [id, sz] : nxt[i]) {
            rep(k, i+1, i+sz+1) {
                if (chmin(dp[k], dp[i]+1)) {
                    prv[k] = {id, i};
                }
            }
        }
    }
    ll mn = dp[N];
    if (mn >= INF) {
        print(-1);
        return;
    }
    print(mn);
    vector<pll> ans;
    ll cur = N;
    while (cur > 0) {
        auto [id, i] = prv[cur];
        ans.eb(id+1, i+1);
        cur = i;
    }
    reverse(ALL(ans));
    print(ans, '\n');
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
