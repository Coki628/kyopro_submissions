/*
参考：https://twitter.com/shobonvip/status/1650544137874313217
・自力ならず。。
・PQで貪欲
・最後の詰め切れなかった所は「2種類ある限り2つ同時に処理して、
　残り1種類になったら適当な場所との入れ替えで1つずつ処理する」だった。
　実装としてはしょぼんさんの一言を参考にPQでやった。
・うーん、冷静に対処できればこれは気付けたんじゃないかと思う。
　やっぱり手前解けなくて焦ってると考察力が2段階くらい下がってる気がする…。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

// failed case
// 1
// 8
// cebeecea

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    if (N % 2 == 1) {
        print(-1);
        return;
    }
    auto C = Counter(S);
    for (auto [k, v] : C) {
        if (v > N / 2) {
            print(-1);
            return;
        }
    }

    map<char, ll> C2;
    rep(i, N / 2) {
        ll j = N - i - 1;
        if (S[i] == S[j]) {
            C2[S[i]]++;
        }
    }
    PriorityQueue<ll> que;
    ll ans = 0;
    for (auto [k, v] : C2) {
        que.push(v);
    }
    // 文字種が2つ以上あれば同時に2つ消せる
    while (que.size() >= 2) {
        ll a = que.pop();
        ll b = que.pop();
        a--, b--;
        ans++;
        if (a) que.push(a);
        if (b) que.push(b);
    }
    // 文字種が1つになったら後は1個ずつ
    if (que.size()) {
        ans += que.top();
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
