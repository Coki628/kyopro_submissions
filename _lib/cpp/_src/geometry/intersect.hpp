#include "Segment.hpp"
#include "ccw.hpp"

// 線分seg1と線分seg2の交差判定
template<typename T>
bool intersect(Segment<T> seg1, Segment<T> seg2) {
    return (
        ccw(seg1.p1, seg1.p2, seg2.p1) * ccw(seg1.p1, seg1.p2, seg2.p2) <= 0 and
        ccw(seg2.p1, seg2.p2, seg1.p1) * ccw(seg2.p1, seg2.p2, seg1.p2) <= 0
    );
}
