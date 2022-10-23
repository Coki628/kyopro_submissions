/*
ライブラリ整備：Fraction
・Fractionクラスでやってみた。やっぱ遅くなった。1.41秒。。
　でも色々ライブラリのバグ取りはできたからまあOK。
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

#include "numbers/Fraction.hpp"
using Frac = Fraction<ll>;

void solve() {
    ll N;
    Frac len;
    cin >> N >> len;
    vector<Frac> W(N), X(N);
    vector<ll> V(N);
    rep(i, N) {
        cin >> W[i] >> X[i] >> V[i];
    }

    Frac ans = 0;
    rep(i, N) {
        vector<tuple<Frac, ll, ll>> events;
        Frac sm = 0;
        rep(j, N) {
            // 速度が同じなら初期位置で判定
            if (V[j] == V[i]) {
                if (X[i] <= X[j] and X[j] <= X[i]+len) {
                    sm += W[j];
                }
            } else {
                // xi + t*vi = xj + t*vj を式変形
                auto tl = (X[i]-X[j]) / (V[j]-V[i]);
                auto tr = (X[i]-X[j]+len) / (V[j]-V[i]);
                if (tl > tr) swap(tl, tr);
                if (tr < 0) continue;
                chmax(tl, (Frac)0);
                events.eb(tl, 0, j);
                events.eb(tr, 1, j);
            }
        }
        sort(ALL(events));
        chmax(ans, sm);
        for (auto [pos, type, j] : events) {
            if (type == 0) {
                sm += W[j];
            } else {
                sm -= W[j];
            }
            chmax(ans, sm);
        }
    }
    assert(ans.denominator == 1);
    print(ans.numerator);
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
