/*
・自力ならず。。分かってみれば典型考察で解きたい系だった。
・約数の性質、平方数、累積XOR、zero sum ranges系、余事象
・まず、約数の個数が偶数って所で性質が見抜けずにうんうん言って終わってしまった。
　確かに約数って平方数の時以外は全部ペアになるから、平方数かどうかが偶奇だった。
　で、これで区間XORが平方数になる区間の個数が分かれば答えの余事象が求まったことになる。
　区間XORがある数になる数え上げは累積和みたくzero sum rangesの要領でできる。
　これ何度もやってるのに身についてないなー…。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    vector<ll> acc(N + 1);
    rep(i, N) {
        acc[i + 1] = acc[i] ^ A[i];
    }
    ll L = 1LL << bit_length(N);
    vector<ll> C(L);
    ll sub = 0;
    rep(i, N + 1) {
        ll j = 0;
        while (j * j < L) {
            ll sq = j * j;
            sub += C[acc[i] ^ sq];
            j++;
        }
        C[acc[i]]++;
    }
    ll total = N * (N + 1) / 2;
    ll ans = total - sub;
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
