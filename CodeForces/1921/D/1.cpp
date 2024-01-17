/*
・なんとか自力AC、きつかった。。
・multisetでシミュ
・ようはどこまで大きい方で使ってどこから小さい方で使うかみたいなことを全探索。
　これを高速に処理するためにA,Bを1個ずつずらしてくみたいにするんだけど、
　最初添字で頑張ろうとしたら脳が破滅したので、multisetで陽に操作することにした。
　まあそれでも大分ゴチャゴチャして大変だったけど…。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N), B(M);
    cin >> A >> B;

    sort(ALL(A));
    sort(ALL(B));
    ll ans = -INF, amnsm = sum(A), amxsm = 0, bmnsm = 0, bmxsm = 0;
    Multiset<ll> amn(ALL(A)), amx, bmn, bmx;
    rep(i, M - 1, M - 1 - N, -1) {
        bmx.insert(B[i]);
        bmxsm += B[i];
    }
    if (amn.back() <= bmx.front()) {
        chmax(ans, abs(bmxsm - amnsm));
    }
    rep(i, N) {
        ll a = amn.pop_back();
        amnsm -= a;
        amx.insert(a);
        amxsm += a;
        ll b = bmx.pop_front();
        bmxsm -= b;
        bmn.insert(B[i]);
        bmnsm += B[i];
        if ((amn.empty() or amn.back() <= bmx.front()) and bmn.back() <= amx.front()) {
            chmax(ans, abs(bmxsm - amnsm) + abs(amxsm - bmnsm));
        }
    }
    print(ans);
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
