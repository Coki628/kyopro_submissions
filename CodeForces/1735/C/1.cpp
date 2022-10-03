/*
・自力AC！
・辞書順最小、UF
・辞書順最小なので、定番の前から貪欲で決めていく。
　文字同士をUFで連結チェックして最後以外は非連結な場所と繋ぐとした。
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
    string S;
    cin >> S;

    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] - 'a';
    }
    ll L = 26;
    map<ll, ll> mp;
    vector<ll> used(L);
    UnionFind uf(L);
    string ans;
    rep(i, N) {
        if (mp.count(A[i])) {
            ans += 'a' + mp[A[i]];
        } else {
            rep(c, L) {
                if (c == S[i]) continue;
                if (not used[c] and (mp.size() == L-1 or not uf.same(A[i], c))) {
                    used[c] = 1;
                    mp[A[i]] = c;
                    uf.merge(A[i], c);
                    ans += 'a' + c;
                    break;
                }
            }
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
