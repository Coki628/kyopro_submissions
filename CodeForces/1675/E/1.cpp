/*
・なんとか自力AC。でも時間切れで終了後15分くらい…。
・辞書順最小、グラフに帰着、UF
・同じ文字が全て同時に変化する設定なので、文字種毎に同一視するUFをやる。
　26個の超頂点作っておいて、最初は元の文字の頂点とだけ連結。
　操作する時は、前から見ていって、1文字動かす時には、
　その文字と1文字手前の文字の頂点を繋ぐ。
　これで手前で連結済の文字は何回も見なくて済む。
・なんだけど、文字種の頂点を呼ぶのに番号にN足し忘れる添字ミスとかで、
　やたら時間かかってしまって時間切れだった…。
　Dで時間取られたのもあるとはいえ悔しい。
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

void solve() {
    ll N, K;
    cin >> N >> K;
    string S;
    cin >> S;

    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] - 'a';
    }
    ll M = 26;
    vector<ll> C(N+M, M);
    ll c = 0;
    rep(i, N, N+M) {
        C[i] = c;
        c++;
    }
    UnionFind uf(N+M);
    rep(u, N) {
        ll v = N + A[u];
        ll ra = uf.find(u);
        ll rb = uf.find(v);
        ll r = uf.merge(u, v);
        chmin(C[r], C[ra]);
        chmin(C[r], C[rb]);
    }
    rep(i, N) {
        while (K and C[uf.find(i)] > 0) {
            ll u = N + C[uf.find(i)];
            ll v = u - 1;
            if (uf.same(u, v)) break;
            ll ra = uf.find(u);
            ll rb = uf.find(v);
            ll r = uf.merge(u, v);
            chmin(C[r], C[ra]);
            chmin(C[r], C[rb]);
            K--;
        }
    }
    string ans;
    rep(i, N) {
        ans += 'a' + C[uf.find(i)];
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
