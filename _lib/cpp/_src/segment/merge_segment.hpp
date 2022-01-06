#include "../macros.hpp"

// 2つの閉区間seg1[l,r],seg2[l,r]から、重複を除いた長さを返す
ll merge_segment(pll seg1, pll seg2) {
    auto& [l1, r1] = seg1;
    auto& [l2, r2] = seg2;
    if (l1 > l2) {
        swap(l1, l2);
        swap(r1, r2);
    }
    ll ln1 = r1-l1+1;
    ll ln2 = r2-l2+1;
    if (ln1 <= 0 and ln2 <= 0) {
        return 0;
    } elif (ln2 <= 0 or l2 <= r1 and r2 <= r1) {
        return ln1;
    } elif (l2 <= r1 and r2 > r1) {
        return ln1 + ln2 - (r1-l2+1);
    } else {
        return ln1 + ln2;
    }
}
