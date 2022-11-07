/*
参考：みんなのツイート
・next_permutation
・C++のnext_permutationは、渡した数列を辞書順で次の列にしてくれるらしい。
　まあ名前的にそれはそう…。最初見た時、なんだこの使いづらいのは、
　って早々にpythonのpermutations風のラッパー作って使ってたから、そうやって使えるの気付かなかった…
　で、元の列を正負逆にすれば次じゃなくて1つ前も取れる、と。
　prev_permutationってのもあって、そっちなら一発で取れる。
・なんか名前の割に、順列に限らず任意の列に対して辞書順で次を出してくれるようなので、
　もしかしたら今後使える機会があるかもしれない。
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

    prev_permutation(ALL(A));
    print(A);
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
