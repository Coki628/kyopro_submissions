/*
・dojo set_e_6_3
・なんとか自力AC。ペナ出し過ぎ…。
・差分、累積和応用
・検討すると、K要素の連続した区間を選ぶのが良さそうとなる。
　まず先頭K要素で作って、1つずつずらして増減を足し引きする。
　増減分は、差分列を前後から累積和したものから、
　さらに区間和のようなものを取ると求まる。
　ようなものと言うのは、累積和の区間和から、
　「手前の余計な分*区間長」を差し引く必要があるからそう言った。
　差分になったり累積和2回したり、添字がゴチャゴチャでつらい。
　なかなか合わないしサンプル超弱いし、5ペナくらいしてやっと通った…。
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

template<typename T>
vector<T> subarray(const vector<T>& A, int l, int r) {
    return vector<T>(A.begin()+l, A.begin()+r);
}

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    ll K;
    cin >> K;

    vector<pll> AI;
    rep(i, N) {
        AI.eb(A[i], i+1);
    }
    sort(ALL(AI));
    vector<ll> ids;
    tie(A, ids) = zip(AI);
    ll base = 0;
    rep(i, K-1) {
        ll d = A[i+1] - A[i];
        base += d * (i+1) * (K-i-1);
    }

    vector<ll> B(N-1);
    rep(i, N-1) {
        B[i] = A[i+1] - A[i];
    }
    auto tmp = B;
    rep(i, N-2) {
        tmp[i+1] += tmp[i];
    }
    auto tmprev = B;
    rep(i, N-3, -1, -1) {
        tmprev[i] += tmprev[i+1];
    }
    Accumulate<ll> acc(tmp), accrev(tmprev);
    ll mn = base;
    ll mni = 0;
    rep(j, K, N) {
        ll i = j - K;
        ll d = acc.query(i, i+K-1);
        if (i-1 >= 0) {
            d -= tmp[i-1] * (K-1);
        }
        base -= d;
        d = accrev.query(i+1, i+K);
        if (i+K < N-1) {
            d -= tmprev[i+K] * (K-1);
        }
        base += d;
        if (chmin(mn, base)) {
            mni = i + 1;
        }
    }
    vector<ll> ans(subarray(ids, mni, mni+K));
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
