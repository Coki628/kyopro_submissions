/*
・なんとか時間内自力AC…。
・どはまり。最初これ何でもいけない？ってmax(A)-min(A)やってWA食らって、
　おいおい制約2000じゃん両端全探索しないとダメ系か、
　ってその線で考えた時から敗北が確定してた…。
　結局相当悩んだ後、A[0]固定で回すかA[N-1]固定で回すか両方回して隣接チェック、
　ってやってダメで、よくよく見たら隣接の前後が逆になってて、それ直したら通った…
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

    if (N == 1) {
        print(0);
        return;
    }

    ll ans = -INF;
    rep(i, 1, N) {
        chmax(ans, A[i]-A[0]);
    }
    rep(i, N-1) {
        chmax(ans, A[N-1]-A[i]);
    }
    rep(i, N) {
        chmax(ans, A[i]-A[(i+1)%N]);
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
