/*
・ライブラリ整備：オフラインダイコネ
・CFで類題(cf1681F)を解いたので、こっちもダイコネでやってみる。
・ほぼ同じ感じで、注目している色cに係る辺だけ外す。ただし今回は頂点属性なので、
　辺属性のUFと対応させるためにちょっと場合分けとかは要る。
　辺の両端を見て、色cではない頂点ならそちら側の連結成分は色cを含まない状態になっているので、
　成分数から全ペアの通り数を加える。頂点1つだけの分は辺からは判定できないので別処理。
・Nが20万(クエリは40万相当)で、AC1.07秒。
　クエリへの回答にsetを使っているのを高速なものに変えても速度が変わらなかった。
　結局、回答クエリは20万回しかなく、ここは(多分)セグ木やUFのlogと重ならない並列な関係なので、
　setのlogが乗っても乗らなくてもあまり影響がないんだと思われる。
　逆に言えば、クエリの回答にlogが乗るような処理が入っても全然問題ないってことだね。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "graph/OfflineDynamicConnectivity.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<vector<pii>> adj(N);
    auto C = LIST(N);
    rep(i, N) C[i]--;
    auto C2 = Counter(C, N);
    OfflineDynamicConnectivity odc(N, N*2+1);
    ll t = 0;
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        adj[C[u]].eb(u, v);
        adj[C[v]].eb(u, v);
        odc.insert(t, u, v);
    }
    t++;

    vector<int> ttoc(N*2+1, -1);
    rep(c, N) {
        for (auto [u, v] : adj[c]) {
            odc.erase(t, u, v);
        }
        t++;
        ttoc[t++] = c;
        for (auto [u, v] : adj[c]) {
            odc.insert(t, u, v);
        }
    }

    vector<ll> ans(N, N*(N-1)/2);
    odc.run([&](int t) {
        if (ttoc[t] != -1) {
            int c = ttoc[t];
            if (adj[c].empty()) {
                ans[c] = C2[c];
                return;
            }
            ans[c] += C2[c];
            set<int> used;
            for (auto [u, v] : adj[c]) {
                if (C[u] != c) {
                    int ru = odc.uf.find(u);
                    if (not used.count(ru)) {
                        ll sz = odc.uf.size(ru);
                        ans[c] -= sz * (sz-1) / 2;
                        used.insert(ru);
                    }
                }
                if (C[v] != c) {
                    int rv = odc.uf.find(v);
                    if (not used.count(rv)) {
                        ll sz = odc.uf.size(rv);
                        ans[c] -= sz * (sz-1) / 2;
                        used.insert(rv);
                    }
                }
            }
        }
    });
    print(ans, '\n');
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
