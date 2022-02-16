/*
・dojo camp_cfdiv3_1
・きっちり自力AC！
・進数変換、中央値
・まず話を01文字列から、これを2進数とみなして10進数に変換しておくと見やすい。
　L未満の数が全てある所から、N個の値を取り除くとする。
　このうち、元の状態の中央値以下の数の個数によって、
　中央値が何個後ろにずれたかが分かる。削除済のものをset等で持っておいて、
　削除済でない場所が来る度に個数を1つずつ進めていけば、操作後の中央値が分かる。
　ここで前に進む回数はせいぜいN回くらいのはずなので間に合う。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include"../../../_lib/cpp/_src/numbers/ntod.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;

    ll L = pow(2, M);
    vector<ll> A;
    rep(i, N) {
        string s;
        cin >> s;
        A.eb(ntod(s, 2));
    }
    L -= N;
    ll mid = (L-1)/2;
    sort(ALL(A));
    ll cnt = bisect_right(A, mid);
    set<ll> se(ALL(A));
    while (cnt) {
        if (not se.count(mid+1)) {
            cnt--;
        }
        mid++;
    }
    auto ans = zfill(bin(mid), M);
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
