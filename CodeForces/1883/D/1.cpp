/*
・なんとか自力AC！
・区間の集合があって、intersectしない区間ペアがあるかどうかを見る問題。
　する方ならともかく、しない方ってそんな簡単に分かるか？って
　しばらく考えたけど浮かばずスキップ。後半解いて戻ってきた。
　再度考えると、r>lな場所が1つでもあれば確実じゃないかと思った。
　必要だとは思ったけど十分かは分からず、でもDiv.3のDくらいなら
　きっとこのくらいで解けるやつだろうという読みの元に投げると、無事AC。
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

void solve() {
    ll Q;
    cin >> Q;
    Multiset<ll> sel, ser;
    rep(i, Q) {
        char op;
        ll l, r;
        cin >> op >> l >> r;
        if (op == '+') {
            sel.insert(l);
            ser.insert(r);
        } else {
            sel.erase(l);
            ser.erase(r);
        }
        if (ser.size() and ser.front() < sel.back()) {
            YES();
        } else {
            NO();
        }
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
