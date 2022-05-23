/*
参考：https://atcoder.jp/contests/abc249/editorial
・自力ならず。。これむずい。
・更新は逆操作、優先度付きキュー
・最後に更新処理する時点に注目すると、それより手前は一切関係がなくなり、
　それより先で更新処理をスキップするために必要な操作回数が一意になり、
　加算処理をスキップするために使える操作回数も定まるので方針が見えてくる。
　この加算処理に使える回数は、当然減算の大きい所を優先する方がよく、
　これは後ろから順に見て行けば、PQに詰めて前の状態を使いまわしていける。
・なんとか理解はできたけど、これ自分で思いつかないなぁ…。
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

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> T(N), Y(N);
    rep(i, N) {
        cin >> T[i] >> Y[i];
    }

    Accumulate<ll> acc(N);
    rep(i, N) {
        if (T[i] == 2) {
            acc.set(i, Y[i]);
        }
    }
    acc.build();

    // 加算を取り除ける残り回数
    ll rest = K;
    ll sub = 0, ans = -INF;
    priority_queue<ll, vector<ll>> que;
    rep(i, N-1, -1, -1) {
        if (T[i] == 1) {
            chmax(ans, Y[i]+acc.query(i, N)-sub);
            rest--;
            if (rest < 0) {
                print(ans);
                return;
            }
        } elif (T[i] == 2 and Y[i] < 0) {
            que.push(Y[i]);
            sub += Y[i];
        }
        while (que.size() > rest) {
            sub -= que.top(); que.pop();
        }
    }
    chmax(ans, acc.query(0, N)-sub);
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
