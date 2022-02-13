/*
参考：https://twitter.com/butsurizuki/status/1492547397867937794
・自力ならず。。自力は、ペアのソートの優先順位とか考えてたけど、
　実際は持ち方変えれば全探索できるやつだった。
　この種類数√Nのテーマは何回も見てるのに、気付けなかったの悔しい。
・種類数は最大でも√N、みたいなやつ。そっちをキーで持てばペア全探索できる。
　各種類ごとで最大の方からだけ見る。
・これは雑にmapとsetで持って、√だけじゃなくlogも乗ってTLE。。
・存在チェックのsetをvectorのsortとlower_boundにして、
　mapがキーの隣接リストは座圧してvectorの隣接リストにした。これでAC0.56秒。
・なんかシステス後にケース追加されてるっぽくて、システス時点までのケースなら
　最初のゆるく作った方でも通ったっぽい。
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

    vector<pll> banned;
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        banned.pb({a, b});
        banned.pb({b, a});
    }
    sort(ALL(banned));
    banned.eb(INF, INF);

    auto C = Counter(A);
    vector<ll> tmp;
    for (auto [k, v] : C) {
        tmp.eb(v);
    }
    Compress<ll> cp(tmp);
    ll L = cp.size();
    vvl adj(L);
    for (auto& [k, v] : C) {
        v = cp[v];
        adj[v].eb(k);
    }
    rep(i, L) {
        sort(adj[i].rbegin(), adj[i].rend());
    }

    ll ans = 0;
    rep(v1, L) {
        for (auto k1 : adj[v1]) {
            rep(v2, v1+1) {
                for (auto k2 : adj[v2]) {
                    if (k1 == k2) continue;
                    if ((*lower_bound(ALL(banned), mkp(k1, k2))) != mkp(k1, k2)) {
                        chmax(ans, (k1+k2)*(cp.unzip(v1)+cp.unzip(v2)));
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
