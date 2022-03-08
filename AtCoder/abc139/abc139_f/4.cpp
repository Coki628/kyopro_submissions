/*
・dojo set_e_4_5
・なんとか自力AC。。
・偏角ソート、誤差、工夫して全探索
・これ1年前くらいにもやってやっぱり苦戦してるんだよね、方針分かってんのに。
　今回もやっぱり謎の誤差で苦しんだんだけど、
　制約緩いんだから、左右端全探索を愚直に全部やればよかったんだよね。
　途中で下手に打ち切りとかやらなければ…。
　結局、色々ガチャガチャやってて、不等号を等号にしてみたらマグレでAC。。
　(EPSは外してみても通った。。EPSの意味ない。)
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
#include "template.hpp"

#include "geometry/Point.hpp"
#include "geometry/get_degree.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<Point<ld>> P(N);
    rep(i, N) {
        cin >> P[i].x >> P[i].y;
    }

    vector<pair<ld, ll>> degs;
    rep(i, N) {
        degs.eb(get_degree<ld>({1, 0}, {0, 0}, P[i]), i);
    }
    rep(i, N) {
        degs.eb(degs[i].first+360, i);
    }
    sort(ALL(degs));

    auto dist = [&](Point<ld> p) {
        return p.abs({0, 0});
    };
    ld ans = -INF;
    rep(l, N) {
        ll i = degs[l].second;
        auto cur = P[i];
        chmax(ans, dist(cur));
        rep(r, l+1, min(l+N, N*2)) {
            ll j = degs[r].second;
            auto nxt = cur+P[j];
            if (dist(cur) <= dist(nxt)+EPS) {
                chmax(ans, dist(nxt));
                cur = nxt;
            } else {
                break;
            }
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
