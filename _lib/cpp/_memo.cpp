#include "_tpl.cpp"

// 一発全インクルード
#include <bits/stdc++.h>
using namespace std;

// どっちででもいいみたい
typedef long long ll;
using ll = long long;

#define ALL(A) A.begin(), A.end()

// 高速化っぽい
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

vector<int> A;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    // 降順ソート   
    sort(A.rbegin(), A.rend());
    // 最大値
    ll INF = LONG_LONG_MAX;
    cout << INF << endl;

    // 重複削除(案外めんどい)
    sort(A.begin(), A.end());
    A.erase(unique(ALL(A)), A.end());

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
    ll mx = numeric_limits<ll>::max();

    // main内での再帰の書き方
    // auto dfs = [&](auto&& f, ll u, ll prev) -> void {
    //     for (auto v : nodes[u]) {
    //         if (v == prev) continue;
    //         f(f, v, u);
    //     }
    //     return;
    // };
    // dfs(dfs, 0, -1);

    // これで数字判定できるんだって。。
    if (isdigit('0')) {
    }

    // 逆順の回し方
    // for (auto itr = rbegin(mp); itr != rend(mp); itr++) {
    // }

    // char -> str
    cout << string({'a'}) << endl;

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

    set<pair<ll, ll>> se;
    (*se.begin()).first;
    // これのが楽だね
    se.begin()->first;

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

    return 0;
}
