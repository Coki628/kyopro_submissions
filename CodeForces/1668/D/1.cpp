/*
参考：https://twitter.com/kude_coder/status/1516456639578382337
・自力ならず。。
・区切るDP高速化、累積和、座圧
・まず題意にある最大化を行うDPを考えると、位置rで区切るとした時、
　そこを右端とした区間和の正負0によって得られる値が変わるといった形になる。
　これを全ての左端で試すのを高速化できるといい。
　この時の区間和の正負は、累積和配列上での値の大小関係で決まるので、これをセグ木に乗せる。
　正負0によっての変化はそれぞれ、区間長か-区間長か0で、
　0はそのまま遷移させればいいとして、区間長は遷移先index-遷移元indexをするとよくて、
　これは値の取得時にindexを足して、更新時にindexを引くようにすればセグ木に乗る。
　元々の値はセグ木のindexに使いたいので座圧しておく。
　正と負で最大値取得のセグ木を2本持って、0はvectorとかでいい。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<ll> acc(N+1);
    rep(i, N) {
        acc[i+1] = acc[i] + A[i];
    }
    vector<ll> dp(N+1, -INF);
    dp[0] = 0;
    // rep(i, 1, N+1) {
    //     rep(j, i+1) {
    //         if (acc[j] < acc[i]) {
    //             chmax(dp[i], dp[j] + (i-j));
    //         } elif (acc[j] > acc[i]) {
    //             chmax(dp[i], dp[j] - (i-j));
    //         } else {
    //             chmax(dp[i], dp[j]);
    //         }
    //     }
    // }
    // ll ans = dp[N];
    // print(ans);

    Compress<ll> cp(acc);
    acc = cp.zip(acc);
    ll M = cp.size();
    auto low = get_segment_tree(M, [](ll a, ll b) { return max(a, b); }, -INF);
    auto hi = get_segment_tree(M, [](ll a, ll b) { return max(a, b); }, -INF);
    vector<ll> same(M, -INF);
    low.update(acc[0], 0);
    hi.update(acc[0], 0);
    same[acc[0]] = 0;
    rep(i, 1, N+1) {
        dp[i] = max({low.query(0, acc[i])+i, hi.query(acc[i]+1, M)-i, same[acc[i]]});
        low.update(acc[i], max(low[acc[i]], dp[i]-i));
        hi.update(acc[i], max(hi[acc[i]], dp[i]+i));
        chmax(same[acc[i]], dp[i]);
    }
    ll ans = dp[N];
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
