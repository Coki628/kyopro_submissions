/*
・実験エスパー
・しばらく眺めても確実な考察が出ない。簡単な規則性がありそうなのは分かる。
　よって実験エスパーを敢行。やりやすさのため、逆操作。
　そこから読み取れた情報(ソース内コメント参照)を元に解く。
・こういうのちゃんと考察で解きたいよね…。
　今回は0,1,2に3色割り当てればmod 3で不変なのを使うと良かった模様。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    char X;
    cin >> N >> X;
    string S;
    cin >> S;

    // ll M = 5;
    // auto visited = listnd(M, M, M, 0);
    // auto rec = [&](auto &&f, ll r, ll b, ll w) {
    //     if (r >= M or b >= M or w >= M) return;
    //     if (visited[r][b][w]) return;
    //     visited[r][b][w] = 1;

    //     if (w >= 1) {
    //         f(f, r, b, w + 1);
    //         f(f, r + 1, b + 1, w - 1);
    //     }
    //     if (r >= 1) {
    //         f(f, r - 1, b + 2, w);
    //         f(f, r, b, w + 1);
    //     }
    //     if (b >= 1) {
    //         f(f, r + 2, b - 1, w);
    //         f(f, r, b, w + 1);
    //     }
    // };
    // print();
    // print('R');
    // rec(rec, 1, 0, 0);
    // rep(r, M) {
    //     rep(b, M) {
    //         rep(w, M) {
    //             if (visited[r][b][w]) {
    //                 array<ll, 3> rbw = {r, b, w};
    //                 debug(rbw);
    //                 print();
    //             }
    //         }
    //     }
    // }
    // visited = listnd(M, M, M, 0);
    // print();
    // print('B');
    // rec(rec, 0, 1, 0);
    // rep(r, M) {
    //     rep(b, M) {
    //         rep(w, M) {
    //             if (visited[r][b][w]) {
    //                 array<ll, 3> rbw = {r, b, w};
    //                 debug(rbw);
    //                 print();
    //             }
    //         }
    //     }
    // }
    // visited = listnd(M, M, M, 0);
    // print();
    // print('W');
    // rec(rec, 0, 0, 1);
    // rep(r, M) {
    //     rep(b, M) {
    //         rep(w, M) {
    //             if (visited[r][b][w]) {
    //                 array<ll, 3> rbw = {r, b, w};
    //                 debug(rbw);
    //                 print();
    //             }
    //         }
    //     }
    // }

    // R,Bはmod 3で同一、Wは何でもいい、どう消してもラス1は結局一意
    auto C = Counter(S);
    ll r = C['R'] % 3;
    ll b = C['B'] % 3;
    while (max(r, b) >= 2) {
        if (r >= 2) {
            r -= 2;
            b++;
        } else if (b >= 2) {
            b -= 2;
            r++;
        }
    }
    char res;
    if (r == 1 and b == 0) {
        res = 'R';
    } else if (b == 1 and r == 0) {
        res = 'B';
    } else {
        res = 'W';
    }
    if (res == X) {
        Yes();
    } else {
        No();
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
