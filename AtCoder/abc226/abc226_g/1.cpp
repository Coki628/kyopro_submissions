/*
参考：https://www.youtube.com/watch?v=SZGIhJaZxK8
・ABC残埋め
・当然自力ならず。こういう貪欲は苦手よね…。
・ビンパッキング問題
・一般にNP困難だそうだけど、N=5のこの問題は貪欲に解ける。
・3,4,5の荷物は1対1で持たせるしかないので比較的選択肢は限られていて、
　1は隙間に詰めれるだけ詰めるみたいにできるので、2の荷物の扱いがキーになる。
　結局、この2の荷物をいかに効率よく持てるようにするかが大事で、
　そのために3の荷物を詰める時、優先順位を3→5→4の順にする。
　(5を優先することで、2が優先して残るため)
　逆に言えば、ここ以外は割とお気持ち貪欲な感じにすればいい。
　大きい荷物は大きい人にしか持たせられないので、基本的に大きい方から順に埋めてく。
・実装は、荷物を詰める関数を切ったのはいいんだけど、
　何か2ついっぺんに詰める処理とか余計に難しく考えてしまった。
　後からすぬけさんの実装見てたら、さすがに簡潔でへえぇとなった。
　全然場合分けとか要らなくて、どうせ1個ずつ持たせても、
　残りが少ない方に回るだけなので、小さい方をやる時には普通に使える。
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

const ll N = 5;

// 荷物A[i]を人B[j]に持てるだけ持たせる
void pack(vector<ll> &A, vector<ll> &B, ll i, ll j) {
    assert(i <= j);
    assert(i >= 2);
    ll rest = j - i;
    if (i == 2 and j >= 4) {
        rest -= 2;
        auto [d, m] = divmod(A[i], 2LL);
        ll use = min(d, B[j]);
        A[i] -= use * 2;
        B[j] -= use;
        if (rest) B[rest] += use;
        if (m and B[j]) {
            A[i]--;
            B[j]--;
            B[j-2]++;
        }
    } else {
        ll use = min(A[i], B[j]);
        A[i] -= use;
        B[j] -= use;
        if (rest) B[rest] += use;
    }
}

void solve() {
    auto A = LIST(N);
    auto B = LIST(N);
    A.insert(A.begin(), 0);
    B.insert(B.begin(), 0);

    pack(A, B, 5, 5);
    pack(A, B, 4, 4);
    pack(A, B, 4, 5);
    pack(A, B, 3, 3);
    pack(A, B, 3, 5);
    pack(A, B, 3, 4);
    rep(i, N, 1, -1) {
        pack(A, B, 2, i);
    }
    rep(i, 2, N+1) {
        if (A[i] > 0) {
            No();
            return;
        }
    }

    ll smb = 0;
    rep(i, 1, N+1) {
        smb += B[i] * i;
    }
    if (smb >= A[1]) {
        Yes();
    } else {
        No();
    }
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
