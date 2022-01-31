/*
・まじのブザービートAC！！
・区間GCD、二分探索
・ダメな場所が発生しそうになったらそこを適当な素数を置き換えると考える。
　1つ要素が増える度に左にGCD=区間長ができないかセグ木とかにGCD乗せて
　チェックしにいくとして、ずっと約数列挙してそれを候補に見に行ってた。
　これだと、A[i]が10億まであるから、20万のN回すのがきつい。GCDのlogも乗るし。
　で、色々悩んだ後、GCDは下がってくし区間長は上がっていくんだから、
　両方単調性があるのでにぶたんできるんじゃん？となった。
　めちゃ時間なかったんだけど、これが01:59:59で提出間に合ってAC。
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

#include "segment/SparseTable.hpp"

void solve() {
    int N;
    cin >> N;
    auto A = LIST(N);

    auto st = get_sparse_table(A, [](ll a, ll b) { return gcd(a, b); }, 0LL);
    ll j = -1, need = 0;
    vector<ll> ans;
    rep(i, N) {
        ll r = i+1;
        ll l = bisearch_min(j, r-1, [&](ll m) {
            return st.query(m, r) >= r-m;
        });
        if (st.query(l, r) == r-l) {
            j = i;
            need++;
        }
        ans.eb(need);
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
