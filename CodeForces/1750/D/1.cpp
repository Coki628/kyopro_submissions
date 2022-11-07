/*
・なんとか自力AC！
・素因数分解、ビット全探索、包除原理
・まず降順ソートじゃないやつは弾く。
　で、2つ目以降、変化したGCD=A[i]で素因数分解して、直前より減った素因数に注目。
　この位置の要素にはこれらが(このA[i]より多くは)使えないので、
　それに該当する数をM以下のA[i]の倍数から引く。
　このままだとor条件でつらいので、これらの素因数でビット全探索して、
　立ってるビットの偶奇で包除するやつをやる。
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

#include "numbers/FastPrimeFactorization.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    cin >> A;

    if (reversed(sorted(A)) != A) {
        print(0);
        return;
    }

    mint ans = 1;
    HashMap<ll, ll> C;
    for (auto [k, v] : FastPrimeFactorization::factorize(A[0])) {
        C[k] = v;
    }
    rep(i, 1, N) {
        if (A[i] == A[i-1]) {
            // M以下のA[i]の倍数何でもOK
            ans *= M / A[i];
        } else {
            HashMap<ll, ll> nxt;
            for (auto [k, v] : FastPrimeFactorization::factorize(A[i])) {
                // assert(v <= C[k]);
                if (v > C[k]) {
                    print(0);
                    return;
                }
                nxt[k] = v;
            }
            vector<ll> cur;
            for (auto [k, v] : C) {
                if (not nxt.count(k) or nxt[k] < C[k]) {
                    cur.eb(k);
                }
            }
            C = nxt;
            ll n = cur.size();
            mint val =  M / A[i];
            rep(bit, 1, 1<<n) {
                ll b = A[i];
                rep(j, n) {
                    if (bit>>j & 1) {
                        b *= cur[j];
                    }
                }
                if (popcount(bit)%2 == 1) {
                    val -= M / b;
                } else {
                    val += M / b;
                }
            }
            ans *= val;
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
