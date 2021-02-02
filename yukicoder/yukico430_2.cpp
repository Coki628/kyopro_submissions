/**
 * ・蟻本演習4-7-3
 * ・文字列検索、Aho-Corasick法
 * ・使い方が分かってきたのでこっちも解いてみる。
 * ・アホコラ、分かってくると、すごく強い道具なのが分かるね。。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define ALL(A) A.begin(), A.end()
#define elif else if
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll INF = 1e18;
constexpr ll MOD = 1000000007;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

vector<ll> LIST(ll N) { vector<ll> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(vector<T> A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

template< int char_size >
struct TrieNode {
    int nxt[char_size];

    int exist;
    vector< int > accept;

    TrieNode() : exist(0) {
        memset(nxt, -1, sizeof(nxt));
    }
};

template< int char_size, int margin >
struct Trie {
    using Node = TrieNode< char_size >;

    vector< Node > nodes;
    int root;

    Trie() : root(0) {
        nodes.push_back(Node());
    }

    void update_direct(int node, int id) {
        nodes[node].accept.push_back(id);
    }

    void update_child(int node, int child, int id) {
        ++nodes[node].exist;
    }

    void add(const string &str, int str_index, int node_index, int id) {
        if(str_index == str.size()) {
            update_direct(node_index, id);
        } else {
            const int c = str[str_index] - margin;
            if(nodes[node_index].nxt[c] == -1) {
                nodes[node_index].nxt[c] = (int) nodes.size();
                nodes.push_back(Node());
            }
            add(str, str_index + 1, nodes[node_index].nxt[c], id);
            update_child(node_index, nodes[node_index].nxt[c], id);
        }
    }

    void add(const string &str, int id) {
        add(str, 0, 0, id);
    }

    void add(const string &str) {
        add(str, nodes[0].exist);
    }

    void query(const string &str, const function< void(int) > &f, int str_index, int node_index) {
        for(auto &idx : nodes[node_index].accept) f(idx);
        if(str_index == str.size()) {
            return;
        } else {
            const int c = str[str_index] - margin;
            if(nodes[node_index].nxt[c] == -1) return;
            query(str, f, str_index + 1, nodes[node_index].nxt[c]);
        }
    }

    void query(const string &str, const function< void(int) > &f) {
        query(str, f, 0, 0);
    }

    int count() const {
        return (nodes[0].exist);
    }

    int size() const {
        return ((int) nodes.size());
    }
};

template< int char_size, int margin >
struct AhoCorasick : Trie< char_size + 1, margin > {
    using Trie< char_size + 1, margin >::Trie;

    const int FAIL = char_size;
    vector< int > correct;

    void build(bool heavy = true) {
        correct.resize(this->size());
        for(int i = 0; i < this->size(); i++) {
            correct[i] = (int) this->nodes[i].accept.size();
        }
        queue< int > que;
        for(int i = 0; i <= char_size; i++) {
            if(~this->nodes[0].nxt[i]) {
                this->nodes[this->nodes[0].nxt[i]].nxt[FAIL] = 0;
                que.emplace(this->nodes[0].nxt[i]);
            } else {
                this->nodes[0].nxt[i] = 0;
            }
        }
        while(!que.empty()) {
            auto &now = this->nodes[que.front()];
            int fail = now.nxt[FAIL];
            correct[que.front()] += correct[fail];
            que.pop();
            for(int i = 0; i < char_size; i++) {
                if(~now.nxt[i]) {
                    this->nodes[now.nxt[i]].nxt[FAIL] = this->nodes[fail].nxt[i];
                    if(heavy) {
                        auto &u = this->nodes[now.nxt[i]].accept;
                        auto &v = this->nodes[this->nodes[fail].nxt[i]].accept;
                        vector< int > accept;
                        set_union(begin(u), end(u), begin(v), end(v), back_inserter(accept));
                        u = accept;
                    }
                    que.emplace(now.nxt[i]);
                } else {
                    now.nxt[i] = this->nodes[fail].nxt[i];
                }
            }
        }
    }

    map< int, int > match(const string &str, int now = 0) {
        map< int, int > result;
        for(auto &c : str) {
            now = this->nodes[now].nxt[c - margin];
            for(auto &v : this->nodes[now].accept) result[v] += 1;
        }
        return result;
    }

    pair< int64_t, int > move(const char &c, int now = 0) {
        now = this->nodes[now].nxt[c - margin];
        return {correct[now], now};
    }

    pair< int64_t, int > move(const string &str, int now = 0) {
        int64_t sum = 0;
        for(auto &c : str) {
            auto nxt = move(c, now);
            sum += nxt.first;
            now = nxt.second;
        }
        return {sum, now};
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    string S;
    cin >> S;
    ll N = S.size();

    ll M;
    cin >> M;
    AhoCorasick<26, 'A'> aho;
    rep(i, 0, M) {
        string t;
        cin >> t;
        aho.add(t);
    }
    aho.build();

    ll ans = 0, v = 0, cnt = 0;
    rep(i, 0, N) {
        // i文字目まで終わった時のアホコラ上での位置v
        tie(cnt, v) = aho.move(S[i], v);
        // 合計が欲しいだけなので、ここで一致した分を足すだけ
        ans += cnt;
    }
    print(ans);
    return 0;
}
