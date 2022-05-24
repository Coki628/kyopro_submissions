/*
・なんとか自力AC…。
・構築
・A,Bの優先順位でソートしてBもソート済になってなかったらNG。
　なんだけど、構築がつらい。無限時間かけた。。結局どうやるのが楽だったんだろ。
・終了後、ちょっと構築パートを再考。制約的に線形じゃなくてもいいから、
　こんな感じで2乗かけて位置の変更を落ち着いてシミュれればよかったかもしれない。
　(それでも、これもぱっと考えた感じではなく、手元で動きを追いながらガチャガチャした。)
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
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    vector<array<ll, 3>> arr;
    rep(i, N) {
        arr.pb({A[i], B[i], i});
    }
    sort(ALL(arr));
    rep(i, N-1) {
        if (arr[i][1] > arr[i+1][1]) {
            print(-1);
            return;
        }
    }

    vector<ll> pos(N);
    rep(i, N) {
        pos[i] = arr[i][2];
    }
    vector<pll> ans;
    rep(i, N) {
        if (pos[i] != i) {
            ans.eb(pos[i]+1, i+1);
            rep(j, i+1, N) {
                if (pos[j] == i) {
                    pos[j] = pos[i];
                    break;
                }
            }
        }
    }
    print(ans.size());
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
