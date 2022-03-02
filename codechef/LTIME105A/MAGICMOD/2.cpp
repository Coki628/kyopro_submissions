/*
・これは途中でやった方針。1にする要素を決め打って、
　倍数としてそこを通るような値にしたいので、約数で探す。
　結果的にはこれだと候補の値を全く網羅できてない。
　でも約数列挙の方針だし、これが正解にいくらか近かったんだな。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A =  LIST(N);

    UNIQUE(A);
    if (A.size() < N) {
        NO();
        return;
    }

    vector<ll> expected(N);
    iota(ALL(expected), 1);
    if (A == expected) {
        YES();
        return;
    }

    rep(i, N) {
        if (A[i] <= N) continue;
        ll x = A[i]-1;
        for (auto mod : divisors(x)) {
            if (mod <= N) continue;
            set<ll> cur;
            bool ok = true;
            rep(j, N) {
                ll a = A[i]%mod;
                if (a > N or cur.count(a)) {
                    ok = false;
                    break;
                }
                cur.insert(a);
            }
            if (ok) {
                cout << "YES " << mod << '\n';
                return;
            }
        }
    }
    NO();
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
