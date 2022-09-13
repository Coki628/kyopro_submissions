/*
参考：https://twitter.com/ei1333/status/1568596369610543104
・本番中、ちょっと考えたけどダメだった。
・Aho-Corasick
・小さい文字列がたくさん出てきて、大きい文字列との比較をするので、
　置いてある位置(Ex)的にもアホコラとか使えそうだなー、って思ったのに、
　使った経験値が少なすぎて正しく運用する方法が分からず…。
・使い方が分かると、Sを前から順に見ていって、パターン文字列を1つでも検知した時点で区切るとすればいいので、
　前から貪欲やるだけみたいなかなり軽い実装で済む。
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

#include "string/AhoCorasick.hpp"

void solve() {
    string S;
    cin >> S;
    ll N;
    cin >> N;
    AhoCorasick<26, 'a'> aho;
    rep(i, N) {
        string t;
        cin >> t;
        aho.add(t);
    }
    aho.build();

    ll ans = 0, cur = 0;
    for (auto c : S) {
        auto [cnt, nxt] = aho.move(c, cur);
        // 1つでもマッチしたら、ここで一旦区切る
        if (cnt) {
            ans++;
            cur = 0;
        } else {
            cur = nxt;
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
