/*
・自力ならず。これもひどい。
・前後からどこまで行けるか取っておいて、
　にぶたんで元の長さに届く個数を取る。そこまで方針は立ってた。
　どこまで行けるかの判定でLCSを考えてしまったんだけど、
　普通に先頭からのやつだけだよね。それはLCSじゃない。
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
    string T;
    cin >> T;
    ll M = T.size();
    vector<string> S(N);
    cin >> S;

    auto calc = [M](string S, string T) {
        ll i = 0;
        rep(j, S.size()) {
            if (T[i] == S[j]) {
                i++;
            }
            if (i == M) break;
        }
        return i;
    };
    vector<ll> L(N), R(N);
    auto revT = reversed(T);
    rep(i, N) {
        L[i] = calc(S[i], T.substr(0, min((ll)S[i].size(), M)));
        R[i] = calc(reversed(S[i]), revT.substr(0, min((ll)S[i].size(), M)));
    }
    ll ans = 0;
    sort(ALL(R));
    rep(i, N) {
        ans += N - bisect_left(R, M - L[i]);
    }
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
