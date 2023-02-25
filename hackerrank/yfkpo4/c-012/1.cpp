/*
・自力ならず。悔しいー。
・場合分け
・0,1,2それぞれになるケースを考えると、1は1だけになる区間、0は0が1つでも含まれる区間、
　2は2が1つと1がたくさんの区間、となるので場合分けする。
　ランレングスして、1は割と自明、0も余事象使えばOK、で2でWAが取れずコンテスト終了…。
・家帰ってしばらく考えると、2がたくさんある区間まで左右の分を数えてしまっていたので、
　そこを修正したら無事AC。ちゃんと落ち着いて考えたら通せる問題だったよなーこれは。
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
    vector<ll> A(N);
    cin >> A;

    auto rle = RLE(A);
    vector<ll> A2(N);
    rep(i, N) {
        A2[i] = A[i] != 0;
    }
    auto rle2 = RLE(A2);

    vector<ll> ans(3);
    ans[0] = nC2(N);
    ll M = rle.size();
    rep(i, M) {
        auto [k, cnt] = rle[i];
        if (k == 1) {
            ans[1] += nC2(cnt);
        } else if (k == 2) {
            if (i > 0) {
                auto [k2, cnt2] = rle[i - 1];
                if (k2 == 1) {
                    // ...1112...
                    ans[2] += cnt2;
                }
            }
            if (i < M - 1) {
                auto [k2, cnt2] = rle[i + 1];
                if (k2 == 1) {
                    // ...2111...
                    ans[2] += cnt2;
                }
            }
            // 1個だけの2なら左右の1同士でペアを作れる
            if (i > 0 and i < M - 1 and cnt == 1) {
                auto [k2, cnt2] = rle[i - 1];
                auto [k3, cnt3] = rle[i + 1];
                if (k2 == 1 and k3 == 1) {
                    // ...1112111...
                    ans[2] += (ll)cnt2 * (ll)cnt3;
                }
            }
        }
    }
    for (auto [k, cnt] : rle2) {
        // 0は全体から0がない区間ペアを全部引く
        if (k) {
            ans[0] -= nC2(cnt);
        }
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
