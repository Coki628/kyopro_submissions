/*
・自力ならず。。
・等差数列の和、三分探索
・各A[i],B[i]を初項と末項だけ持つ。各iでの累積の操作自体は別のiに影響しないので個別に処理できる。
　前のiでの結果(末項)だけを次のiに足し込めばいい。
　累積の結果については、1回目は掛け算で、2回目は等差数列の和で求まる。
　さて、ここまでの方針は自分でもだいたい出てたんだけど、
　真ん中あたりの項が最大値を取る時、これをどう確認すればいいか分からなかった。
・等差数列の和は項数nについての2次関数なので、極値を三分探索で求められる。
　これに気付ければよかったんだけど、見えなかったなー。。
・あと三分探索を書いた後も、WAが取れなくて悩んだ。
　結局、三分探索内での-INFが10^18で足りてなくてオーバーフローしてた。。
　ライブラリ内のINFを直した。ここは逆側に溢れる心配ないから10^18である必要ないし。
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

#include "numbers/arithmetic_sequence_sum.hpp"
#include "common/trisearch.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> X(N), Y(N);
    rep(i, N) {
        cin >> X[i] >> Y[i];
    }

    ll ans = -INF;
    vector<pll> B(N), A(N);
    B[0].first = X[0];
    B[0].second = X[0]*Y[0];
    rep(i, 1, N) {
        B[i].first = X[i]+B[i-1].second;
        B[i].second = X[i]*Y[i]+B[i-1].second;
    }
    A[0].first = B[0].first;
    A[0].second = arithmetic_sequence_sum(B[0].first, X[0], Y[0]);
    auto [id, val] = trisearch_max(1, Y[0]+1, [&](ll m) -> ll {
        return arithmetic_sequence_sum(B[0].first, X[0], m);
    });
    chmax(ans, val);
    rep(i, 1, N) {
        A[i].first = B[i].first+A[i-1].second;
        A[i].second = arithmetic_sequence_sum(B[i].first, X[i], Y[i])+A[i-1].second;
        auto [id, val] = trisearch_max(1, Y[i]+1, [&](ll m) {
            return arithmetic_sequence_sum(B[i].first, X[i], m)+A[i-1].second;
        });
        chmax(ans, val);
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
