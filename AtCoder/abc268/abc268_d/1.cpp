/*
・自力AC！
・工夫して全探索
・判定は予めsetに詰めとく。で、しんどめの全探索。
　順列全探索の内側で、アンスコの入れ方を再帰全探索した。
　雑にアンスコ16個までやったら3件TLEで、残りの使える個数とかを丁寧に枝刈りしたら通った。
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
    ll N, M;
    cin >> N >> M;
    vector<string> S(N);
    ll len = 0;
    rep(i, N) {
        cin >> S[i];
        len += S[i].size();
    }
    HashSet<string> se;
    rep(i, M) {
        string t;
        cin >> t;
        se.insert(t);
    }

    for (auto& perm : permutations(S)) {
        string cur;
        ll cnt = 0;
        auto rec = [&](auto&& f, ll i) {
            cur += perm[i];
            if (cur.size() > 16) {
                rep(_, perm[i].size()) {
                    cur.pop_back();
                }
                return;
            }
            if (i == N-1) {
                if (cur.size() < 3) {
                    rep(_, perm[i].size()) {
                        cur.pop_back();
                    }
                    return;
                } elif (not se.count(cur)) {
                    print(cur);
                    exit(0);
                } else {
                    rep(_, perm[i].size()) {
                        cur.pop_back();
                    }
                    return;
                }
            }
            rep(j, 1, 16-len-cnt+1) {
                string sep(j, '_');
                cur += sep;
                cnt += sep.size();
                f(f, i+1);
                cnt -= sep.size();
                rep(_, j) {
                    cur.pop_back();
                }
            }
            rep(_, perm[i].size()) {
                cur.pop_back();
            }
        };
        rec(rec, 0);
    }
    print(-1);
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
