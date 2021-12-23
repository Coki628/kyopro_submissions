/*
参考：https://twitter.com/kude_coder/status/1472261926076162048
・くでさんの別解。
・辞書順最小、K番目の値、N進数に帰着
・これは前(上位桁)から決めていく。これでもできる。
　自分より下位を動かして作れる通り数を調べておいて、
　Xとその通り数によって今の位置に使うbの個数を決める。
・これでも考え方の根っこは結局基数がないとダメな気はするけど、
　公式よりは直観的に思いつきやすい気がする。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll N, K, X;
    cin >> N >> K >> X;
    string S;
    cin >> S;

    auto rle = RLE(S);
    X--;
    string ans;
    ll M = rle.size();
    rep(i, M) {
        auto [c, cnt] = rle[i];
        if (c == '*') {
            // ここより下位でいくつ作れるか
            ll tmp = 1;
            rep(j, i+2, M, 2) {
                if (mul_overflow(tmp, rle[j].second*K+1)) {
                    tmp = INF;
                    break;
                }
                tmp *= rle[j].second*K+1;
            }
            ans += string(X/tmp, 'b');
            X %= tmp;
        } else {
            ans += string(cnt, 'a');
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
