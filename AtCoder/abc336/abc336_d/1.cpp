/*
・なんとか自力AC！
・ピラミッド、山型の数列
・決め打ちにぶたん、セグ木、左右で分けて処理
・それぞれの位置が必要な数足りてるかを判定してくんだけど、
　条件が階段状のままだとやりづらいので、index引いたりで平らにする。
　これを左右両方用意しておく。山が小さい分にはさらに引いて作れるはずなので、
　決め打ちにぶたんでシミュる。位置iを頂点にして作れるか、
　を全部試して、左右両方OKだった場所があれば可、とする。
・最初全体加算じゃなくて区間加算が必要な気がしてしまい、
　遅延セグ木を呼んでたんだけど、本番中はそのまま投げてAC1.91秒。
　終了後普通のセグ木に置き換えたら、想像以上に速くなってAC0.41秒。
・なお、にぶたん要らなそうだなーって思ったけどやっぱ要らなかった。
　各位置で「高さいくつのやつまで作れるか？」が求まる(はずな)ので、
　それを左右作っといてminしたmaxでいい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    vector<ll> A(N);
    cin >> A;

    vector<ll> L(N), R(N);
    rep(i, N) {
        L[i] = A[i] - (i + 1);
        R[i] = A[i] - (N - i);
    }
    ll res = bisearch_max(0, ceil(N, 2LL) + 1, [&](ll k) {
        ll len = 2 * k - 1;
        if (len > N) return false;
        vector<ll> goodl(N), goodr(N);
        // auto segl = get_lazy_segment_tree(L, f, g, h, T, E);
        // auto segr = get_lazy_segment_tree(R, f, g, h, T, E);
        auto segl = get_segment_tree(L, [](ll a, ll b) { return min(a, b); }, INF);
        auto segr = get_segment_tree(R, [](ll a, ll b) { return min(a, b); }, INF);
        ll add = 0;
        rep(i, k - 1, N) {
            ll mn = segl.query(i + 1 - k, i + 1) + add;
            if (mn >= 0) {
                goodl[i] = true;
            }
            // segl.update(0, N, 1);
            add++;
        }
        add = 0;
        rep(i, N - k, -1, -1) {
            ll mn = segr.query(i, i + k) + add;
            if (mn >= 0) {
                goodr[i] = true;
            }
            // segr.update(0, N, 1);
            add++;
        }
        rep(i, N) {
            if (goodl[i] and goodr[i]) {
                return true;
            }
        }
        return false;
    });
    print(res);
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
