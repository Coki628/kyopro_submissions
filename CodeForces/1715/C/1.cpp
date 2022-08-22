/*
参考：https://twitter.com/hamamu_kyopro/status/1561285771234910209
・自力ならず…。
・更新した時に周囲だけ再計算すればいいんだけど、
　要素をベースに考えたら色々破滅して終了…。
　境界をベースに考えるとよかったぽい。境界が変化した時 i*(N-i) みたいにできる。
　って話聞いてなるほどー、って実装したのに通らない。
　通ってる実装見ると確かにもっと何かゴニョゴニョしてるので、
　きっとなんか考慮が足りてないんだけど、
　これの提出見るとランダムケースがそこそこいい所まで通っちゃってるので、
　何がいけないのかよく分からない。
　そのうちやる気がある時にupsolveしようと思う。
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
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);

    ll ans = N*(N+1) / 2;
    rep(i, N-1) {
        if (A[i] != A[i+1]) {
            ans += (i+1) * (N-(i+1));
        }
    }
    rep(_, M) {
        ll i, x;
        cin >> i >> x;
        i--;
        if (A[i] == x) continue;
        if (i > 0) {
            if (A[i-1] == A[i] and A[i-1] != x) {
                ans += i * (N-i);
            }
            if (A[i-1] != A[i] and A[i-1] == x) {
                ans -= i * (N-i);
            }
        }
        if (i < N-1) {
            if (A[i] == A[i+1] and x != A[i+1]) {
                ans += (i+1) * (N-(i+1));
            }
            if (A[i] != A[i+1] and x == A[i+1]) {
                ans -= (i+1) * (N-(i+1));
            }
        }
        A[i] = x;
        print(ans);
    }
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
