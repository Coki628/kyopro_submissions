/**
 * 参考：http://www.utpc.jp/2014/slides/I.pdf
 * 　　　https://kmjp.hatenablog.jp/entry/2015/05/25/0930
 * ・蟻本演習4-6-2
 * ・木クエリ系、マージテクの逆
 * ・難しかったけどためになったー。マージテクの逆、聞いたことあったけど初めてやった。
 * 　連結成分のマージはUFで簡単にやれる場合が多いけど、分裂はこうやってできるんだねー。
 * ・まず、連結成分はsetで辺集合を持つような形にする。これをpairでコストを前にして持てば、
 * 　コスト最小の辺がいつでも取れる。
 * ・で、連結成分を分割する際には、分けた時に辺の数が少なくなる方を動かすようにすれば、
 * 　マージテクと同じで計算量がlogになるのでいい感じ。
 * ・この時、どっちの集合の方が小さくなるかをチェックする時にもひと工夫必要になって、
 * 　これはBFSとかで両方の連結成分を並行に走査していって、どちらかが全部の頂点に行ききったところで
 * 　打ち切り、ってやると、小さい方の連結成分の頂点数くらいの計算量しかかからなくなるのでOK。
 * ・最初素直な実装で投げたら1個TLEで、多分スターグラフっぽいやつの時に、
 * 　大きい方の集合を先に走査してしまうと、その1回の分だけでも大きな計算量が取られるんだと思う。
 * 　BFSやる各回の前に、次の頂点から出る辺の数を数えて少ない方からやって、
 * 　先にやった方のキューが空になったら、もう反対側はやらないでbreakする、ってしたら無事AC。
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vector<set<ll>> nodes(N);
    // G[i] := i番目の連結成分に属する辺集合(コスト, 辺番号)
    vector<set<pll>> G(N);
    ll gsz = 1;
    // group[i] := i番目の辺が属する連結成分番号
    vector<ll> group(N-1);
    vector<pll> edges;
    vector<ll> cost(N-1);
    vector<bool> removed(N-1);
    map<pll, ll> edgetoid;
    rep(i, 0, N-1) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].insert(v);
        nodes[v].insert(u);
        G[0].insert({c, i});
        cost[i] = c;
        edges.pb({u, v});
        edgetoid[{u, v}] = i;
        edgetoid[{v, u}] = i;
    }

    ll Q;
    cin >> Q;
    rep(_, 0, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll i, d;
            cin >> i >> d;
            i--;
            if (!removed[i]) {
                ll g = group[i];
                G[g].erase({cost[i], i});
                cost[i] += d;
                G[g].insert({cost[i], i});
            }
        } else {
            ll i;
            cin >> i;
            i--;
            if (!removed[i]) {
                ll g = group[i];
                // iが属する連携つ成分でコスト最小の辺j
                auto [c, j] = *G[g].begin();
                print(j+1);
                removed[j] = 1;
                G[g].erase({c, j});
                auto [u, v] = edges[j];
                nodes[u].erase(v);
                nodes[v].erase(u);

                vector<ll> tmp[2];
                queue<pll> que[2];
                que[0].push({u, -1});
                que[1].push({v, -1});
                // 連結成分数の小さい方が弾切れになるまでBFSする
                bool ok = 1;
                while (ok) {
                    // 次の頂点から出る辺が少ない方からやる
                    if (nodes[que[0].front().first].size() > nodes[que[1].front().first].size()) {
                        swap(que[0], que[1]);
                        swap(tmp[0], tmp[1]);
                    }
                    rep(k, 0, 2) {
                        auto [u, prv] = que[k].front(); que[k].pop();
                        for (ll v : nodes[u]) {
                            if (v == prv) continue;
                            ll eid = edgetoid[{u, v}];
                            tmp[k].pb(eid);
                            que[k].push({v, u});
                        }
                        // 空になった時点で打ち切って逆側をやらない
                        if (que[k].empty()) {
                            ok = 0;
                            break;
                        }
                    }
                }
                if (que[0].size() > que[1].size()) {
                    swap(tmp[0], tmp[1]);
                }
                // サイズの小さかった方を、新たな連結成分として分割させる
                for (ll eid : tmp[0]) {
                    G[g].erase({cost[eid], eid});
                    G[gsz].insert({cost[eid], eid});
                    group[eid] = gsz;
                }
                gsz++;
            } else {
                print(-1);
            }
        }
    }
    return 0;
}
