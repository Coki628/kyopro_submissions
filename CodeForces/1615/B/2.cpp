/*
・なんとか自力AC！
・クエリ先読み、BIT、ビット毎に見る
・右端毎に見る。その時の左端からの個数はBITで数えられる。
　区間を1進める毎に各ビットに紐づく18本のBITを更新。
・これでも最初MLEした。さすがにこどふぉは256MBなので油断できない。
　全部intにして無事AC0.73秒。メモリは203MBだった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    int Q;
    cin >> Q;
    int N = 10e5*2;

    vector<vector<pii>> adj(N+1);
    rep(i, Q) {
        int l, r;
        cin >> l >> r;
        r++;
        adj[r].eb(l, i);
    }

    int M = 18;
    vector<BIT<int>> bit(M, {N+1});
    vector<int> ans(Q);
    rep(r, 1, N+1) {
        for (auto [l, i] : adj[r]) {
            int mx = 0;
            rep(k, M) {
                chmax(mx, bit[k].query(l, r));
            }
            ans[i] = r-l-mx;
        }
        rep(k, M) {
            if (r>>k & 1) {
                bit[k].add(r, 1);
            }
        }
    }
    for (int a : ans) print(a);
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
