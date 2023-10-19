/*
参考：https://github.com/E869120/kyopro-tessoku/blob/main/editorial/chap06/chap06.pdf
・上限値を考える
・これは方針詰まった。なんかランレングスとかやろうとしてガチャガチャやって、
　境界の処理とかでグチャグチャになってた。良くない。
・一度に全部考えようとしないで、<と>の条件を分けて考えれば良かった。
　それで最後に強い方の条件を優先させて答えに反映させればいい。
・なんかこういうたまに明らかに格下のはずの考察で詰まるのを、
　きっちり拾って詰まらず考えられるようにならないとなー。
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
    string S;
    cin >> S;

    vector<ll> cond1(N), cond2(N);
    // ai<ai+1に関する条件を左から見て行く
    cond1[0] = 1;
    rep(i, N - 1) {
        if (S[i] == 'A') {
            cond1[i + 1] = cond1[i] + 1;
        } else {
            cond1[i + 1] = 1;
        }
    }
    // ai>ai+1に関する条件を右から見て行く
    cond2[N - 1] = 1;
    rep(i, N - 2, -1, -1) {
        if (S[i] == 'B') {
            cond2[i] = cond2[i + 1] + 1;
        } else {
            cond2[i] = 1;
        }
    }
    ll ans = 0;
    rep(i, N) {
        ans += max(cond1[i], cond2[i]);
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
