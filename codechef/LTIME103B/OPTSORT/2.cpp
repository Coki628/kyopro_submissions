/*
参考：https://twitter.com/butsurizuki/status/1474796089597644801
・TLで解法見てたら割と考え方は離れてないぽかったのでupsolveした。
・セグ木、区間set
・mn,mxについて、重なる区間はまとめたいし、離れていたら分けたい、
　っていうお気持ちは合ってて、たださっきのやつだと、
　重ならないけど接してるような区間はマージされてしまう。
　今回の設定だと、重なるだけのやつは分けた方が得になる。
　なので区間setに詰める時には1短くして、
　最終的に区間長数える時に1長く戻して帳尻合わせる、ってやったらAC。
・区間setが、今残ってる区間がどういう状態かを見れる形で
　保持してくれているのが分かったので、それは収穫だったかな。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

// 閉区間の範囲を管理
template<typename T>
struct RangeSet {
    set<pair<T,T>> st;
    T TINF;
 
    RangeSet() {
        TINF=numeric_limits<T>::max()/2;
        st.emplace(TINF,TINF);
        st.emplace(-TINF,-TINF);
    }
    // [l,r] covered?
    bool covered(T l,T r) {
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        return ite->first<=l and r<=ite->second;
    }
    bool covered(T x) {
        return covered(x,x);
    }
    // [l, r]がカバーされているなら，その区間を返す. されていないなら[-TINF,-TINF]を返す
    pair<T,T> covered_by(T l,T r) {
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        if (ite->first<=l and r<=ite->second) return *ite;
        return make_pair(-TINF,-TINF);
    }
    pair<T,T> covered_by(T x) {
        return covered_by(x,x);
    }
    // insert[l,r], 増加量を返す
    T insert(T l,T r) {
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        if (ite->first<=l and r<=ite->second) return T(0);
        T sum_erased=T(0);
        if (ite->first<=l and l<=ite->second+1) {
            l=ite->first;
            sum_erased+=ite->second-ite->first+1;
            ite=st.erase(ite);
        } else ite=next(ite);
        while (r>ite->second) {
            sum_erased+=ite->second-ite->first+1;
            ite=st.erase(ite);
        }
        if (ite->first-1<=r and r<=ite->second) {
            sum_erased+=ite->second-ite->first+1;
            r=ite->second;
            st.erase(ite);
        }
        st.emplace(l,r);
        return r-l+1-sum_erased;
    }
    T insert(T x) {
        return insert(x,x);
    }
    // erase [l,r], 減少量を返す
    T erase(T l,T r) {
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        if (ite->first<=l and r<=ite->second) {
            // 完全に1つの区間に包含されている
            if (ite->first<l)  st.emplace(ite->first,l-1);
            if (r<ite->second) st.emplace(r+1,ite->second);
            st.erase(ite);
            return r-l+1;
        }
 
        T ret=T(0);
        if (ite->first<=l and l<=ite->second) {
            ret+=ite->second-l+1;// 消えた
            if (ite->first<l) st.emplace(ite->first,l-1);
            ite=st.erase(ite);// 次へ
        } else ite=next(ite);
        while (ite->second<=r) {
            ret+=ite->second-ite->first+1;
            ite=st.erase(ite);
        }
        // 右端が区間の間にあるか
        if (ite->first<=r and r<=ite->second) {
            ret+=r-ite->first+1;
            if (r<ite->second) st.emplace(r+1,ite->second);
            st.erase(ite);
        }
        return ret;
    }
    T erase(T x) {
        return erase(x,x);
    }
    // number of range
    int size() {
        return (int)st.size()-2;
    }
    // mex [x,~)
    T mex(T x=0) {
        auto ite=prev(st.lower_bound({x+1,x+1}));
        if (ite->first<=x and x<=ite->second) return ite->second+1;
        else return x;
    }
    void output() {
        cout<<"RangeSet : ";
        for(auto &p:st) {
            if (p.first==-TINF or p.second==TINF) continue;
            cout<<"["<<p.first<<", "<<p.second<<"] ";
        }
        cout<<"\n";
    }

    vector<pair<T, T>> get_ranges() {
        vector<pair<T, T>> res;
        for (auto& [l, r] : st) {
            if (l == -TINF or r == TINF) continue;
            res.emplace_back(l, r);
        }
        return res;
    }
};

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    auto segmn = get_segment_tree([](ll a, ll b) { return min(a, b); }, INF);
    auto segmx = get_segment_tree([](ll a, ll b) { return max(a, b); }, -INF);
    segmn.build(A);
    segmx.build(A);
    RangeSet<ll> rs;
    rep(i, N) {
        ll mx = segmx.query(0, i);
        if (mx > A[i]) {
            ll j = segmx.find_first(0, [&](ll x) { return x >= mx; });
            ll mn = segmn.query(j, i+1);
            rs.insert(mn, mx-1);
        }
    }

    ll ans = 0;
    for (auto [l, r] : rs.get_ranges()) {
        ans += r-l+1;
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
