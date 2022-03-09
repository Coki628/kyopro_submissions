/*
・なんとか終了後自力AC。間に合わず。。
・差分をmultisetで管理
・どの1個を移動させるか全探索。変化する差分をmultisetで管理しながら、
　一番広い場所に差し込むのを試していく感じ。
　なんだけど、末尾要素の後ろが扱いが違うので、ここの場合分けが結構面倒だった。。
　(ソース内コメントも参照)
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
    ll N, D;
    cin >> N >> D;
    auto A = LIST(N);

    multiset<ll> diff;
    A.insert(A.begin(), 0);
    A.eb(D+1);
    rep(i, N+1) {
        diff.insert(A[i+1]-A[i]-1);
    }
    // 末尾要素の後ろ
    ll end = D-A[N];
    ll ans = 0;
    rep(i, 1, N+1) {
        diff.erase(diff.find(A[i]-A[i-1]-1));
        diff.erase(diff.find(A[i+1]-A[i]-1));
        if (i == N) {
            end = D-A[N-1];
        }
        diff.insert(A[i+1]-A[i-1]-1);
        // 1個抜いた状態で一番狭い場所(末尾要素の後ろ以外)
        ll mn1 = *diff.begin() == end ? *++diff.begin() : *diff.begin();
        // 末尾要素の後ろか今一番広い場所のどちらかにこの1個を詰めるとする
        ll mn2 = max(end-1, ceil(*diff.rbegin(), 2LL)-1);
        chmax(ans, min(mn1, mn2));
        diff.erase(diff.find(A[i+1]-A[i-1]-1));
        diff.insert(A[i]-A[i-1]-1);
        diff.insert(A[i+1]-A[i]-1);
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
