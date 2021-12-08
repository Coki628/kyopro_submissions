/*
参考：https://blog.hamayanhamayan.com/entry/2019/12/07/000441
　　　https://math314.hateblo.jp/entry/2015/05/07/014908
・ライブラリ整備：FPS
・任意MODのFFTがACL依存だと難しそうだったので、はまやんさんのやつそのまま使った。
・ようはDP遷移が規則的な、行列累乗に乗りそうなやつとかはFPSでも叩けることがあるぽいな。
　それも制約10万が通るならかなり強力だな。
*/

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
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(const vector<T> &A) { rep(i, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(const deque<T> &A) { vector<T> V(A.begin(), A.end()); print(V); }
template<typename T> void print(const set<T> &S) { vector<T> A(S.begin(), S.end()); print(A); }

template<int mod> struct ModInt { int x; ModInt() : x(0) {} ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {} ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; } ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; } ModInt &operator*=(const ModInt &p) { x = (int) (1LL * x * p.x % mod); return *this; } ModInt &operator/=(const ModInt &p) { *this *= p.inverse(); return *this; } ModInt operator-() const { return ModInt(-x); } ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; } ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; } ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; } ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; } bool operator==(const ModInt &p) const { return x == p.x; } bool operator!=(const ModInt &p) const { return x != p.x; } ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); } ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; } friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; } friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); } static int get_mod() { return mod; } };
using mint = ModInt<MOD>;

template<typename T>
struct FormalPowerSeries {
    using Poly = vector<T>;
    using Conv = function<Poly(Poly, Poly)>;
    Conv conv;
    FormalPowerSeries(Conv conv) :conv(conv) {}

    Poly pre(const Poly& as, int deg) {
        return Poly(as.begin(), as.begin() + min((int)as.size(), deg));
    }

    Poly add(Poly as, Poly bs) {
        int sz = max(as.size(), bs.size());
        Poly cs(sz, T(0));
        for (int i = 0; i < (int)as.size(); i++) cs[i] += as[i];
        for (int i = 0; i < (int)bs.size(); i++) cs[i] += bs[i];
        return cs;
    }

    Poly sub(Poly as, Poly bs) {
        int sz = max(as.size(), bs.size());
        Poly cs(sz, T(0));
        for (int i = 0; i < (int)as.size(); i++) cs[i] += as[i];
        for (int i = 0; i < (int)bs.size(); i++) cs[i] -= bs[i];
        return cs;
    }

    Poly mul(Poly as, Poly bs) {
        return conv(as, bs);
    }

    Poly mul(Poly as, T k) {
        for (auto& a : as) a *= k;
        return as;
    }

    // F(0) must not be 0, 第2引数は返す項数
    Poly inv(Poly as, int deg) {
        assert(as[0] != T(0));
        Poly rs({ T(1) / as[0] });
        for (int i = 1; i < deg; i <<= 1)
            rs = pre(sub(add(rs, rs), mul(mul(rs, rs), pre(as, i << 1))), i << 1);
        return rs;
    }

    // not zero
    Poly div(Poly as, Poly bs) {
        while (as.back() == T(0)) as.pop_back();
        while (bs.back() == T(0)) bs.pop_back();
        if (bs.size() > as.size()) return Poly();
        reverse(as.begin(), as.end());
        reverse(bs.begin(), bs.end());
        int need = as.size() - bs.size() + 1;
        Poly ds = pre(mul(as, inv(bs, need)), need);
        reverse(ds.begin(), ds.end());
        return ds;
    }

    // F(0) must be 1
    Poly sqrt(Poly as, int deg) {
        assert(as[0] == T(1));
        T inv2 = T(1) / T(2);
        Poly ss({ T(1) });
        for (int i = 1; i < deg; i <<= 1) {
            ss = pre(add(ss, mul(pre(as, i << 1), inv(ss, i << 1))), i << 1);
            for (T& x : ss) x *= inv2;
        }
        return ss;
    }

    Poly diff(Poly as) {
        int n = as.size();
        Poly res(n - 1);
        for (int i = 1; i < n; i++) res[i - 1] = as[i] * T(i);
        return res;
    }

    Poly integral(Poly as) {
        int n = as.size();
        Poly res(n + 1);
        res[0] = T(0);
        for (int i = 0; i < n; i++) res[i + 1] = as[i] / T(i + 1);
        return res;
    }

    // F(0) must be 1
    Poly log(Poly as, int deg) {
        return pre(integral(mul(diff(as), inv(as, deg))), deg);
    }

    // F(0) must be 0
    Poly exp(Poly as, int deg) {
        Poly f({ T(1) });
        as[0] += T(1);
        for (int i = 1; i < deg; i <<= 1)
            f = pre(mul(f, sub(pre(as, i << 1), log(f, i << 1))), i << 1);
        return f;
    }

    Poly partition(int n) {
        Poly rs(n + 1);
        rs[0] = T(1);
        for (int k = 1; k <= n; k++) {
            if (1LL * k * (3 * k + 1) / 2 <= n) rs[k * (3 * k + 1) / 2] += T(k % 2 ? -1LL : 1LL);
            if (1LL * k * (3 * k - 1) / 2 <= n) rs[k * (3 * k - 1) / 2] += T(k % 2 ? -1LL : 1LL);
        }
        return inv(rs, n + 1);
    }
};
template<class T> T extgcd(T a, T b, T& x, T& y) { for (T u = y = 1, v = x = 0; a;) { T q = b / a; swap(x -= q * u, u); swap(y -= q * v, v); swap(b -= q * a, a); } return b; }
template<class T> T mod_inv(T a, T m) { T x, y; extgcd(a, m, x, y); return (m + x % m) % m; }
ll mod_pow(ll a, ll n, ll mod) { ll ret = 1; ll p = a % mod; while (n) { if (n & 1) ret = ret * p % mod; p = p * p % mod; n >>= 1; } return ret; }
struct MathsNTTModAny {
    template<int mod, int primitive_root>
    class NTT {
    public:
        int get_mod() const { return mod; }
        void _ntt(vector<ll>& a, int sign) {
            const int n = (int)a.size();
            assert((n ^ (n & -n)) == 0); //n = 2^k

            const int g = 3; //g is primitive root of mod
            int h = (int)mod_pow(g, (mod - 1) / n, mod); // h^n = 1
            if (sign == -1) h = (int)mod_inv(h, mod); //h = h^-1 % mod

            //bit reverse
            int i = 0;
            for (int j = 1; j < n - 1; ++j) {
                for (int k = n >> 1; k > (i ^= k); k >>= 1);
                if (j < i) swap(a[i], a[j]);
            }

            for (int m = 1; m < n; m *= 2) {
                const int m2 = 2 * m;
                const ll base = mod_pow(h, n / m2, mod);
                ll w = 1;
                rep(x, m) {
                    for (int s = x; s < n; s += m2) {
                        ll u = a[s];
                        ll d = a[s + m] * w % mod;
                        a[s] = u + d;
                        if (a[s] >= mod) a[s] -= mod;
                        a[s + m] = u - d;
                        if (a[s + m] < 0) a[s + m] += mod;
                    }
                    w = w * base % mod;
                }
            }

            for (auto& x : a) if (x < 0) x += mod;
        }
        void ntt(vector<ll>& input) {
            _ntt(input, 1);
        }
        void intt(vector<ll>& input) {
            _ntt(input, -1);
            const int n_inv = mod_inv((int)input.size(), mod);
            for (auto& x : input) x = x * n_inv % mod;
        }

        vector<ll> convolution(const vector<ll>& a, const vector<ll>& b) {
            int ntt_size = 1;
            while (ntt_size < (int)a.size() + (int)b.size()) ntt_size *= 2;

            vector<ll> _a = a, _b = b;
            _a.resize(ntt_size); _b.resize(ntt_size);

            ntt(_a);
            ntt(_b);

            rep(i, ntt_size) {
                (_a[i] *= _b[i]) %= mod;
            }

            intt(_a);
            return _a;
        }
    };

    ll garner(vector<pair<int, int>> mr, int mod) {
        mr.emplace_back(mod, 0);

        vector<ll> coffs(((int)mr.size()), 1);
        vector<ll> constants(((int)mr.size()), 0);
        rep(i, ((int)mr.size()) - 1) {
            // coffs[i] * v + constants[i] == mr[i].second (mod mr[i].first)
            ll v = (mr[i].second - constants[i]) * mod_inv<ll>(coffs[i], mr[i].first) % mr[i].first;
            if (v < 0) v += mr[i].first;

            for (int j = i + 1; j < ((int)mr.size()); j++) {
                (constants[j] += coffs[j] * v) %= mr[j].first;
                (coffs[j] *= mr[i].first) %= mr[j].first;
            }
        }

        return constants[((int)mr.size()) - 1];
    }

    typedef NTT<167772161, 3> NTT_1;
    typedef NTT<469762049, 3> NTT_2;
    typedef NTT<1224736769, 3> NTT_3;

    vector<ll> solve(vector<ll> a, vector<ll> b, int mod = 1000000007) {
        for (auto& x : a) x %= mod;
        for (auto& x : b) x %= mod;

        NTT_1 ntt1; NTT_2 ntt2; NTT_3 ntt3;
        assert(ntt1.get_mod() < ntt2.get_mod() && ntt2.get_mod() < ntt3.get_mod());
        auto x = ntt1.convolution(a, b);
        auto y = ntt2.convolution(a, b);
        auto z = ntt3.convolution(a, b);

        const ll m1 = ntt1.get_mod(), m2 = ntt2.get_mod(), m3 = ntt3.get_mod();
        const ll m1_inv_m2 = mod_inv<ll>(m1, m2);
        const ll m12_inv_m3 = mod_inv<ll>(m1 * m2, m3);
        const ll m12_mod = m1 * m2 % mod;
        vector<ll> ret((int)x.size());
        rep(i, (int)x.size()) {
            ll v1 = (y[i] - x[i]) * m1_inv_m2 % m2;
            if (v1 < 0) v1 += m2;
            ll v2 = (z[i] - (x[i] + m1 * v1) % m3) * m12_inv_m3 % m3;
            if (v2 < 0) v2 += m3;
            ll constants3 = (x[i] + m1 * v1 + m12_mod * v2) % mod;
            if (constants3 < 0) constants3 += mod;
            ret[i] = constants3;
        }

        return ret;
    }

    vector<int> solve(vector<int> a, vector<int> b, int mod = 1000000007) {
        vector<ll> x(ALL(a));
        vector<ll> y(ALL(b));

        auto z = solve(x, y, mod);
        vector<int> res;
        for (auto &aa : z) res.push_back(aa % mod);

        return res;
    }

    vector<mint> solve(vector<mint> a, vector<mint> b, int mod = 1000000007) {
        int n = a.size();
        vector<ll> x(n);
        rep(i, 0, n) x[i] = a[i].x;
        n = b.size();
        vector<ll> y(n);
        rep(i, 0, n) y[i] = b[i].x;

        auto z = solve(x, y, mod);
        vector<int> res;
        for (auto &aa : z)  res.push_back(aa % mod);

        vector<mint> res2;
        for (auto &x : res) res2.push_back(x);

        return res2;
    }
};
/*
    FormalPowerSeries<mint> fps([&](auto a, auto b) {
        MathsNTTModAny ntt;
        return ntt.solve(a, b);
    });
*/

void solve() {
    ll K, N;
    cin >> K >> N;
    auto A = LIST(N);

    vector<mint> G(K+1);
    rep(i, N) {
        G[A[i]] += 1;
    }
    FormalPowerSeries<mint> fps([&](auto a, auto b) {
        MathsNTTModAny ntt;
        return ntt.solve(a, b);
    });
    vector<mint> F(K+1);
    F[0] = 1;
    // mint ans = 0;
    // rep(_, K) {
    //     // dp[i+1] = dp[i]+A
    //     F = fps.mul(F, G);
    //     // ans += dp[i+1][K]
    //     ans += F[K];
    // }
    // print(ans);

    // 1/(1-G)
    F = fps.inv(fps.sub(F, G), K+1);
    mint ans = F[K];
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
