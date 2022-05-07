/*
・自力AC！やったね！
・主客転倒、差分、累積和
・まず、要素ではなく差分にして見る。すると、
　各クエリ毎にある量の差分が左右の要素どちらかから食い潰されていくような形になる。
　この状態で状態の変化をクエリ毎ではなく差分毎にまとめて見ることにすると、
　ある差分がどこまで残っているかが分かれば、そこまでに左右からどれくらいずつ取られるかは、
　移動の正負で累積和を分けて持っておけば分かる。差分がどこまで残っているかは、
　両方を合わせた消費量の累積和でにぶたんすれば分かる。
　これでほぼまとめて処理できるので、端数だけ別途やればいい。
　どの段階で正負にどのくらい消費するかはクエリを見てシミュレーションしておける。
・元の値から差分になること、座標の軸とクエリの軸で添字が2方向になること、
　クエリ側の軸で累積和すること、などがあり、まあまあゴチャゴチャする。
　累積和にぶたんから取る右端rはクエリの軸なのに、
　条件をr < Nとしてしまっていたバグを発見するのにちょっと時間がかかった。。
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
    ll N, Q;
    cin >> N >> Q;
    auto X = LIST(N);
    auto W = LIST(Q);

    vector<ll> A(Q);
    ll mn = 0, mx = 0, cur = 0;
    rep(i, Q) {
        cur += W[i];
        if (cur < mn) {
            A[i] = cur - mn;
            mn = cur;
        } elif (cur > mx) {
            A[i] = cur - mx;
            mx = cur;
        }
    }
    vector<ll> acc(Q);
    Accumulate<ll> accp(Q), accm(Q);
    rep(i, Q) {
        acc[i] = abs(A[i]);
        if (A[i] > 0) {
            accp.set(i, A[i]);
        } elif (A[i] < 0) {
            accm.set(i, -A[i]);
        }

    }
    rep(i, Q-1) {
        acc[i+1] += acc[i];
    }
    accp.build();
    accm.build();

    vector<ll> B(N-1);
    rep(i, N-1) {
        B[i] = X[i+1] - X[i];
    }
    vector<ll> ans(N);
    rep(i, N-1) {
        ll r = bisect_right(acc, B[i]);
        ans[i] += accp.query(0, r);
        ans[i+1] += accm.query(0, r);
        ll rest = B[i] - (r > 0 ? acc[r-1] : 0);
        if (r < Q) {
            if (A[r] > 0) {
                ans[i] += rest;
            } elif (A[r] < 0) {
                ans[i+1] += rest;
            }
        }
    }
    ans[0] += accm.query(0, Q);
    ans[N-1] += accp.query(0, Q);
    print(ans, '\n');
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
