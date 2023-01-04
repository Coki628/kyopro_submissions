/*
・きっちり自力AC！
・区間chmin、セグ木にぶたん
・前から、今の位置を切る必要があるならできるだけ右端を長く伸ばす、
　みたいなシミュをにぶたんとかしながら進めたら通った。
　chminのシミュにBeats持ち出したけど、1点取得だから多分普通の遅延セグでも大丈夫。
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

#include "datastructure/SegmentTreeBeats.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    cin >> A >> B;
    ll M;
    cin >> M;
    vector<ll> X(M);
    cin >> X;

    rep(i, N) {
        if (A[i] < B[i]) {
            NO();
            return;
        }
    }

    auto C = Counter(X);
    SegmentTreeBeats sega(A);
    auto segb = get_segment_tree(
        B, [](ll a, ll b) { return max(a, b); }, -INF);
    rep(i, N) {
        assert(sega[i] >= B[i]);
        if (sega[i] > B[i]) {
            if (not C.count(B[i]) or C[B[i]] == 0) {
                NO();
                return;
            }
            C[B[i]]--;
            ll j = segb.find_first(i, [&](ll x) { return x > B[i]; });
            if (j == -1) j = N;
            sega.chmin(i, j, B[i]);
        }
    }
    rep(i, N) {
        assert(sega[i] == B[i]);
    }
    YES();
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
