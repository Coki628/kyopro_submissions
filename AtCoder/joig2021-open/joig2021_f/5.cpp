/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
　　　https://www2.ioi-jp.org/joig/2020/tasks/2021-joig-t6-review.pdf
・尺取りのキュー実装
・これは長く動かすタイプ。まあでもこれは尺取りじゃないパートがむずい。
　あと尺取りの動き方自体は普通だけど、左右端で別配列を見てるあたりがちょっと独特かも。
・自分なりの解釈で解き直してみた。サブ区間は左右端とも同じ配列で持っておき、
　イベントソートみたいにどっちか分かるようにだけ印つけといてソート。
　で、尺取りするのをメイン区間として、右端と右端が重なったら区間数+1、
　左端と左端が重なったら-1みたいにする。メイン区間より長いやつは予め除外。
　これだと汎用的に「ある区間長K以内に収まるサブ区間の最大個数」みたいのを解けそう。
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
    ll H, W, S;
    cin >> H >> W >> S;
    auto A = listnd(H, W, 0);
    rep(h, H) {
        rep(w, W) {
            cin >> A[h][w];
            A[h][w]--;
        }
    }

    ll M = 256;
    vector<ll> L(M, MOD), R(M, -MOD), U(M, MOD), D(M, -MOD);
    rep(h, H) {
        rep(w, W) {
            chmin(L[A[h][w]], w);
            chmax(R[A[h][w]], w);
            chmin(U[A[h][w]], h);
            chmax(D[A[h][w]], h);
        }
    }

    ll ans = INF;
    rep(uh, H) {
        rep(dh, uh + 1, H + 1) {
            ll wlen = S / (dh - uh);
            vector<pll> vec;
            rep(i, M) {
                if (U[i] >= uh and D[i] < dh and R[i] - L[i] + 1 <= wlen) {
                    vec.eb(L[i], 0);
                    vec.eb(R[i], 1);
                }
            }
            ll m = vec.size();
            sort(ALL(vec));

            deque<ll> que;
            ll res = 0, cnt = 0;
            rep(i, m) {
                auto [val, lr] = vec[i];
                if (lr == 1) {
                    cnt++;
                }
                que.eb(i);
                while (que.size() and vec[que.back()].first - vec[que.front()].first + 1 > wlen) {
                    if (vec[que.front()].second == 0) {
                        cnt--;
                    }
                    que.pop_front();
                }
                chmax(res, cnt);
            }
            chmin(ans, M - res);
        }
    }
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
