/*
・きっちり自力AC！
・素数列挙、枝刈り、オーバーフロー
・3乗だからまあすぐでかくなるだろうと思って普通にループ回した。
　とりあえずNが10^18でオーバーフローが怖いのでそこのチェックは念入りにやった。
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
using mint = ModInt<MOD>;
#include "template.hpp"

vector<ll> eratosthenes_sieve(ll n) {
    vector<bool> table(n+1);
    vector<ll> primes;
    rep(i, 2, n+1) {
        if (!table[i]) {
            primes.eb(i);
            for (ll j=i+i; j<=n; j+=i) {
                table[j] = true;
            }
        }
    }
    return primes;
}

void solve() {
    ll N;
    cin >> N;

    auto primes = eratosthenes_sieve(10000000);
    ll M = primes.size();
    vector<ll> ans;
    rep(i, M) {
        ll p = primes[i];
        rep(j, i+1, M) {
            if (mul_overflow(primes[j], primes[j])) break;
            ll q = primes[j] * primes[j];
            if (mul_overflow(q, primes[j])) break;
            q *= primes[j];
            if (mul_overflow(p, q)) break;
            ll pq = p * q;
            if (pq > N) break;
            ans.eb(pq);
        }
    }
    UNIQUE(ans);
    print(ans.size());
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
