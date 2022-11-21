/*
・きっちり自力AC！
・辞書順最小の貪欲、セグ木にぶたん
・Bに含まれないN/2個をAとして、BとAでペアを見つけるマッチングのイメージ。
　大きいやつは組める候補が少ないので、大きい方から決める。
　Aを大きい方から見て、辞書順最小を目指す以上、大きいやつは後ろにやりたいので
　「自身より大きくて一番後ろにある」やつと組ませる。
　これはセグ木にぶたんして、使用済みを-INFに更新みたいにすると見つかる。
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
    ll N;
    cin >> N;
    vector<ll> B(N/2);
    cin >> B;

    vector<ll> used(N+1);
    rep(i, N/2) {
        if (used[B[i]]) {
            print(-1);
            return;
        }
        used[B[i]] = 1;
    }
    vector<ll> A;
    rep(a, 1, N+1) {
        if (not used[a]) {
            A.eb(a);
        }
    }
    vector<ll> A2(N/2);
    auto seg = get_segment_tree(B, [](ll a, ll b) { return max(a, b); }, -INF);
    rep(i, N/2-1, -1, -1) {
        ll j = seg.find_last(N, [&](ll x) { return x > A[i]; });
        if (j == -1) {
            print(-1);
            return;
        }
        A2[j] = A[i];
        seg.update(j, -INF);
    }
    vector<ll> ans;
    rep(i, N/2) {
        if (B[i] < A2[i]) {
            ans.eb(B[i]);
            ans.eb(A2[i]);
        } elif (B[i] > A2[i]) {
            ans.eb(A2[i]);
            ans.eb(B[i]);
        } else {
            assert(0);
        }
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
