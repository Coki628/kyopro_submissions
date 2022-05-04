/*
・なんとか自力AC！終了間際1分前くらいでのブザービート。
・場合分け、CRT
・偶奇それぞれの個数*2が和の周期になるので、うまく一致させられるか見る。
　総和が一定なので、一方決めれば他方が決まるやつなんだけど、
　CRTに乗せる所まで落とし込むのが大変だった。
　例えば奇数側の要素数が5なら周期は10で、
　mod 10の5が実際の奇数側の和になるんだけど、これそのままではダメで、
　5,10,15..となる所を総和から引いた形(つまり偶数側に残る値)にして、例えば総和が41なら、
　36,26,16..として、この値が偶数側のmodで0になるならOK、みたいにしたら通った。
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

#include "acl/math.hpp"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    vvl B(2);
    rep(i, N) {
        B[A[i]%2].eb(A[i]);
    }
    rep(i, 2) sort(ALL(B[i]));

    vector<ll> diff(2), mod(2);
    rep(i, 2) mod[i] = B[i].size() * 2;
    rep(i, 2) {
        rep(j, B[i].size()) {
            diff[i] += B[i][j] - B[i][0];
        }
    }
    rep(i, 2) diff[i] %= mod[i];

    ll total = sum(A);
    if (mod[0] == 0) {
        if (diff[1] == 0) {
            YES();
        } else {
            NO();
        }
    } elif (mod[1] == 0) {
        if (diff[0] == 0) {
            YES();
        } else {
            NO();
        }
    } else {
        auto res = crt({0, (total-mod[1]/2)%mod[1]}, mod);
        if (res.second != 0) {
            YES();
        } else {
            NO();
        }
    }
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
