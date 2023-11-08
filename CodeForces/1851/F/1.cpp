/*
・自力AC！
・ビット演算、ビット毎に見る、上位桁から貪欲に決める、集合を2つに分けていく再帰探索
・色々考察すると、選ぶペアのビットが(0,0)か(1,1)なら、
　xを逆側とすることでそのビットを立てれるのが分かる。
　これで候補になる要素の集合を半分ずつにしていけるので、再帰探索する。
　半分のどちらもペアを作れない時だけ、そのビットを諦めて集合そのままで探索を続ける。
・公式解や他の人の方法を。
　(ai^x)&(aj^x)の最大化は(ai^aj)の最小化に帰着できて、
　これはabc308_gでソートして隣接見ればOKが目から鱗だったやつ。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    ll mx = -INF;
    vector<ll> vec(N);
    iota(ALL(vec), 0);
    array<ll, 3> ans;
    auto rec = [&](auto &&f, ll k, vector<ll>& vec, ll x, ll val) -> void {
        if (k < 0) {
            if (vec.size() >= 2 and chmax(mx, val)) {
                ans = {vec[0] + 1, vec[1] + 1, x};
            }
            return;
        }
        vector<ll> v1, v2;
        rep(i, vec.size()) {
            if (A[vec[i]] >> k & 1) {
                v1.eb(vec[i]);
            } else {
                v2.eb(vec[i]);
            }
        }
        if (v1.size() >= 2) {
            f(f, k - 1, v1, x, val + (1LL << k));
        }
        if (v2.size() >= 2) {
            f(f, k - 1, v2, x + (1LL << k), val + (1LL << k));
        }
        if (v1.size() < 2 and v2.size() < 2) {
            f(f, k - 1, vec, x, val);
        }
    };
    rec(rec, K - 1, vec, 0, 0);
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
