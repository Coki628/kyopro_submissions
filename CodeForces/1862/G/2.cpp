/*
・終了後なんとか自力AC。けど1時間近くかかってて全然ダメだー。
・差分列をmultisetで動的に管理
・考察としては、クエリの答えは「数列の最大値+差分列の最大値」
　になりそうだと分かる。で、これを管理するためにmultiset2本をガチャガチャする。
　最終的に通せたものの、方針決めてから時間かかりすぎなので、
　手早く実装できる方法を検討しよう。このmultiset2本で差分管理するやつ、
　今までにも何回も時間かかってる感じがするので。
・とりあえず番兵を入れてみた。最近indexずれるの嫌であんまり番兵使わないんだけど、
　今回は別にindex関係ないし、積極的に使ってもまあいい気はする。
　先頭末尾の場合分けは要らなくなる。最大値の取得位置がちょっと変わるから気をつける。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    multiset<ll> se1(ALL(A)), se2;
    se1.insert(-INF);
    se1.insert(INF);
    auto itr = se1.begin();
    while (itr != --se1.end()) {
        se2.insert(*next(itr) - *itr);
        itr++;
    }
    ll Q;
    cin >> Q;
    vector<ll> ans(Q);
    rep(i, Q) {
        ll j, x;
        cin >> j >> x;
        j--;

        auto itr = se1.find(A[j]);
        se2.erase(se2.find(*itr - *prev(itr)));
        se2.erase(se2.find(*next(itr) - *itr));
        se2.insert(*next(itr) - *prev(itr));
        se1.erase(itr);
        itr = se1.insert(x);
        se2.erase(se2.find(*next(itr) - *prev(itr)));
        se2.insert(*itr - *prev(itr));
        se2.insert(*next(itr) - *itr);
        A[j] = x;
        ans[i] = *prev(se1.end(), 2) + (N >= 2 ? *prev(se2.end(), 3) : 0);
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
