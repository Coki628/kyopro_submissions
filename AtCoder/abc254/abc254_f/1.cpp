/*
・自力ならず。でもこれは粘れば解けてそう…。D粘着よりこっちちゃんと考えればよかったかなー。。
・セグ木、区間GCD取得、差分GCD
・あるA[i]をB[0],B[1]と足すことを考えると、B[0]とB[1]の差分と、
　B[0]+A[i]とB[1]+A[i]の差分は、どのA[i]を足すにしても変わらないことが分かる。
　ここから、差分だけが重要だと思うと、差分GCDかなって思える。
　あとは基準になる場所1箇所だけ(多分どこでも)拾えばOK。
・制約20万で、セグ木とgcd演算でlog2つ乗るんだけど、余裕のAC0.28秒。
　Sparse Table使えばlog1つ外せるけど、それ試す気もなくなってしまったわ。
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
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);
    auto B = LIST(N);

    vector<ll> C(N), D(N);
    rep(i, N-1) {
        C[i] = abs(A[i+1] - A[i]);
        D[i] = abs(B[i+1] - B[i]);
    }
    auto segc = get_segment_tree(C, [](ll a, ll b) { return gcd(a, b); }, 0LL);
    auto segd = get_segment_tree(D, [](ll a, ll b) { return gcd(a, b); }, 0LL);
    rep(i, Q) {
        ll h1, h2, w1, w2;
        cin >> h1 >> h2 >> w1 >> w2;
        h1--; w1--; h2--; w2--;
        ll res = gcd(vector<ll>{A[h1]+B[w1], segc.query(h1, h2), segd.query(w1, w2)});
        print(res);
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
