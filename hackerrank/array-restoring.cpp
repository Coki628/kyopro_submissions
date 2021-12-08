/*
参考：https://blog.hamayanhamayan.com/entry/2019/12/07/000441
　　　https://opt-cp.com/fps-implementation/
　　　https://tsuchi.hateblo.jp/entry/2021/10/09/124804
・ライブラリ整備：FPS
・ついに着手したFPS絡みの整備。
　お気持ちの理解ははまやんさん、FPSライブラリ本体はnok0さん(この後のBM導入を見据えて)、
　FPSライブラリの使い方説明は主にoptさんの記事から、それぞれ参考にさせてもらった。
・とりあえずこの問題の解き方ははまやんさんの説明そのままなんだけど、色々あって。
・hackerrankの仕様？なのかasciiじゃない文字を受け付けなくて、日本語のコメントとか
　計算量の所に混ざってたギリシャ文字みたいのとかを取り除いた。非本質…。
　あとコード長制限50kbもオーバーしてたからいつものテンプレート外した。FFTのライブラリが重い。。
・これは10万くらい項がある2つの多項式の割り算がメインパートなんだけど、
　畳み込みの速いやつの制限みたいで、分母の後ろの方に係数0の項があるとバグるみたいなので、
　そこは取り除いてから割り算したらちゃんと動いた。
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

////////// FFT, MOD's FFT //////////
// --- ACL start --- //
#include <algorithm>
#include <array>
#include <cassert>
#include <type_traits>
#include <vector>
#ifdef _MSC_VER
#include <intrin.h>
#endif
namespace atcoder {
namespace internal {
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}
constexpr int bsf_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}
}  // namespace internal
}  // namespace atcoder
#include <cassert>
#include <numeric>
#include <type_traits>
#ifdef _MSC_VER
#include <intrin.h>
#endif
#include <utility>
#ifdef _MSC_VER
#include <intrin.h>
#endif
namespace atcoder {
namespace internal {
constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}
struct barrett {
    unsigned int _m;
    unsigned long long im;
    explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}
    unsigned int umod() const { return _m; }
    unsigned int mul(unsigned int a, unsigned int b) const {
        unsigned long long z = a;
        z *= b;
#ifdef _MSC_VER
        unsigned long long x;
        _umul128(z, im, &x);
#else
        unsigned long long x =
            (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
        unsigned int v = (unsigned int)(z - x * _m);
        if (_m <= v) v += _m;
        return v;
    }
};
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    unsigned long long r = 1;
    unsigned long long y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}
constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr long long bases[3] = {2, 7, 61};
    for (long long a : bases) {
        long long t = d;
        long long y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;
    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
constexpr int primitive_root_constexpr(int m) {
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int i = 3; (long long)(i)*i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        divs[cnt++] = x;
    }
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt; i++) {
            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
template <int m> constexpr int primitive_root = primitive_root_constexpr(m);
}  // namespace internal
}  // namespace atcoder
#include <cassert>
#include <numeric>
#include <type_traits>
namespace atcoder {
namespace internal {
#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value ||
                                  std::is_same<T, __int128>::value,
                              std::true_type,
                              std::false_type>::type;
template <class T>
using is_unsigned_int128 =
    typename std::conditional<std::is_same<T, __uint128_t>::value ||
                                  std::is_same<T, unsigned __int128>::value,
                              std::true_type,
                              std::false_type>::type;
template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value,
                              __uint128_t,
                              unsigned __int128>;
template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value ||
                                                  is_signed_int128<T>::value ||
                                                  is_unsigned_int128<T>::value,
                                              std::true_type,
                                              std::false_type>::type;
template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                                                 std::is_signed<T>::value) ||
                                                    is_signed_int128<T>::value,
                                                std::true_type,
                                                std::false_type>::type;
template <class T>
using is_unsigned_int =
    typename std::conditional<(is_integral<T>::value &&
                               std::is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              std::true_type,
                              std::false_type>::type;
template <class T>
using to_unsigned = typename std::conditional<
    is_signed_int128<T>::value,
    make_unsigned_int128<T>,
    typename std::conditional<std::is_signed<T>::value,
                              std::make_unsigned<T>,
                              std::common_type<T>>::type>::type;
#else
template <class T> using is_integral = typename std::is_integral<T>;
template <class T>
using is_signed_int =
    typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                              std::true_type,
                              std::false_type>::type;
template <class T>
using is_unsigned_int =
    typename std::conditional<is_integral<T>::value &&
                                  std::is_unsigned<T>::value,
                              std::true_type,
                              std::false_type>::type;
template <class T>
using to_unsigned = typename std::conditional<is_signed_int<T>::value,
                                              std::make_unsigned<T>,
                                              std::common_type<T>>::type;
#endif
template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;
template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;
template <class T> using to_unsigned_t = typename to_unsigned<T>::type;
}  // namespace internal
}  // namespace atcoder
namespace atcoder {
namespace internal {
struct modint_base {};
struct static_modint_base : modint_base {};
template <class T> using is_modint = std::is_base_of<modint_base, T>;
template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;
}  // namespace internal
template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
struct static_modint : internal::static_modint_base {
    using mint = static_modint;
  public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }
    static_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    static_modint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    static_modint(T v) {
        _v = (unsigned int)(v % umod());
    }
    unsigned int val() const { return _v; }
    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }
    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        if (prime) {
            assert(_v);
            return pow(umod() - 2);
        } else {
            auto eg = internal::inv_gcd(_v, m);
            assert(eg.first == 1);
            return eg.second;
        }
    }
    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }
  private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
    static constexpr bool prime = internal::is_prime<m>;
};
template <int id> struct dynamic_modint : internal::modint_base {
    using mint = dynamic_modint;
  public:
    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) {
        assert(1 <= m);
        bt = internal::barrett(m);
    }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }
    dynamic_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        long long x = (long long)(v % (long long)(mod()));
        if (x < 0) x += mod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        _v = (unsigned int)(v % mod());
    }
    unsigned int val() const { return _v; }
    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }
    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v += mod() - rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        _v = bt.mul(_v, rhs._v);
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        auto eg = internal::inv_gcd(_v, mod());
        assert(eg.first == 1);
        return eg.second;
    }
    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }
  private:
    unsigned int _v;
    static internal::barrett bt;
    static unsigned int umod() { return bt.umod(); }
};
template <int id> internal::barrett dynamic_modint<id>::bt(998244353);
using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;
namespace internal {
template <class T>
using is_static_modint = std::is_base_of<internal::static_modint_base, T>;
template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;
template <class> struct is_dynamic_modint : public std::false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};
template <class T>
using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;
}  // namespace internal
}  // namespace atcoder
namespace atcoder {
namespace internal {
template <class mint,
          int g = internal::primitive_root<mint::mod()>,
          internal::is_static_modint_t<mint>* = nullptr>
struct fft_info {
    static constexpr int rank2 = bsf_constexpr(mint::mod() - 1);
    std::array<mint, rank2 + 1> root;   // root[i]^(2^i) == 1
    std::array<mint, rank2 + 1> iroot;  // root[i] * iroot[i] == 1
    std::array<mint, std::max(0, rank2 - 2 + 1)> rate2;
    std::array<mint, std::max(0, rank2 - 2 + 1)> irate2;
    std::array<mint, std::max(0, rank2 - 3 + 1)> rate3;
    std::array<mint, std::max(0, rank2 - 3 + 1)> irate3;
    fft_info() {
        root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);
        iroot[rank2] = root[rank2].inv();
        for (int i = rank2 - 1; i >= 0; i--) {
            root[i] = root[i + 1] * root[i + 1];
            iroot[i] = iroot[i + 1] * iroot[i + 1];
        }
        {
            mint prod = 1, iprod = 1;
            for (int i = 0; i <= rank2 - 2; i++) {
                rate2[i] = root[i + 2] * prod;
                irate2[i] = iroot[i + 2] * iprod;
                prod *= iroot[i + 2];
                iprod *= root[i + 2];
            }
        }
        {
            mint prod = 1, iprod = 1;
            for (int i = 0; i <= rank2 - 3; i++) {
                rate3[i] = root[i + 3] * prod;
                irate3[i] = iroot[i + 3] * iprod;
                prod *= iroot[i + 3];
                iprod *= root[i + 3];
            }
        }
    }
};
template <class mint, internal::is_static_modint_t<mint>* = nullptr>
void butterfly(std::vector<mint>& a) {
    int n = int(a.size());
    int h = internal::ceil_pow2(n);
    static const fft_info<mint> info;
    int len = 0;  // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
    while (len < h) {
        if (h - len == 1) {
            int p = 1 << (h - len - 1);
            mint rot = 1;
            for (int s = 0; s < (1 << len); s++) {
                int offset = s << (h - len);
                for (int i = 0; i < p; i++) {
                    auto l = a[i + offset];
                    auto r = a[i + offset + p] * rot;
                    a[i + offset] = l + r;
                    a[i + offset + p] = l - r;
                }
                if (s + 1 != (1 << len))
                    rot *= info.rate2[bsf(~(unsigned int)(s))];
            }
            len++;
        } else {
            int p = 1 << (h - len - 2);
            mint rot = 1, imag = info.root[2];
            for (int s = 0; s < (1 << len); s++) {
                mint rot2 = rot * rot;
                mint rot3 = rot2 * rot;
                int offset = s << (h - len);
                for (int i = 0; i < p; i++) {
                    auto mod2 = 1ULL * mint::mod() * mint::mod();
                    auto a0 = 1ULL * a[i + offset].val();
                    auto a1 = 1ULL * a[i + offset + p].val() * rot.val();
                    auto a2 = 1ULL * a[i + offset + 2 * p].val() * rot2.val();
                    auto a3 = 1ULL * a[i + offset + 3 * p].val() * rot3.val();
                    auto a1na3imag =
                        1ULL * mint(a1 + mod2 - a3).val() * imag.val();
                    auto na2 = mod2 - a2;
                    a[i + offset] = a0 + a2 + a1 + a3;
                    a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
                    a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
                    a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
                }
                if (s + 1 != (1 << len))
                    rot *= info.rate3[bsf(~(unsigned int)(s))];
            }
            len += 2;
        }
    }
}
template <class mint, internal::is_static_modint_t<mint>* = nullptr>
void butterfly_inv(std::vector<mint>& a) {
    int n = int(a.size());
    int h = internal::ceil_pow2(n);
    static const fft_info<mint> info;
    int len = h;  // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
    while (len) {
        if (len == 1) {
            int p = 1 << (h - len);
            mint irot = 1;
            for (int s = 0; s < (1 << (len - 1)); s++) {
                int offset = s << (h - len + 1);
                for (int i = 0; i < p; i++) {
                    auto l = a[i + offset];
                    auto r = a[i + offset + p];
                    a[i + offset] = l + r;
                    a[i + offset + p] =
                        (unsigned long long)(mint::mod() + l.val() - r.val()) *
                        irot.val();
                    ;
                }
                if (s + 1 != (1 << (len - 1)))
                    irot *= info.irate2[bsf(~(unsigned int)(s))];
            }
            len--;
        } else {
            int p = 1 << (h - len);
            mint irot = 1, iimag = info.iroot[2];
            for (int s = 0; s < (1 << (len - 2)); s++) {
                mint irot2 = irot * irot;
                mint irot3 = irot2 * irot;
                int offset = s << (h - len + 2);
                for (int i = 0; i < p; i++) {
                    auto a0 = 1ULL * a[i + offset + 0 * p].val();
                    auto a1 = 1ULL * a[i + offset + 1 * p].val();
                    auto a2 = 1ULL * a[i + offset + 2 * p].val();
                    auto a3 = 1ULL * a[i + offset + 3 * p].val();
                    auto a2na3iimag =
                        1ULL *
                        mint((mint::mod() + a2 - a3) * iimag.val()).val();
                    a[i + offset] = a0 + a1 + a2 + a3;
                    a[i + offset + 1 * p] =
                        (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();
                    a[i + offset + 2 * p] =
                        (a0 + a1 + (mint::mod() - a2) + (mint::mod() - a3)) *
                        irot2.val();
                    a[i + offset + 3 * p] =
                        (a0 + (mint::mod() - a1) + (mint::mod() - a2na3iimag)) *
                        irot3.val();
                }
                if (s + 1 != (1 << (len - 2)))
                    irot *= info.irate3[bsf(~(unsigned int)(s))];
            }
            len -= 2;
        }
    }
}
template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution_naive(const std::vector<mint>& a,
                                    const std::vector<mint>& b) {
    int n = int(a.size()), m = int(b.size());
    std::vector<mint> ans(n + m - 1);
    if (n < m) {
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                ans[i + j] += a[i] * b[j];
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i + j] += a[i] * b[j];
            }
        }
    }
    return ans;
}
template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution_fft(std::vector<mint> a, std::vector<mint> b) {
    int n = int(a.size()), m = int(b.size());
    int z = 1 << internal::ceil_pow2(n + m - 1);
    a.resize(z);
    internal::butterfly(a);
    b.resize(z);
    internal::butterfly(b);
    for (int i = 0; i < z; i++) {
        a[i] *= b[i];
    }
    internal::butterfly_inv(a);
    a.resize(n + m - 1);
    mint iz = mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
    return a;
}
}  // namespace internal
template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution(std::vector<mint>&& a, std::vector<mint>&& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (std::min(n, m) <= 60) return convolution_naive(a, b);
    return internal::convolution_fft(a, b);
}
template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution(const std::vector<mint>& a,
                              const std::vector<mint>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (std::min(n, m) <= 60) return convolution_naive(a, b);
    return internal::convolution_fft(a, b);
}
template <unsigned int mod = 998244353,
          class T,
          std::enable_if_t<internal::is_integral<T>::value>* = nullptr>
std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    using mint = static_modint<mod>;
    std::vector<mint> a2(n), b2(m);
    for (int i = 0; i < n; i++) {
        a2[i] = mint(a[i]);
    }
    for (int i = 0; i < m; i++) {
        b2[i] = mint(b[i]);
    }
    auto c2 = convolution(move(a2), move(b2));
    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        c[i] = c2[i].val();
    }
    return c;
}
std::vector<long long> convolution_ll(const std::vector<long long>& a,
                                      const std::vector<long long>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    static constexpr unsigned long long MOD1 = 754974721;  // 2^24
    static constexpr unsigned long long MOD2 = 167772161;  // 2^25
    static constexpr unsigned long long MOD3 = 469762049;  // 2^26
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;
    static constexpr unsigned long long i1 =
        internal::inv_gcd(MOD2 * MOD3, MOD1).second;
    static constexpr unsigned long long i2 =
        internal::inv_gcd(MOD1 * MOD3, MOD2).second;
    static constexpr unsigned long long i3 =
        internal::inv_gcd(MOD1 * MOD2, MOD3).second;
    auto c1 = convolution<MOD1>(a, b);
    auto c2 = convolution<MOD2>(a, b);
    auto c3 = convolution<MOD3>(a, b);
    std::vector<long long> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        unsigned long long x = 0;
        x += (c1[i] * i1) % MOD1 * M2M3;
        x += (c2[i] * i2) % MOD2 * M1M3;
        x += (c3[i] * i3) % MOD3 * M1M2;
        long long diff =
            c1[i] - internal::safe_mod((long long)(x), (long long)(MOD1));
        if (diff < 0) diff += MOD1;
        static constexpr unsigned long long offset[5] = {
            0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
        x -= offset[diff % 5];
        c[i] = x;
    }
    return c;
}
}  // namespace atcoder
// --- ACL end --- //
////////// FFT, MOD's FFT //////////

#pragma region Math Formal Power Series
enum Mode {
    FAST = 1,
    NAIVE = -1,
};
template <class T, Mode mode = FAST>
struct FormalPowerSeries : std::vector<T> {
    using std::vector<T>::vector;
    using std::vector<T>::size;
    using std::vector<T>::resize;
    using std::vector<T>::begin;
    using std::vector<T>::insert;
    using std::vector<T>::erase;
    using F = FormalPowerSeries;
    using S = std::vector<std::pair<int, T>>;

    F &operator+=(const F &g) {
        for(int i = 0; i < int(std::min((*this).size(), g.size())); i++) (*this)[i] += g[i];
        return *this;
    }

    F &operator+=(const T &t) {
        assert(int((*this).size()));
        (*this)[0] += t;
        return *this;
    }

    F &operator-=(const F &g) {
        for(int i = 0; i < int(std::min((*this).size(), g.size())); i++) (*this)[i] -= g[i];
        return *this;
    }

    F &operator-=(const T &t) {
        assert(int((*this).size()));
        (*this)[0] -= t;
        return *this;
    }

    F &operator*=(const T &t) {
        for(int i = 0; i < int((*this).size()); ++i) (*this)[i] *= t;
        return *this;
    }

    F &operator/=(const T &t) {
        T div = t.inv();
        for(int i = 0; i < int((*this).size()); ++i) (*this)[i] *= div;
        return *this;
    }

    F &operator>>=(const int sz) {
        assert(sz >= 0);
        int n = (*this).size();
        (*this).erase((*this).begin(), (*this).begin() + std::min(sz, n));
        (*this).resize(n);
        return *this;
    }

    F &operator<<=(const int sz) {
        assert(sz >= 0);
        int n = (*this).size();
        (*this).insert((*this).begin(), sz, T(0));
        (*this).resize(n);
        return *this;
    }

    F &operator%=(const F &g) { return *this -= *this / g * g; }

    F &operator=(const std::vector<T> &v) {
        int n = (*this).size();
        for(int i = 0; i < n; ++i) (*this)[i] = v[i];
        return *this;
    }

    F operator-() const {
        F ret = *this;
        return ret * -1;
    }

    F &operator*=(const F &g) {
        if(mode == FAST) {
            int n = (*this).size();
            auto tmp = atcoder::convolution(*this, g);
            for(int i = 0; i < n; ++i) (*this)[i] = tmp[i];
            return *this;
        } else {
            int n = (*this).size(), m = g.size();
            for(int i = n - 1; i >= 0; --i) {
                (*this)[i] *= g[0];
                for(int j = 1; j < std::min(i + 1, m); j++)
                    (*this)[i] += (*this)[i - j] * g[j];
            }
            return *this;
        }
    }

    F &operator/=(const F &g) {
        if((*this).size() < g.size()) {
            (*this).assign((*this).size(), T(0));
            return *this;
        }
        if(mode == FAST) {
            int old = (*this).size();
            int n = (*this).size() - g.size() + 1;
            *this = ((*this).rev().pre(n) * g.rev().inv(n));
            (*this).rev_inplace();
            (*this).resize(old);
            return *this;
        } else {
            assert(g[0] != T(0));
            T ig0 = g[0].inv();
            int n = (*this).size(), m = g.size();
            for(int i = 0; i < n; ++i) {
                for(int j = 1; j < std::min(i + 1, m); ++j)
                    (*this)[i] -= (*this)[i - j] * g[j];
                (*this)[i] *= ig0;
            }
            return *this;
        }
    }

    F &operator*=(S g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        if(!d)
            g.erase(g.begin());
        else
            c = 0;
        for(int i = n - 1; i >= 0; --i) {
            (*this)[i] *= c;
            for(auto &[j, b] : g) {
                if(j > i) break;
                (*this)[i] += (*this)[i - j] * b;
            }
        }
        return *this;
    }

    F &operator/=(S g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        assert(!d and c != 0);
        T ic = c.inv();
        g.erase(g.begin());
        for(int i = 0; i < n; ++i) {
            for(auto &[j, b] : g) {
                if(j > i) break;
                (*this)[i] -= (*this)[i - j] * b;
            }
            (*this)[i] *= ic;
        }
        return *this;
    }

    F operator+(const F &g) const { return F(*this) += g; }

    F operator+(const T &t) const { return F(*this) += t; }

    F operator-(const F &g) const { return F(*this) -= g; }

    F operator-(const T &t) const { return F(*this) -= t; }

    F operator*(const F &g) const { return F(*this) *= g; }

    F operator*(const T &t) const { return F(*this) *= t; }

    F operator/(const F &g) const { return F(*this) /= g; }

    F operator/(const T &t) const { return F(*this) /= t; }

    F operator/(const S &g) const { return F(*this) /= g; }

    F operator%(const F &g) const { return F(*this) %= g; }

    F operator*=(const S &g) const { return F(*this) *= g; }

    F operator/=(const S &g) const { return F(*this) /= g; }

    F pre(int d) const { return F((*this).begin(), (*this).begin() + std::min((int)(*this).size(), d)); }

    F &shrink() {
        while(!(*this).empty() and (*this).back() == T(0)) (*this).pop_back();
        return *this;
    }

    F &rev_inplace() {
        reverse((*this).begin(), (*this).end());
        return *this;
    }
    F rev() const { return F(*this).rev_inplace(); }

    // *=(1 + cz^d)
    F &multiply(const int d, const T c) {
        int n = (*this).size();
        if(c == T(1))
            for(int i = n - d - 1; i >= 0; --i)
                (*this)[i + d] += (*this)[i];
        else if(c == T(-1))
            for(int i = n - d - 1; i >= 0; --i)
                (*this)[i + d] -= (*this)[i];
        else
            for(int i = n - d - 1; i >= 0; --i)
                (*this)[i + d] += (*this)[i] * c;
        return *this;
    }
    // /=(1 + cz^d)
    F &divide(const int d, const T c) {
        int n = (*this).size();
        if(c == T(1))
            for(int i = 0; i < n - d; ++i) (*this)[i + d] -= (*this)[i];
        else if(c == T(-1))
            for(int i = 0; i < n - d; ++i) (*this)[i + d] += (*this)[i];
        else
            for(int i = 0; i < n - d; ++i) (*this)[i + d] -= (*this)[i] * c;
        return *this;
    }

    //O(N)
    T eval(const T &t) const {
        int n = (*this).size();
        T res = 0, tmp = 1;
        for(int i = 0; i < n; ++i) res += (*this)[i] * tmp, tmp *= t;
        return res;
    }

    F inv(int deg = -1) const {
        int n = (*this).size();
        assert(mode == FAST and n and (*this)[0] != 0);
        if(deg == -1) deg = n;
        assert(deg > 0);
        F res{(*this)[0].inv()};
        while(int(res.size()) < deg) {
            int m = res.size();
            F f((*this).begin(), (*this).begin() + std::min(n, m * 2)), r(res);
            f.resize(m * 2), atcoder::internal::butterfly(f);
            r.resize(m * 2), atcoder::internal::butterfly(r);
            for(int i = 0; i < m * 2; ++i) f[i] *= r[i];
            atcoder::internal::butterfly_inv(f);
            f.erase(f.begin(), f.begin() + m);
            f.resize(m * 2), atcoder::internal::butterfly(f);
            for(int i = 0; i < m * 2; ++i) f[i] *= r[i];
            atcoder::internal::butterfly_inv(f);
            T iz = T(m * 2).inv();
            iz *= -iz;
            for(int i = 0; i < m; ++i) f[i] *= iz;
            res.insert(res.end(), f.begin(), f.begin() + m);
        }
        res.resize(deg);
        return res;
    }

    //O(N)
    F &diff_inplace() {
        int n = (*this).size();
        for(int i = 1; i < n; ++i) (*this)[i - 1] = (*this)[i] * i;
        (*this)[n - 1] = 0;
        return *this;
    }
    F diff() const { F(*this).diff_inplace(); }

    //O(N)
    F &integral_inplace() {
        int n = (*this).size(), mod = T::mod();
        std::vector<T> inv(n);
        {
            inv[1] = 1;
            for(int i = 2; i < n; ++i)
                inv[i] = T(mod) - inv[mod % i] * (mod / i);
        }
        for(int i = n - 2; i >= 0; --i) (*this)[i + 1] = (*this)[i] * inv[i + 1];
        (*this)[0] = 0;
        return *this;
    }
    F integral() const { return F(*this).integral_inplace(); }

    //O(NlogN)
    F &log_inplace() {
        int n = (*this).size();
        assert(n and (*this)[0] == 1);
        F f_inv = (*this).inv();
        (*this).diff_inplace();
        (*this) *= f_inv;
        (*this).integral_inplace();
        return *this;
    }
    F log() const { return F(*this).log_inplace(); }

    //O(NlogN)
    F &deriv_inplace() {
        int n = (*this).size();
        assert(n);
        for(int i = 2; i < n; ++i) (*this)[i] *= i;
        (*this).erase((*this).begin());
        (*this).push_back(0);
        return *this;
    }
    F deriv() const { return F(*this).deriv_inplace(); }

    //O(NlogN)
    F &exp_inplace() {
        int n = (*this).size();
        assert(n and (*this)[0] == 0);
        F g{1};
        (*this)[0] = 1;
        F h_drv((*this).deriv());
        for(int m = 1; m < n; m *= 2) {
            F f((*this).begin(), (*this).begin() + m);
            f.resize(2 * m), atcoder::internal::butterfly(f);
            auto mult_f = [&](F &p) {
                p.resize(2 * m);
                atcoder::internal::butterfly(p);
                for(int i = 0; i < 2 * m; ++i) p[i] *= f[i];
                atcoder::internal::butterfly_inv(p);
                p /= 2 * m;
            };
            if(m > 1) {
                F g_(g);
                g_.resize(2 * m), atcoder::internal::butterfly(g_);
                for(int i = 0; i < 2 * m; ++i) g_[i] *= g_[i] * f[i];
                atcoder::internal::butterfly_inv(g_);
                T iz = T(-2 * m).inv();
                g_ *= iz;
                g.insert(g.end(), g_.begin() + m / 2, g_.begin() + m);
            }
            F t((*this).begin(), (*this).begin() + m);
            t.deriv_inplace();
            {
                F r{h_drv.begin(), h_drv.begin() + m - 1};
                mult_f(r);
                for(int i = 0; i < m; ++i) t[i] -= r[i] + r[m + i];
            }
            t.insert(t.begin(), t.back());
            t.pop_back();
            t *= g;
            F v((*this).begin() + m, (*this).begin() + std::min(n, 2 * m));
            v.resize(m);
            t.insert(t.begin(), m - 1, 0);
            t.push_back(0);
            t.integral_inplace();
            for(int i = 0; i < m; ++i) v[i] -= t[m + i];
            mult_f(v);
            for(int i = 0; i < std::min(n - m, m); ++i)
                (*this)[m + i] = v[i];
        }
        return *this;
    }
    F exp() const { return F(*this).exp_inplace(); }

    //O(NlogN)
    F &pow_inplace(long long k) {
        int n = (*this).size(), l = 0;
        assert(k >= 0);
        if(!k) {
            for(int i = 0; i < n; ++i) (*this)[i] = !i;
            return *this;
        }
        while(l < n and (*this)[l] == 0) ++l;
        if(l > (n - 1) / k or l == n) return *this = F(n);
        T c = (*this)[l];
        (*this).erase((*this).begin(), (*this).begin() + l);
        (*this) /= c;
        (*this).log_inplace();
        (*this).resize(n - l * k);
        (*this) *= k;
        (*this).exp_inplace();
        (*this) *= c.pow(k);
        (*this).insert((*this).begin(), l * k, 0);
        return *this;
    }
    F pow(const long long k) const { return F(*this).pow_inplace(k); }

    //O(NlogN)
    F sqrt(int deg = -1) const {
        auto SQRT = [&](T t) {
            int mod = T::mod();
            if(t == 0 or t == 1) return t;
            int v = (mod - 1) / 2;
            if(t.pow(v) != 1) return T(-1);
            int q = mod - 1, m = 0;
            while(~q & 1) q >>= 1, m++;
            std::mt19937 mt;
            T z = mt();
            while(z.pow(v) != mod - 1) z = mt();
            T c = z.pow(q), u = t.pow(q), r = t.pow((q + 1) / 2);
            for(; m > 1; m--) {
                T tmp = u.pow(1 << (m - 2));
                if(tmp != 1) r = r * c, u = u * c * c;
                c = c * c;
            }
            return T(std::min(r.val(), mod - r.val()));
        };
        int n = (*this).size();
        if(deg == -1) deg = n;
        if((*this)[0] == 0) {
            for(int i = 1; i < n; i++) {
                if((*this)[i] != 0) {
                    if(i & 1) return F(0);
                    if(deg - i / 2 <= 0) break;
                    auto ret = (*this);
                    ret >>= i;
                    ret.resize(n - i);
                    ret = ret.sqrt(deg - i / 2);
                    if(ret.empty()) return F(0);
                    ret <<= (i / 2);
                    ret.resize(deg);
                    return ret;
                }
            }
            return F(deg);
        }
        auto sqr = SQRT((*this)[0]);
        if(sqr * sqr != (*this)[0]) return F(0);
        F ret{sqr};
        T ti = T(1) / T(2);
        for(int i = 1; i < deg; i <<= 1) {
            auto u = (*this);
            u.resize(i << 1);
            ret = (ret.inv(i << 1) * u + ret) * ti;
        }
        ret.resize(deg);
        return ret;
    }

    void sparse_pow(const int n, const int d, const T c, const int k);
    void sparse_pow_inv(const int n, const int d, const T c, const int k);
    void stirling_first(int n);
    void stirling_second(int n);
    std::vector<T> multipoint_evaluation(const std::vector<T> &p);

    void print(int n) {
        rep(i, n) {
            cout << (*this)[i];
            if (i == n-1) {
                cout << '\n';
            } else {
                cout << ' ';
            }
        }
    }
};
#pragma endregion

// print for acl-modint
std::ostream &operator<<(std::ostream &os, const atcoder::modint998244353 &a) { return os << a.val(); }
std::ostream &operator<<(std::ostream &os, const atcoder::modint1000000007 &a) { return os << a.val(); }
template <int m> std::ostream &operator<<(std::ostream &os, const atcoder::static_modint<m> &a) { return os << a.val(); }
template <int m> std::ostream &operator<<(std::ostream &os, const atcoder::dynamic_modint<m> &a) { return os << a.val(); }

void solve() {
    ll N, M, Q;
    cin >> N >> M >> Q;
    FormalPowerSeries<atcoder::modint998244353> fc(N);
    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        fc[l]++;
    }
    FormalPowerSeries<atcoder::modint998244353> fa(N);
    rep(i, N) {
        ll a;
        cin >> a;
        fa[i] = a;
    }
    // 分母の後ろの方に係数0の項があるとエラーになるので余計な項を除いておく
    while (fc.back() == 0) fc.pop_back();
    auto fb = fa / fc;
    fb.print(M);
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
