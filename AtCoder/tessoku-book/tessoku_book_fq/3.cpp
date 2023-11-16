/*
・なんとか自力AC！
・貪欲を詰める。ランダムケース作って、穴となってるケースを全部埋める。
　基本方針は「届く範囲の最小コスト位置」に飛ぶ、だったんだけど、
　色々詰めていくと、自身より小さいコストに届くなら、
　とりあえずそこまで行ってその先のことはそこから考えても損はない、
　っていうのが分かって、「今位置よりコストが小さい中で一番近く」
　を優先させるようにしたら通った。
　実装はにぶたんで届く範囲探したり、
　セグ木で最小コスト位置とか探せるようにしたり、とかそんな感じ。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

// failed cases
// 14 15 7
// 5 5
// 5 20
// 5 15
// 5 19
// 6 5
// 8 6
// 8 8
// 9 15
// 11 11
// 11 17
// 13 20
// 13 11
// 13 15
// 14 15

// 3 8 4
// 1 8
// 5 20
// 6 10

// 5 9 9
// 1 6
// 1 15
// 4 9
// 6 12
// 7 18

// 8 7 6
// 1 19
// 2 13
// 3 5
// 4 10
// 4 14
// 4 18
// 5 1
// 5 2

// 18 14 6
// 1 14
// 2 11
// 2 13
// 3 8
// 3 7
// 4 19
// 4 13
// 4 11
// 4 5
// 5 19
// 6 13
// 8 14
// 8 4
// 9 6
// 10 19
// 10 2
// 11 3
// 13 9

void solve() {
    ll N, L, K;
    cin >> N >> L >> K;
    vector<ll> A(N), C(N);
    rep(i, N) {
        cin >> A[i] >> C[i];
    }
    A.insert(A.begin(), 0);
    C.insert(C.begin(), 0);
    A.eb(L);
    // 終点は給油目的で優先的に目指さないようにINFにしておく
    C.eb(INF);
    N++;

    auto seg = get_segment_tree(C, [](ll a, ll b) { return min(a, b); }, INF);
    ll i = 0, k = K;
    ll ans = 0;
    while (i < N) {
        ll l = i + 1;
        ll r = bisect_right(A, A[i] + K, l);
        if (r == l) {
            print(-1);
            return;
        }
        ll mn = seg.query(l, r);
        // 届く範囲で一番コストが小さい
        ll mni = seg.find_first(l, [&](ll x) { return x <= mn; });
        // 今位置よりコストが小さい中で一番近く
        ll smi = seg.find_first(l, [&](ll x) { return x < C[i]; });
        assert(mni < r and mni != -1);
        auto [fill, dist, nxi] = [&]() -> array<ll, 3> {
            // 今位置よりコストが小さいのがあったか
            if (smi >= r or smi == -1) {
                // ないなら
                if (r <= N) {
                    // 終点に届かないなら満タンにして、届く範囲で最小コストの位置へ
                    return {K - k, abs(A[i] - A[mni]), mni};
                } else {
                    // 終点に届くなら行く
                    return {max(abs(A[i] - A[N]) - k, 0LL), abs(A[i] - A[N]), N};
                }
            } else {
                // あったらそこまでの最低限
                return {max(abs(A[i] - A[smi]) - k, 0LL), abs(A[i] - A[smi]), smi};
            }
        }();
        assert(fill >= 0);
        assert(fill <= K);
        ll cost = fill * C[i];
        k += fill;
        assert(k <= K);
        k -= dist;
        assert(k >= 0);
        ans += cost;
        i = nxi;
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
