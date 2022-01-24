/*
参考：https://qiita.com/Sooh31/items/97e2d9724fe47ed238b3
・自力ならず。これは知識不足でしゃあない。。
・XOR基底
・聞いたことあるけどちゃんと履修してなかったやつね。ツケが回ってきた。
・線形代数入門でもちょっとやったけど、基底は任意の値を作るために必要になる、
　必要最低限の要素たち、みたいな感じのもの。
　XORについては、ある数列からこれを簡易的に抽出する方法が確立されてる。
・今回の問題で言えば、なるべく低コストで全要素を作りたいので、
　コストの小さい方から、基底になれるかどうかを順番に試していって、
　基底として必要になった要素の分だけコストを足したものが答えになる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

template<typename T>
vector<T> get_xor_basis(const vector<T> &A) {
    vector<T> basis;
    for (auto a : A) {
        for (auto b : basis) {
            chmin(a, a^b);
        }
        if (a > 0) basis.eb(a);
    }
    return basis;
}

void solve() {
    ll N;
    cin >> N;
    ll L = 1LL<<N;
    auto A = LIST(L-1);
    A.insert(A.begin(), 0);

    vector<pll> AB;
    rep(i, 1, L) {
        AB.eb(A[i], i);
    }
    sort(ALL(AB));
    ll ans = 0;
    vector<ll> basis;
    for (auto [a, b] : AB) {
        for (auto ba : basis) {
            chmin(b, b^ba);
        }
        if (b > 0) {
            // 基底として必要になった分のコストを足す
            ans += a;
            basis.eb(b);
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
