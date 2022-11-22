/*
・きっちり自力AC！
・木、グラフ、XOR
・頂点a,bそれぞれから前から木DPみたいにxorの値を求めて、
　同じ値になる所があれば(その間をワープすれば0にできるので)YES。
　a側の探索では頂点b以降に進まないこと。
　b側の探索ではbの分の値0は除く(bへの直接ワープは認められないので)
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
    ll N, a, b;
    cin >> N >> a >> b;
    a--; b--;
    vvpil nodes(N);
    rep(i, N-1) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
    }

    vector<ll> dpa(N);
    auto dfs1 = [&](auto&& f, ll u, ll prv) -> void {
        for (auto [v, c] : nodes[u]) {
            if (v == prv or v == b) continue;
            dpa[v] = dpa[u] ^ c;
            f(f, v, u);
        }
    };
    dfs1(dfs1, a, -1);

    vector<ll> dpb(N);
    auto dfs2 = [&](auto&& f, ll u, ll prv) -> void {
        for (auto [v, c] : nodes[u]) {
            if (v == prv) continue;
            dpb[v] = dpb[u] ^ c;
            f(f, v, u);
        }
    };
    dfs2(dfs2, b, -1);
    dpb.erase(dpb.begin()+b);

    set<ll> froma(ALL(dpa)), fromb(ALL(dpb));
    for (auto a : froma) {
        if (fromb.count(a)) {
            YES();
            return;
        }
    }
    NO();
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
