/*
・自力AC！これね、添字バグり散らかすやつ。
・クエリ系、差分列
・まず問題文の説明上グラフの話とかになっているが、これは諸々整理すると、
　0の塊と1の塊のグループで見て、ある区間上に、グループの境界が
　・1つもなければいずれにしろ前に進むしかできない
　・1つだけなら、始点が右のグループなら最後まで進んで戻る、左のグループだと無理
　・2つ以上あればうまく方向転換できるので(多分)どうにでもできる
　の3パターンを考えればよく、必要なのは区間内の境界の数を数えることと、
　グループが1つ以下だった時に、その始点からで区間を網羅できるかどうかの判定の2点になる。
・まず境界の数を数えるには、予め差分列にしておいて、区間更新を2点更新とすれば、
　これはBITとかで処理できる。(添字ゲーはつらいけど)
・判定の方は、境界0の時はシンプルに始点が区間の左端かどうかでよく、
　境界1の時は、始点が右グループでかつその先頭かどうかでいい。
　どちらもBITでチェックできる。
・差分列の場合、前後に番兵入れてN+1要素とした方が、2点更新で場合分けが要らなくなるので楽だと思った。
　これはそっちを試してみた版。もちろん問題なくACする。
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
#include "template.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    BIT<ll> bit(N+1);
    rep(i, 1, N) {
        if (S[i] != S[i-1]) {
            bit.add(i, 1);
        }
    }
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll l, r;
            cin >> l >> r;
            l--;
            bit.update(l, 1-bit[l]);
            bit.update(r, 1-bit[r]);
        } else {
            ll l, r, x;
            cin >> l >> r >> x;
            ll cnt = bit.query(l, r);
            if (cnt == 0) {
                if (x == l) {
                    YES();
                } else {
                    NO();
                }
            } elif (cnt == 1) {
                ll y = bit.bisearch_fore(l, r-1, 1);
                assert(y != -1);
                if (x == y+1) {
                    YES();
                } else {
                    NO();
                }
            } else {
                YES();
            }
        }
        // bit.print(N-1);
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
