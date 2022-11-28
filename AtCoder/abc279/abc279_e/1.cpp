/*
参考：https://twitter.com/nickname959198/status/1596509704338874370
・自力ならず、、かな。上記ツイートでなんとなく本質っぽいのを見てしまった。
・前後から累積和みたく結果を取れれば、間ひとつ抜いたらどうなるかのiを全探索できる。
　がしかし普通にやろうとすると、前からの結果は1から始まるやつだけ取れればいいので、
　これはO(M)でできるけど、後ろからは最終的にどこに1が来るかは分からないので、
　全箇所から始まるものを全て確認しようとするとO(M^2)になってしまう。
　だけどこれの各回での操作は2点スワップだけなので、
　後ろから全体の状態を保持しながら(in placeに)シミュしていけば、O(M)でできる。
・ヒントありで落ち着いて考えたら整理できたけど、
　本番中にFに行かずにこれに張り付いたとして、ノーヒントで時間内に解けたかは分からない。
　なんか前後から前計算が思いついても、後ろがO(M^2)になるじゃんって棄却してそう…。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(M);
    cin >> A;
    A--;

    vector<ll> prep(M);
    ll cur = 0;
    rep(i, M-1) {
        if (cur == A[i]) {
            cur++;
        } elif (cur == A[i] + 1) {
            cur--;
        }
        prep[i + 1] = cur;
    }
    vector<ll> pos(N), ans(M);
    iota(ALL(pos), 0);
    rep(i, M-1, -1, -1) {
        ans[i] = pos[prep[i]];
        swap(pos[A[i]], pos[A[i] + 1]);
    }
    ans++;
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
