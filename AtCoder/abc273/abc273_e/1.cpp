/*
・永続配列、クエリ先読み、座圧
　本番中に初めて使った。永続配列の長さは固定っぽかったので、その時点のサイズとペアで管理。
　使うページだけクエリ先読みで座圧とかは適宜下処理しておく。
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

#include "common/PersistentArray.hpp"

void solve() {
    ll Q;
    cin >> Q;
    vector<pair<string, ll>> qs;
    Compress<ll> cp;
    rep(i, Q) {
        string s;
        ll x = -1;
        cin >> s;
        if (s != "DELETE") {
            cin >> x;
        }
        qs.eb(s, x);
        if (s == "SAVE" or s == "LOAD") {
            cp.add(x);
        }
    }
    cp.build();
    ll M = cp.size();
    vector<pair<PersistentArray<ll, 3>::Node*, ll>> notebook(M);
    PersistentArray<ll, 3> data;
    data.build(vector<ll>(Q, -1));
    ll sz = 0;
    vector<ll> ans(Q, -1);
    rep(i, Q) {
        auto [s, x] = qs[i];
        if (s == "ADD") {
            data.update(sz, x);
            sz++;
        } elif (s == "DELETE") {
            if (sz) {
                data.update(sz, -1);
                sz--;
            }
        } elif (s == "SAVE") {
            notebook[cp[x]] = {data.root, sz};
        } else {
            tie(data.root, sz) = notebook[cp[x]];
        }
        if (sz > 0) {
            ans[i] = data.get(sz-1);
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
