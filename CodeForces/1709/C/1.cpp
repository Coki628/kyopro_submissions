/*
・きっちり自力AC！こういうのちゃんと考察できたのは良かった。
・括弧列
・括弧列典型で+-列にして考察すると、
　なるべく+側に寄せた形から1つだけ-側にずらせるか、みたいになる。
　なので、初期状態としては'('を左寄せ')'を右寄せで作る。
　ここから1箇所'('と')'をスワップさせると、間の区間が-2される。
　この時負数にならない、つまり区間最小値が2以上ならできる。
　後はやる場所の候補だけど、実は真ん中1つだけで良かった。
　確かにここが一番影響を受ける区間が狭い。(他でやっても区間が長くなるだけで得がない。)
　これで成功なら2種類作れるのでNO。
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
    
    vector<ll> A(N), V1, V2;
    A[0] = 1;
    ll lcnt = count(ALL(S), '(');
    if (S[0] == '?') lcnt++;
    rep(i, 1, N) {
        if (S[i] == '(') {
            A[i] = A[i-1] + 1;
        } elif (S[i] == ')') {
            A[i] = A[i-1] - 1;
        } else {
            if (lcnt < N/2) {
                A[i] = A[i-1] + 1;
                lcnt++;
                V1.eb(i);
            } else {
                A[i] = A[i-1] - 1;
                V2.eb(i);
            }
        }
    }

    if (V1.size() and V2.size()) {
        ll l = V1.back();
        ll r = V2[0];
        ll mn = INF;
        rep(i, l, r) {
            chmin(mn, A[i]);
        }
        if (mn >= 2) {
            NO();
            return;
        }
    }
    YES();
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
