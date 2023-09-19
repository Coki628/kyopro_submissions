/*
・自力ならず。こどふぉはこーいうの落とすからキツい。
・自力では上位ビットから貪欲、、とか考えてたけど、そんなの必要ない。
　全部やるか全部やらないかのどっちか。
・小さいケースで実験ちゃんとやって復元まで見れば気付けたっぽいかな。
　やっぱ面倒がらずにやるべきなんだよなぁ…。
・あとは、Nが奇数だとして、Bjとor取れば必ず全要素でBjで立ってるビットは立つんだから、
　最終的なxorでも必ず奇数個になって、最大化についてこれに損はない、
　逆もそう、みたいな考察が立てれたら良かったんだろうな…。
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
    vector<ll> A(N), B(M);
    cin >> A >> B;

    ll ball = 0;
    rep(i, M) {
        ball |= B[i];
    }
    vector<ll> A2 = A;
    rep(i, N) {
        A2[i] |= ball;
    }
    ll ans1 = 0, ans2 = 0;
    rep(i, N) {
        ans1 ^= A[i];
    }
    rep(i, N) {
        ans2 ^= A2[i];
    }
    if (N % 2 == 0) {
        swap(ans1, ans2);
    }
    print(mkp(ans1, ans2));
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
