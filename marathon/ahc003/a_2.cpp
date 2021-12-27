/*
・マラソン精進
・なんか制約をよく見ると同じ行、同じ列は前後1000くらいの値に収まってるやつが半分くらいある
　みたいなことが書いてあって、これを利用できないか考えてみる。
・とりあえず結果出たところの行列に重み付けしていって、なるべく軽い方優先で進んでく、
　みたいにしてみた。スコアあまり変わらず615億くらい。
*/

#pragma region mytemplate

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
using vvpil = vector<vector<pil>>;
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for (ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for (ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for (ll i = a, _bb = b; (c > 0 && a <= i && i < _bb) or (c < 0 && a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define eb emplace_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define UNIQUE(A) sort(ALL(A)), A.erase(unique(ALL(A)), A.end())
#define elif else if
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(const pair<T1, T2> &p) { cout << p.first << ' ' << p.second << '\n'; }
template<typename T1, typename T2, typename T3> void print(const tuple<T1, T2, T3> &tp) { cout << get<0>(tp) << ' ' << get<1>(tp) << ' ' << get<2>(tp) << '\n'; }
template<typename T1, typename T2, typename T3, typename T4> void print(const tuple<T1, T2, T3, T4> &tp) { cout << get<0>(tp) << ' ' << get<1>(tp) << ' ' << get<2>(tp) << ' ' << get<3>(tp) << '\n'; }
template<typename T> void print(const vector<T> &V) { rep(i, V.size()) { cout << V[i]; if (i != V.size()-1) cout << ' '; } cout << '\n'; }
template<typename T, size_t SZ> void print(const array<T, SZ> &arr) { rep(i, arr.size()) { cout << arr[i]; if (i != arr.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(const deque<T> &que) { vector<T> V(ALL(que)); print(V); }
template<typename T> void print(const set<T> &se) { vector<T> V(ALL(se)); print(V); }
#define debug(x) (cout << #x << ": ", print(x));

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll ceil(ll a, ll b) { if (a >= 0) return (a+b-1) / b; else return a / b; }
template<typename T> pll divmod(ll a, T b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
ll gridtoid(ll i, ll j, ll W) { return i*W+j; }
pll idtogrid(ll id, ll W) { return divmod(id, W); }

string zfill(string str, int len) { string zeros; int n = str.size(); rep(i, len-n) zeros += '0'; return zeros+str; }

#pragma endregion

// [l,r)の範囲で乱数生成
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
ll randrange(ll l, ll r) {
    uniform_int_distribution<ll> rand(l, r-1);
    return rand(mt);
}

// 環境に依存せずミリ秒単位で時間取得するクラス
struct Timer {

    chrono::_V2::system_clock::time_point start_time;
    
    Timer() {
        start_time = this->now();
    }

    chrono::_V2::system_clock::time_point now() {
        return chrono::high_resolution_clock::now();
    }

    int64_t get_diff() {
        return chrono::duration_cast<chrono::milliseconds>(this->now() - start_time).count();
    }
};

const int H = 30, W = 30;
const int N = H*W;
const int Q = 1000;

int R[H][W], D[H][W];
vvi nodes(N);
int G[N][N];
map<char, ll> mp = {{'U', 0}, {'D', 1}, {'L', 2}, {'R', 3}};

void solve(ll t=-1) {
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/"+zfill(tostr(t), 4)+".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/"+zfill(tostr(t), 4)+".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print(-1);
            return;
        }
        rep(h, H) {
            rep(w, W-1) {
                cin >> R[h][w];
                ll u = gridtoid(h, w, W);
                ll v = gridtoid(h, w+1, W);
                G[u][v] = G[v][u] = R[h][w];
            }
        }
        rep(h, H-1) {
            rep(w, W) {
                cin >> D[h][w];
                ll u = gridtoid(h, w, W);
                ll v = gridtoid(h+1, w, W);
                nodes[u].eb(v);
                nodes[v].eb(u);
                G[u][v] = G[v][u] = D[h][w];
            }
        }
    #endif

    vector<ld> rows(H), cols(W);
    auto query = [&](ll sh, ll sw, ll th, ll tw, ll prev_result) {
        // 進行方向
        char hc = sh <= th ? 'D' : 'U';
        char wc = sw <= tw ? 'R' : 'L';
        // 回数
        ll hcnt = abs(sh-th);
        ll wcnt = abs(sw-tw);

        ll ch = sh, cw = sw;
        string res;
        while (hcnt or wcnt) {
            if (rows[ch] <= cols[cw] and hcnt or not wcnt) {
                auto [dh, dw] = directions[mp[hc]];
                hcnt--;
                res += hc;
                ch += dh;
            } else {
                auto [dh, dw] = directions[mp[wc]];
                wcnt--;
                res += wc;
                cw += dw;
            }
        }
        // while (hcnt or wcnt) {
        //     // 縦横どっちか
        //     auto hw = randrange(0, 2);
        //     if (hw) {
        //         if (hcnt == 0) continue;
        //         hcnt--;
        //         res += hc;
        //     } else {
        //         if (wcnt == 0) continue;
        //         wcnt--;
        //         res += wc;
        //     }
        // }
        return res;
    };

    auto calc_path_length = [&](ll sh, ll sw, ll th, ll tw, string path) -> ll {
        ll ch = sh, cw = sw;
        ll res = 0;
        for (char c : path) {
            auto [dh, dw] = directions[mp[c]];
            ll nh = ch+dh;
            ll nw = cw+dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) {
                return -1;
            }
            ll u = gridtoid(ch, cw, W);
            ll v = gridtoid(nh, nw, W);
            res += G[u][v];
            ch = nh, cw = nw;
        }
        return res;
    };

    ll prev_result = 0;
    ld score = 0.0;
    rep(i, Q) {
        ll sh, sw, th, tw;
        cin >> sh >> sw >> th >> tw;
        #ifdef __LOCAL
            ll a;
            ld e;
            cin >> a >> e;
        #endif

        string path = query(sh, sw, th, tw, prev_result);

        #ifdef __LOCAL
            ofs << path << endl;

            ll b = calc_path_length(sh, sw, th, tw, path);
            if (b == -1) {
                print(-1);
                return;
            }
            score = score*0.998 + a/(ld)b;
            prev_result = round(b*e);
        #else
            cout << path << endl;

            cin >> prev_result;
        #endif

        if (sh > th) swap(sh, th);
        if (sw > tw) swap(sw, tw);
        ll hlen = th-sh+1;
        ll wlen = tw-sw+1;
        rep(h, sh, th) {
            rows[h] += prev_result/hlen;
        }
        rep(w, sw, tw) {
            cols[w] += prev_result/wlen;
        }
    }
    #ifdef __LOCAL
        print(round(2312311*score));
    #endif
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // テスト実施数
        ll T = 10;
        rep(i, T) {
            solve(i);
        }
    #else
        solve();
    #endif

    return 0;
}
