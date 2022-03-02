/*
参考：https://twitter.com/kude_coder/status/1498717652457787393
　　　https://discuss.codechef.com/t/magicmod-editorial/99584
・自力ならず。
・式変形、総和に注目、約数列挙
・個々の要素ではなく総和に注目する。ここが見えづらいと思う。
　完成させる順列をR、答えとなるmodをxとすると、まず個々の要素では
　Ai-Ri = Qi*x のような形を取ることになる。
　しかしA,Rがそれぞれどのiと対応するかは分からないのでこのままでは使えない。
　そこで総和にして、sum(A)-sum(R) = sum(Q)*x とする。
　個々の要素がxの倍数なら総和でもxの倍数であるはずなのでこれはできる。
　これを式変形して (sum(A)-sum(R))/sum(Q) = x とすると、
　これがまたちょっと分かりにくいんだけど、
　例えば a*b = x ならxがaの倍数であるように、
　a/b = x ならxがaの約数であることが成り立つので、
　(やってみると確かにそうだし、倍数・約数の関係からしても確かにそうなりそうではある)
　先程変形した式に適用させると、xはsum(A)-sum(R)の約数であることになる。
　これで答えの候補が探索可能な量に絞られたので、
　sum(A)-sum(R)の約数を全探索して答えが見つかるをチェックすればいい。
・総和に注目する発想は気付くの難しいけど、式変形の結果から答えの候補を
　ある数の約数に絞り込むのは結構汎用性がありそうな気がするから、
　考察の手札として頭の片隅に置いておけるといいかもしれない。
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

    sort(ALL(A));
    vector<ll> R(N);
    iota(ALL(R), 1);
    if (A == R) {
        YES();
        return;
    }

    ll sa = sum(A);
    ll sr = sum(R);
    ll sq = sa-sr;
    if (sq <= 0) {
        NO();
        return;
    }
    for (auto mod : divisors(sq)) {
        vector<ll> cur(N);
        rep(i, N) {
            cur[i] = A[i]%mod;
        }
        sort(ALL(cur));
        if (cur == R) {
            cout << "YES " << mod << '\n';
            return;
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
