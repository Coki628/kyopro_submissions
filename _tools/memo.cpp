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

// // 一発全インクルード
// #include <bits/stdc++.h>
// using namespace std;

// // どっちでもいい
// typedef long long ll;
// using ll = long long;

// // 高速化
// #define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    // // 降順ソート
    // sort(A.rbegin(), A.rend());
    // // 最大値
    // ll INF = LONG_LONG_MAX;
    // cout << INF << endl;

    // // 重複削除(案外めんどい)
    // sort(A.begin(), A.end());
    // A.erase(unique(ALL(A)), A.end());

    // 型が決まってれば、ペアもこれで入る
    // pair<int, int> p;
    // p = {2, 4};
    // // mapもこんな感じ
    // map<int, int> m;
    // m = {{123, 12}, {32, 14}};
    // int a, b;
    // for (auto p : m) {
    //     // あとペア分解する時これでいける
    //     tie(a, b) = p;
    // }
    // タプルでも。これ3要素以上の扱い楽になりそう
    // tuple<int, int, int> tpl;
    // int c;
    // tpl = {1, 3, 4};
    // tie(a, b, c) = tpl;

    // 累積和の先頭に0
    // vector<ll> acc;
    // acc.insert(acc.begin(), 0);

    // min,maxのラムダ
    // [](ll a, ll b) { return min(a, b); }
    // [](ll a, ll b) { return max(a, b); }
    // 大小比較関数
    // less_equal<ll>()
    // greater_equal<ll>()

    // vector -> set
    // unordered_set<ll> S(A.begin(), A.end());

    // c++17からはこう書ける
    // vector<pair<ll, ll>> AB;
    // for (auto &[a, b] : AB) {
    // }

    // substrは右端じゃなくて文字数渡す。多すぎたらよしなに切ってくれるぽい。
    // string s = "test";
    // string t = s.substr(1, 10);
    // cout << t << endl;

    // llでもldでも、その型の最大値が取れる
    // ll mx = numeric_limits<ll>::max();

    // main内での再帰の書き方
    // auto dfs = [&](auto&& f, ll u, ll prev) -> void {
    //     for (auto v : nodes[u]) {
    //         if (v == prev) continue;
    //         f(f, v, u);
    //     }
    //     return;
    // };
    // dfs(dfs, 0, -1);

    // これで数字判定できる
    if (isdigit('0')) {
    }

    // map逆順の回し方
    // for (auto itr = rbegin(mp); itr != rend(mp); itr++) {
    // }

    // char -> str
    // cout << string({'a'}) << endl;

    // これでカウントできる。(vectorもOK)
    // string s;
    // count(ALL(s), '1');

    // C++でスペース区切らないで1行取得
    // getline(cin, S);

    // メモリ開放
    // A.clear();
    // A.shrink_to_fit();

    // 2秒直前で打ち切り(単位はミリ秒じゃなくてマイクロ秒みたい)
    // clock_t start = clock();
    // clock_t cur = clock();
    // if (cur-start > 1900000) {
    //     // do something and exit
    //     exit(0);
    // }

    // 配列シャッフル
    // mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
    // shuffle(ALL(A), mt);

    // マルチテストケースで再帰の即returnさせたい時のtry/catch使用例
    // ll N;
    // cin >> N;
    // try {
    //     auto rec = [&](auto&& f, ll x) {
    //         if (N >= 11) {
    //             throw -1;
    //         }
    //         if (x == N) return;
    //         f(f, x+1);
    //     };
    //     rec(rec, 0);
    // } catch (int e) {
    //     print(e);
    //     return;
    // }

    // set<pair>の先頭要素
    // set<pair<ll, ll>> se;
    // (*se.begin()).first;
    // // これのが楽だね
    // se.begin()->first;

    // vectorのfind
    // find(ALL(A), x);

    // string <-> vector<char> 変換
    // string S = "1231223";
    // vector<char> A(ALL(S));
    // string T(ALL(A));

    // pushとかinsertの代わりにemplaceって使える(emplace_backみたいな)

    // vector<char> <=> string 変換
    // vector<char> v = {'a', 'b', 'c'};
    // string s = "abc";
    // print(string(ALL(v)));
    // print(vector<char>(ALL(s)));

    // ローカルだけ実行(要コンパイルオプション)
    // #ifdef __LOCAL
    //     debug(ans);
    // #endif

    // // ポインタのこと
    // struct Node {
    //     Node(ll val) : val(val) {}
    //     ll val;
    // };
    // // 構造体を初期化して普通の変数に代入
    // Node node = Node(5);
    // // 普通の変数 → ポインタに変換してポインタ変数に代入
    // Node *np = &node;
    // // ポインタ → ポインタ変数に代入
    // Node *np2 = np;
    // // ポインタ → 値に変換して普通の変数に代入
    // Node node3 = *np;
    // // 構造体を初期化して領域を確保してポインタ変数に代入
    // Node *np3 = new Node(7);
    // // 普通の変数からメンバにアクセス
    // print(node3.val);
    // // ポインタ変数からメンバにアクセス
    // print(np3->val);

    // setのマージ
    set<ll> se1, se2;
    se1.insert(ALL(se2));

    return 0;
}
