/*
・なんとか自力AC…。そもそも今回はここで詰まった時点で幸先良くなかった。
・マージテク
・最初UFで繋いだら合わなくて、そこで結構悩んだ。
　結局UFだと、b->c,a->bの順でやった時のaまでcになっちゃうんだよね。
　今回の題意でそれは適切じゃない。なので普通にvectorで陽に管理して、
　マージテクやりつつシミュした。
・公式解見たけど、26個の変換配列を作って、そっちで変換の過程だけシミュして、
　最後に元の文字列に適用、みたいにしてた。言われると確かに…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    ll M = 26;
    vvl adj(M);
    rep(i, N) {
        adj[S[i] - 'a'].eb(i);
    }

    ll Q;
    cin >> Q;
    rep(_, Q) {
        char c, d;
        cin >> c >> d;
        c -= 'a', d -= 'a';
        if (c == d) continue;
        if (adj[c].size() > adj[d].size()) {
            swap(adj[c], adj[d]);
        }
        for (auto i : adj[c]) {
            adj[d].eb(i);
        }
        adj[c].clear();
    }

    string ans(N, '*');
    rep(c, M) {
        for (auto i : adj[c]) {
            ans[i] = 'a' + c;
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
