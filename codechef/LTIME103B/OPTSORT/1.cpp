/*
・部分点。
・セグ木、区間set
・なんかshojinさんが通してたの見て、頑張って粘ったら部分点取れた。
　ソートする範囲にあるmn,mxを考えた時、そこが重なるようなら結局まとめた方がいい。
　っていう方針でセグ木と区間setぶん回したらなんか部分点1,3は取れた。
　全部WAなら分かるんだけど、2だけ落ちてるのが逆に分からない。
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
            rs.insert(mn, mx);
        }
    }

    ll ans = 0;
    for (auto [l, r] : rs.st) {
        if (l == -rs.TINF or r == rs.TINF) continue;
        ans += r-l;
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
