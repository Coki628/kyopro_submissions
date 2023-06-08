/*
・これはbayashikoさんが言ってた、ソート済判定を差分列の最小値セグ木でやる方針。
　差分列な分、添字管理がだるいけど、考察自体はすごくシンプルで、
　差分列が下がってる所が区間内に1つでもあればソート済じゃないとするもの。
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
    ll Q;
    cin >> Q;
    ll M = 26;
    vector<BIT<ll>> bit(M, BIT<ll>{N});
    rep(i, N) {
        bit[A[i]].add(i, 1);
    }
    auto C = Counter(A);
    auto seg = get_segment_tree(N, [](ll a, ll b) { return min(a, b); }, INF);
    rep(i, 1, N) {
        seg.set(i, A[i] - A[i - 1]);
    }
    seg.build();

    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            char c;
            cin >> x >> c;
            x--;
            c -= 'a';
            bit[A[x]].add(x, -1);
            bit[c].add(x, 1);
            C[A[x]]--;
            C[c]++;
            A[x] = c;
            if (x > 0) {
                seg.update(x, A[x] - A[x - 1]);
            }
            if (x < N - 1) {
                seg.update(x + 1, A[x + 1] - A[x]);
            }
        } else {
            ll l, r;
            cin >> l >> r;
            l--;

            deque<pll> que;
            rep(c, M) {
                que.eb(c, bit[c].query(l, r));
            }
            bool ok = true;
            // ソート済か
            if (seg.query(l + 1, r) >= 0) {
                while (que.front().second == 0) {
                    que.pop_front();
                }
                while (que.back().second == 0) {
                    que.pop_back();
                }
                ll n = que.size();
                assert(n >= 1);
                rep(j, n) {
                    if (j == 0 or j == n - 1) continue;
                    auto [k, v] = que[j];
                    // 左右端以外の文字の個数が合ってるか
                    if (C[k] != v) {
                        ok = false;
                        break;
                    }
                }
            } else {
                ok = false;
            }
            if (ok) {
                Yes();
            } else {
                No();
            }
        }
    }
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
