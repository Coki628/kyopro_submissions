/*
・なんとか自力AC！
・サイクルシフト
・1がないと無理。1が先頭に来るまでサイクルさせておく。
　2番目は2、3番目以降は2以上で1つ手前+1以下、みたいにしたら通った。
　なんか条件書き違えてて、終盤D1解けなくて戻ってきた時に、
　それ気付いて書き直したら通ったんだよね。もったいない。
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

#include "mystl/my_deque.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    if (find(ALL(A), 1) == A.end()) {
        NO();
        return;
    }

    my_deque<ll> dq(ALL(A));
    while (dq[0] != 1) {
        dq.push_front(dq.pop_back());
    }
    rep(i, 1, N) {
        if (i == 1) {
            if (dq[i] != 2) {
                NO();
                return;
            }
        } else {
            if (dq[i] == 1 or (dq[i]-dq[i-1]) >= 2) {
                NO();
                return;
            }
        }
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
