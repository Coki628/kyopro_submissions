/*
参考：https://codeforces.com/blog/entry/98061
・むっず。自力ならず。
・辞書順最小、K番目の値、N進数に帰着
・これは出なかった。各aの間にある連続したbを増減させると辞書順も進むだけど、
　末尾に現れるbが増えれば1進み、末尾にそれ以上足せなくなったら1つ手前にbを増やして後ろが空、
　みたいなのを同じように進めてく。これはN進数で下位桁から順に値を上げていくような感じになる。
　今回さらに独特なのが、各桁で基数が違っても、1つのN進数と同様に扱えるということ。
　なんか直観的に下位桁の基準で値操作したら上位桁で基数変わった時に壊れるんじゃないかと
　思ったんだけど、そんなことない。各桁は独立に周期を持てる。
・なので各桁で基数変えながら10進→N進変換みたいな操作を進めて行くと良い。
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
    reverse(ALL(rle));
    X--;
    string ans;
    for (auto [c, cnt] : rle) {
        if (c == '*') {
            auto [d, m] = divmod(X, cnt*K+1);
            ans += string(m, 'b');
            X = d;
        } else {
            ans += string(cnt, 'a');
        }
    }
    reverse(ALL(ans));
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
