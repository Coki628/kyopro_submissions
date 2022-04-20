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
・「indexを足し引き」が直感的に分かりにくい時、
　遅延セグ木で考察を一段階軽くできると思う。indexによる値の変化は、
　ようは先に進む度、確定済の値の価値が1ずつ上がったり下がったりすることなので、
　今ある値全体に対して+1,-1を作用させるように、区間加算できる遅延セグ木を使えば、
　更新・取得時にindexの足し引きは要らなくなる。
・まあでも、やってみると-1する時-INFがあると正しく動かないので
　初期化をちょっと小さめのINFにしないといけなかったり、
　加算セグ木に1点更新をするために今そこにある値を引かないといけなかったり、
　言うほど直感的にもなってない気がするので何とも言えない。
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

#include "segment/LazySegmentTree.hpp"

// 区間加算・区間最大値取得
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = -INF;
const ll E = 0;

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
    Compress<ll> cp(acc);
    acc = cp.zip(acc);
    ll M = cp.size();
    auto low = get_lazy_segment_tree(vector<ll>(M, -MOD), f, g, h, T, E);
    auto hi = get_lazy_segment_tree(vector<ll>(M, -MOD), f, g, h, T, E);
    vector<ll> same(M, -INF);
    low.update(acc[0], MOD);
    hi.update(acc[0], MOD);
    same[acc[0]] = 0;
    rep(i, 1, N+1) {
        low.update(0, M, 1);
        hi.update(0, M, -1);
        dp[i] = max({low.query(0, acc[i]), hi.query(acc[i]+1, M), same[acc[i]]});
        low.update(acc[i], max(low[acc[i]], dp[i])-low[acc[i]]);
        hi.update(acc[i], max(hi[acc[i]], dp[i])-hi[acc[i]]);
        chmax(same[acc[i]], dp[i]);
        // low.print(M);
        // hi.print(M);
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
