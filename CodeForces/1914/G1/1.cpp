/*
・終了後ほぼ自力AC？手掛かりはあまり得ていないけど、WAのケースは見に行ってしまった。
・交差する区間、UF
・題意の操作を整理すると、交差する区間(とその間にある区間)は全て芋づる式に処理することができ、
　この中でどの1個を残すか(ここでは交差している区間からしか選べない、内包されてるやつは不可)を選ぶだけになる。
　よって交差する区間をUFで全て繋げて、左から連結成分毎に(内包してるのは無視して)数える。
　UFと一緒に最右の右端を持っておけば、内包飛ばして次の連結成分に進める。
　G1は2乗が効くので、上記さえ整理できれば交差区間を集めるのは愚直でOK。
　(まあその考察整理するまでも大変だったんだけどね…。)
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    N *= 2;
    vector<ll> A(N);
    cin >> A;
    A--;

    vector<pll> prv(N, {-1, -1});
    rep(i, N) {
        if (prv[A[i]].first == -1) {
            prv[A[i]].first = i;
        } else {
            prv[A[i]].second = i;
        }
    }
    UnionFind uf(N);
    vector<ll> R(N);
    iota(ALL(R), 0);
    rep(i, N) {
        if (prv[A[i]].second == i) {
            ll j = prv[A[i]].first;
            uf.merge(i, j, [&](ll r, ll ch) {
                if (r == -1) return;
                chmax(R[r], R[ch]);
            });
            rep(k, j + 1, i) {
                if (prv[A[k]].first == k and prv[A[k]].second > i) {
                    uf.merge(i, k, [&](ll r, ll ch) {
                        if (r == -1) return;
                        chmax(R[r], R[ch]);
                    });
                }
            }
        }
    }
    ll i = 0, mn = 0;
    mint cnt = 1;
    while (i < N) {
        ll r = uf.find(i);
        mn++;
        cnt *= uf.size(r);
        i = R[r] + 1;
    }
    print(mkp(mn, cnt));
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
