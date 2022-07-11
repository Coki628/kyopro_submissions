/*
・JOI埋め
・きっちり自力AC！
・再帰探索、枝刈り、実装
・各Kにおいて、全埋めする3区画はその時点でコストが確定する。
　残り1箇所についてだけ再帰的に見ていくので、各深さで4回、
　まともにやると4^K回の探索で無理だが、N個のマスが1つも含まれない区画は
　自明にコスト0なので、これを即returnすることで枝刈りになる。
　TL3秒だし結構重いのかと思ったけど、0.1秒でACした。
・マスを4区画に分けるパートとか、その時確定する3区画へのJOIの割り当て3!通りから
　最小コストを取るパートとか、色々やることあってまあまあ実装がめんどい。
　特に高速化とか要らないし、愚直に組めばいいんだけどね…。
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
    ll K, N;
    cin >> K >> N;
    vector<tuple<ll, ll, char>> P;
    rep(i, N) {
        ll x, y;
        char c;
        cin >> x >> y >> c;
        x--; y--;
        P.eb(x, y, c);
    }

    auto rec = [&](
        auto&& f, ll k, ll sx, ll sy, ll tx, ll ty,
        const vector<tuple<ll, ll, char>>& P
    ) -> ll {
        if (k == 0 or P.empty()) {
            return 0;
        }
        ll mx = (sx+tx) / 2;
        ll my = (sy+ty) / 2;
        vector<tuple<ll, ll, char>> nxp[4];
        vector<map<char, ll>> C(4);
        for (auto [cx, cy, cc] : P) {
            // 左上
            if (cx < mx and cy < my) {
                nxp[0].eb(cx, cy, cc);
                C[0][cc]++;
            // 右上
            } elif (cx >= mx and cy < my) {
                nxp[1].eb(cx, cy, cc);
                C[1][cc]++;
            // 左下
            } elif (cx < mx and cy >= my) {
                nxp[2].eb(cx, cy, cc);
                C[2][cc]++;
            // 右下
            } elif (cx >= mx and cy >= my) {
                nxp[3].eb(cx, cy, cc);
                C[3][cc]++;
            }
        }
        vector<ll> nxsx = {sx, mx, sx, mx}, nxsy = {sy, sy, my, my};
        vector<ll> nxtx = {mx, tx, mx, tx}, nxty = {my, my, ty, ty};
        ll res = INF;
        rep(i, 4) {
            ll mncost = INF, total = 0;
            vector<map<char, ll>> others;
            rep(j, 4) {
                if (j == i) continue;
                others.eb(C[j]);
                total += nxp[j].size();
            }
            for (auto& perm : permutations(vector<char>{'J', 'O', 'I'})) {
                ll cost = total;
                rep(j, 3) {
                    cost -= others[j][perm[j]];
                }
                chmin(mncost, cost);
            }
            chmin(res, f(f, k-1, nxsx[i], nxsy[i], nxtx[i], nxty[i], nxp[i]) + mncost);
        }
        return res;
    };
    ll res = rec(rec, K, 0, 0, pow(2, K), pow(2, K), P);
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
