/*
・なんとか自力AC！これで無事Sランク。
・構文解析、再帰探索
・ナメてかかったら結構やり慣れないタイプの問題(構文解析)来て焦ったわ。
・途中幼稚園のお迎えが入った(1時間くらいあれば片付くかと思ったら無理だったので…)
　のもあったけど、満点の期限2時間に結構ギリギリで間に合った。
・全体的には、再帰でその括弧の内側の結果を出して、
　戻した時(括弧を閉じた時)に、外側の情報と適切にマージする感じ。
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
#include "common/print.hpp"
#include "common/toint.hpp"

void solve() {
    string S;
    cin >> S;
    S = "(" + S + ")";
    ll N = S.size();

    map<char, ll> C;
    auto rec = [&](auto&& f, ll i) -> pair<vector<pair<char, ll>>, ll> {
        string curds = "";
        vector<pair<char, ll>> res;
        rep(j, i, N) {
            if (S[j] == '(') {
                ll curd = curds == "" ? 1 : toint(curds);
                auto [tmp, k] = f(f, j+1);
                for (auto [c, d] : tmp) {
                    res.eb(c, d * curd);
                }
                curds = "";
                j = k;
            } elif (S[j] == ')') {
                return {res, j};
            } elif (isdigit(S[j])) {
                curds += S[j];
            } elif (islower(S[j])) {
                res.eb(S[j], curds == "" ? 1 : toint(curds));
                curds = "";
            }
        }
        return {res, N};
    };
    auto [res, _] = rec(rec, 0);
    for (auto [c, d] : res) {
        C[c] += d;
    }
    rep(c, 'a', 'z'+1) {
        print(mkp((char)c, C[c]));
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
