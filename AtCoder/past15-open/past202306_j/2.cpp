/*
・自力ならず。。
・優先度付きキューで貪欲
・比較的近い方針までは行っていたが、詰め切れなかった。
　手裏剣をどう使うかの優先度決めが重要になる。
　これには「その1回を使うことで自分が食らうダメージをどのくらい減らせるか」
　を利得の大きさとして考えていく。
　基本的には相手と打ち合うのが1ターン減るので利得はA[i]なんだけど、
　鳥の最初の1回(ただし体力2以上)だけは、
　体力を1減らす上にこっちの先制攻撃になるので、この利得の重さが2倍になる。
　この点を考慮して適切に順序決めすればいいんだけど、
　自分がやろうとした「手裏剣最初の1回だけ別で考える」の方針だと、
　鳥の一発目より優先すべき地上のやつがいた時に、
　鳥の方に手裏剣を1回使ってしまうため、最適になってなかった。
　あと、体力が1しかない地上の敵にも手裏剣1回投げてた。
　(先制攻撃1回で倒せるので、使う必要がない。)
　結局、上記前者の問題を解決するために、ソート2回じゃなくて、
　プリキューの実装に書き直した。
　鳥が来た場合は1回だけ手裏剣投げて、
　利得が変わった状態で再度キューに詰める、とした。
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
    ll N, M;
    cin >> N >> M;
    vector<array<ll, 3>> vec;
    rep(i, N) {
        ll a, b, x;
        cin >> a >> b >> x;
        vec.pb({a, b, x});
    }

    PriorityQueue<pll> que;
    rep(i, N) {
        auto [a, b, x] = vec[i];
        if (x == 1 and b >= 2) {
            que.push({a * 2, i});
        } else {
            que.push({a, i});
        }
    }
    ll ans = 0, cur = M;
    while (que.size()) {
        auto [_, i] = que.pop();
        auto &[a, b, x] = vec[i];
        // 手裏剣もうないなら殴り合うだけ
        if (cur == 0) {
            if (x == 0) {
                b--;
            }
            ans += a * b;
        } else {
            // ある場合で相手が鳥なら、1回だけ使う
            if (x == 1) {
                cur--;
                x = 0;
                b--;
                if (b > 0) {
                    // 優先度が変わった状態で再度キューに詰める
                    que.push({a, i});
                }
            } else {
                // 地上ならこれ以降優先度は変わらないので、使えるだけ使う
                b--;
                ll use = min(b, cur);
                cur -= use;
                b -= use;
                ans += a * b;
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
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
