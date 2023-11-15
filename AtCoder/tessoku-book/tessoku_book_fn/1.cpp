/*
・きっちり自力AC！
・座圧してin-place DP
・flight[i] := 飛行機iで移動中状態の最大利得
　みたいに持っておいて、隣接リストで出発と到着の遷移を適切に作れば、
　時刻を1つずつ前に進めながら、頂点(空港)の状態は上書きしつつ、
　全ての頂点に対するDPを最後の時刻まで進められる。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> A(M), S(M), B(M), T(M);
    Compress<ll> cp;
    rep(i, M) {
        cin >> A[i] >> S[i] >> B[i] >> T[i];
        A[i]--, B[i]--;
        T[i] += K;
        cp.add(S[i]);
        cp.add(T[i]);
    }
    cp.build();
    ll L = cp.size();

    vvl depart(L), arrive(L);
    rep(i, M) {
        depart[cp[S[i]]].eb(i);
        arrive[cp[T[i]]].eb(i);
    }

    vector<ll> dp(N), flight(M);
    rep(t, L) {
        for (ll i : arrive[t]) {
            chmax(dp[B[i]], flight[i]);
        }
        for (ll i : depart[t]) {
            flight[i] = dp[A[i]] + 1;
        }
    }
    ll ans = max(dp);
    print(ans);
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
