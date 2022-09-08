/*
・なんとか自力AC！
・括弧列典型ってことでとりあえず+-の数列にして考える。
　連結が増やせるかどうかは、開き括弧が来た時に、1つ手前の同じ深さの所と対応できるかどうかで、
　これはそこまでの区間に浅くなった場所がないかどうかで判定できる(んじゃないかと思ってる)。
　区間最小をセグ木で取れば高速にチェックできる。
・なんか終了後TL眺めてたらすごく単純な判定で解けたっぽい話だったので悲しみ…。
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
    string S;
    cin >> S;
    N *= 2;

    vector<ll> A(N);
    ll cur = 0;
    rep(i, N) {
        A[i] = cur;
        if (S[i] =='(') {
            cur++;
        } else {
            cur--;
        }
    }

    auto seg = get_segment_tree(A, [](ll a, ll b) { return min(a, b); }, INF);
    ll ans = N / 2;
    vector<ll> prv(N, -1);
    rep(i, N) {
        if (prv[A[i]] != -1 and S[i] == '(') {
            ll j = prv[A[i]];
            if (seg.query(j, i) >= A[i]) {
                ans--;
            }
        }
        prv[A[i]] = i;
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
