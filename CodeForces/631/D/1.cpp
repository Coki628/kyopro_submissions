/*
・dojo set_e_6_4
・きっちり自力AC！
・ランレングス、ロリハ
・ちょっと実装重め系？まずは同じ文字が連続する所は繋いでランレングスを完全なものにする。
　で、文字列Bが長さ1だと色々困るので先に場合分けして処理。
　長さが2以上なら、先頭と末尾が合わなければ絶対NGなので、1つずつずらしてN箇所以下のチェックで済む。
　先頭末尾は文字の一致+長さがA>=Bかどうか、中の区間は完全一致が条件。
　中の区間の完全一致は予め(長さ,文字)ペアにロリハを仕込んでおけば、高速に一致判定できる。
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

#include "string/RollingHash.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<pair<ll, char>> A, B;
    rep(i, N) {
        string s;
        cin >> s;
        ll l = toint(s.substr(0, s.size()-2));
        char c = s.back();
        if (A.size() and A.back().second == c) {
            A.back().first += l;
        } else {
            A.eb(l, c);
        }
    }
    rep(i, M) {
        string s;
        cin >> s;
        ll l = toint(s.substr(0, s.size()-2));
        char c = s.back();
        if (B.size() and B.back().second == c) {
            B.back().first += l;
        } else {
            B.eb(l, c);
        }
    }
    N = A.size();
    M = B.size();

    if (M == 1) {
        ll ans = 0;
        auto [lb, cb] = B[0];
        for (auto [la, ca] : A) {
            if (ca == cb) {
                ans += max(la-lb+1, 0LL);
            }
        }
        print(ans);
        return;
    }

    assert(M >= 2);
    vector<ll> A2(N), B2(M);
    rep(i, N) {
        A2[i] = A[i].first*26 + (A[i].second-'a');
    }
    rep(i, M) {
        B2[i] = B[i].first*26 + (B[i].second-'a');
    }
    RollingHash rh;
    auto a_table = rh.build(A2);
    auto b_table = rh.build(B2);

    auto check1 = [](pair<ll, char> a, pair<ll, char> b) {
        return a.second == b.second and a.first >= b.first;
    };
    auto check2 = [&](ll l, ll r) {
        assert(r-l == M-2);
        return rh.query(a_table, l, r) == rh.query(b_table, 1, M-1);
    };
    ll ans = 0;
    rep(i, N-M+1) {
        ll j = i + M - 1;
        if (check1(A[i], B[0]) and check1(A[j], B[M-1]) and check2(i+1, j)) {
            ans++;
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
