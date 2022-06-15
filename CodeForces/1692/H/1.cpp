/*
・自力ならず。悔しい。。
・最大部分配列問題、連続部分列のDP、復元
・データの持ち替え方まではできてたんだけど、その後嘘貪欲してた…。
・まず、値が連続で出現する位置と個数を、値をキーにして持つ。
　これはランレングスっぽい感じで作る。
　で、目的の値が出現した区間を+、その次に出現する位置までの他の値がある区間を-として、
　これの連続した区間を最大化すればいいんだけど、貪欲っぽくしてうまくいかず。
　復元だるいからかなんとなく無意識に候補から外れてたんだけど、
　これは最大部分配列問題ってやつに帰着できて、DPすると解けるんだよね…。
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
    auto A = LIST(N);

    map<ll, vector<pll>> adj;
    pll cur = {A[0], 0};
    ll cnt = 1;
    rep(i, 1, N) {
        if (A[i] == cur.first) {
            cnt++;
        } else {
            adj[cur.first].eb(cur.second, cnt);
            cur = {A[i], i};
            cnt = 1;
        }
    }
    adj[cur.first].eb(cur.second, cnt);
    ll mx = 0;
    array<ll, 3> ans;
    for (auto& [k, li] : adj) {
        vector<ll> idx = {li[0].first}, A = {li[0].second};
        rep(i, 1, li.size()) {
            auto [l1, cnt1] = li[i-1];
            auto [l2, cnt2] = li[i];
            ll r1 = l1 + cnt1;
            ll r2 = l2 + cnt2;
            idx.eb(r1);
            A.eb(-(l2-r1));
            idx.eb(l2);
            A.eb(cnt2);
        }
        idx.eb(li.back().first+li.back().second);
        assert(A.size()+1 == idx.size());
        ll n = A.size();
        auto dp = list2d(n+1, 3, array<ll, 3>({-INF, -1, -1}));
        dp[0][0] = {0, -1, -1};
        rep(i, n) {
            rep(j, 3) {
                auto [val, l, r] = dp[i][j];
                rep(jj, j, 3) {
                    ll nxval = val, nxl = l, nxr = r;
                    if (jj == 1) {
                        nxval += A[i];
                    }
                    if (j == 0 and jj == 1) {
                        nxl = idx[i];
                    }
                    if (j == 1 and jj == 2) {
                        nxr = idx[i];
                    }
                    if (dp[i+1][jj][0] < nxval) {
                        dp[i+1][jj] = {nxval, nxl, nxr};
                    }
                }
            }
        }
        rep(j, 1, 3) {
            auto [val, l, r] = dp[n][j];
            if (j == 1) r = idx[n];
            if (chmax(mx, val)) {
                ans = {k, l+1, r};
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
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
