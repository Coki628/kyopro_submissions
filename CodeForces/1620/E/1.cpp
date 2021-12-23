/*
・きっちり自力AC！みんな通してたので先にやった。
・マージテク
・値をキーにしてindexのリストを持つ。値が変わる時はマージテクする。
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
    ll Q;
    cin >> Q;
    ll n = 0;
    map<ll, vector<ll>> mp;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            mp[x].eb(n);
            n++;
        } else {
            ll x, y;
            cin >> x >> y;
            if (x == y) continue;
            if (mp[x].size() > mp[y].size()) {
                swap(mp[x], mp[y]);
            }
            for (ll i : mp[x]) {
                mp[y].eb(i);
            }
            mp.erase(x);
        }
    }
    vector<ll> ans(n);
    for (auto& [k, li] : mp) {
        for (ll i : li) {
            ans[i] = k;
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
