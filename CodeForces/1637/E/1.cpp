/*
参考：https://twitter.com/butsurizuki/status/1492547397867937794
・自力ならず。。自力は、ペアのソートの優先順位とか考えてたけど、
　実際は持ち方変えれば全探索できるやつだった。
　この種類数√Nのテーマは何回も見てるのに、気付けなかったの悔しい。
・種類数は最大でも√N、みたいなやつ。そっちをキーで持てばペア全探索できる。
　各種類ごとで最大の方からだけ見る。
・これは雑にmapとsetで持って、√だけじゃなくlogも乗ってTLE。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
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
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);

    set<pll> banned;
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        banned.insert({a, b});
        banned.insert({b, a});
    }

    auto C = Counter(A);
    map<ll, vector<ll>> adj;
    for (auto [k, v] : C) {
        adj[v].eb(k);
    }
    for (auto& [_, li] : adj) {
        sort(li.rbegin(), li.rend());
    }

    ll ans = 0;
    for (auto& [v1, li1] : adj) {
        for (auto k1 : li1) {
            for (auto& [v2, li2] : adj) {
                for (auto k2 : li2) {
                    if (k1 == k2) continue;
                    if (not banned.count({k1, k2})) {
                        chmax(ans, (k1+k2)*(v1+v2));
                        break;
                    }
                }
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
