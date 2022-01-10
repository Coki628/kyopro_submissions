/*
・jsc2019_qual_c
・自力AC！やったね。当時は自力通せなかったぽいし。
・括弧列に帰着
・この操作はある要素と、その先にある別の要素をペアにする、括弧列みたいな話と考えられる。
　で、前から見て行って、その時点での閉じてない括弧の偶奇によってその場所の白黒が決まる。
　とすると、例えば先頭要素はその要素を開き括弧とするか閉じ括弧とするかによってしか
　白黒を変えられないので、その時点での色に対して白くする操作は一意、
　同様に2番目の要素は最初の要素の操作は既に固定されているので、
　やはりその位置の要素の操作が一意となり、これが列の終わりまで一般に続く。
　この時、ある要素を閉じ括弧とする時、今残っている開き括弧のどれと組ませるか、
　というのは選択できるので、この分は通り数に掛ける。
　これでどの要素を開き/閉じ括弧とするかは一意になる、つまりペアが決まる。
　後はこれらのペアする操作はどの順番でやっても結果が変わらないので、
　操作回数の階乗をやる。これで答え。
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
constexpr double EPS = 1e-10;
constexpr double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;
    N *= 2;
    string S;
    cin >> S;

    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] == 'B';
    }
    ll cnt = 0;
    mint ans = 1;
    rep(i, N) {
        if (A[i] ^ (cnt%2)) {
            cnt++;
        } else {
            ans *= cnt;
            cnt--;
        }
        if (cnt < 0) {
            print(0);
            return;
        }
    }
    if (cnt > 0) {
        print(0);
        return;
    }
    ans *= factorial<mint>(N/2);
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
