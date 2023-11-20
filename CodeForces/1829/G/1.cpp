/*
・なんとか自力AC！本日のボトルネック。。
・構築、逆操作、グリッドDPの数え上げ、ダブルカウントを引く
・まず題意に合うピラミッドを、グリッドに当てはめて構築する。
　で、崩すスコア計算みたいのをBFSで毎回やってTLE。。
　その後結構悩んだ。結果、グリッドDPすると逆操作みたいにできると分かる。
　これで全位置について前計算しておける。
　ただし、グリッドDPの数え上げでダブルカウントが発生するので注意。
　遷移が斜めなのもあって、差し引く位置も普通と少し違ってくる。
・ちなみに、O(2023^2)で0.5秒かかるの重いなぁと思って、
　後からvectorを生配列に変えて投げてみたんだけど、速くならなかった。。
・公式解説見た。45度回して普通の2次元累積和にしてた。かしこっ。
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

const ll H = 2023, W = 2023;
ll grid[H][W] = {};
ll dp[H][W] = {};
map<ll, pii> mp;
void prep() {
    ll wlen = 1, num = 1;
    rep(h, H) {
        rep(w, wlen) {
            grid[h][w] = num * num;
            mp[num * num] = {h, w};
            num++;
        }
        wlen++;
    }

    rep(h, H) {
        rep(w, W) {
            dp[h][w] = grid[h][w];
            if (h > 0) {
                dp[h][w] += dp[h - 1][w];
            }
            if (h > 0 and w > 0) {
                dp[h][w] += dp[h - 1][w - 1];
            }
            if (h > 1 and w > 0) {
                // ダブルカウントを引く
                dp[h][w] -= dp[h - 2][w - 1];
            }
        }
    }
}

void solve() {
    ll N;
    cin >> N;
    assert(mp.count(N * N));
    auto [sh, sw] = mp[N * N];

    print(dp[sh][sw]);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
