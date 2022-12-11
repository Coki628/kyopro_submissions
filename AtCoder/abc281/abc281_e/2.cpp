/*
・途中でTLEがmultisetが重いからの可能性も考えて、
　プリキュー2本のやつも書いた時の。これも同じのでTLEして撃沈。
　そして同じようにサイズチェック入れたら問題なく通った。。
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

#include "mystl/my_multiset.hpp"

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> A(N);
    cin >> A;

    priority_queue<pll, vector<pll>> left;
    priority_queue<pll, vector<pll>, greater<pll>> right;
    // 0: init, 1: left, 2: right, 3: out
    vector<ll> state(N);
    rep(i, M) {
        right.push({A[i], i});
        state[i] = 2;
    }
    ll cur = 0;
    rep(i, K) {
        cur += right.top().first;
        state[right.top().second] = 1;
        left.push(right.top());
        right.pop();
    }
    vector<ll> ans;
    ans.eb(cur);

    rep(i, M, N) {
        ll nxta = A[i];
        ll prva = A[i - M];
        if (state[i - M] == 1) {
            state[i - M] = 3;
            cur -= prva;
            while (left.size() and state[left.top().second] == 3) {
                left.pop();
            }
            while (right.size() and state[right.top().second] == 3) {
                right.pop();
            }
            if (right.size() and right.top().first < nxta) {
                cur += right.top().first;
                state[right.top().second] = 1;
                left.push(right.top());
                right.pop();
                right.push({nxta, i});
                state[i] = 2;
            } else {
                cur += nxta;
                left.push({nxta, i});
                state[i] = 1;
            }
        } else {
            assert(state[i - M] == 2);
            state[i - M] = 3;
            while (left.size() and state[left.top().second] == 3) {
                left.pop();
            }
            while (right.size() and state[right.top().second] == 3) {
                right.pop();
            }
            if (left.size() and left.top().first > nxta) {
                cur -= left.top().first;
                cur += nxta;
                state[left.top().second] = 2;
                right.push(left.top());
                left.pop();
                left.push({nxta, i});
                state[i] = 1;
            } else {
                right.push({nxta, i});
                state[i] = 2;
            }
        }
        ans.eb(cur);
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
