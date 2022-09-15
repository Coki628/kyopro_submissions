/*
・upsolved。本番時は見えなかったし、ノーヒントでは多分解けてない。
・ベルマンフォード
・なんとなく問題開いてしばらく考えて方針が見えたのは、
　最近ベルマンフォードが出たっていう予備情報があったからで、実力とは言えない。
　とはいえ、この問題だってことは分からない状態から見えたので、まあ良しとする。
・1文字増やした時に増えるコスト(利得)を考えると、Tに含まれる文字列長が3以下なので、
　今回使う文字と合わせて、直近2文字を状態として持てばいけそう。
　いくらでもスコアが伸ばせるというのは、そういう閉路が存在するかどうかなので、
　正負逆で考えると、(負コストを含む)コスト最小化と負閉路検出が必要。
　この要件はまさにベルマンフォードが適任だけど、その計算量O(VE)を確認すると、
　さっきの直近2文字の状態は頂点数で言うと27^2(空文字を表したいので26+1)=729となり、
　辺数は頂点数*遷移先の数26=18954で、729*18954=1400万くらいなので間に合いそう。
　古のpythonライブラリからベルマンフォードを取ってきて、
　適切に構築したグラフをここに流し込むと、無事AC。
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

#include "graph/bellman_ford.hpp"

void solve() {
    ll N;
    cin >> N;
    map<string, ll> mp;
    rep(i, N) {
        string t;
        ll p;
        cin >> t >> p;
        mp[t] = -p;
    }

    ll L = 27;
    ll LL = L*L;
    auto stoi = [&](string s) -> ll {
        assert(s.size() == 2);
        ll c2 = s[1]-'a';
        ll c1 = s[0]-'a';
        return c1*L + c2;
    };
    auto itos = [&](ll i) -> string {
        auto [c1, c2] = divmod(i, L);
        return {(char)('a'+c1), (char)('a'+c2)};
    };
    vector<array<ll, 3>> edges;
    rep(u, LL) {
        string s = itos(u);
        rep(c3, L-1) {
            string t = s + (char)('a'+c3);
            ll v = stoi(t.substr(1));
            ll cost = 0;
            rep(i, t.size()) {
                auto sb = t.substr(i);
                if (mp.count(sb)) {
                    cost += mp[sb];
                }
            }
            edges.pb({u, v, cost});
        }
    }

    auto res = bellman_ford(LL, edges, LL-1);
    ll ans = -min(subarray(res, 0, LL-1));
    if (ans == INF) {
        print("Infinity");
    } else {
        print(ans);
    }
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
