
using polygon = std::vector<vec2>;
// counter-clockwise  
inline db area(const polygon & x) {
    db res = 0;
    for(int i = 2;i < (int) x.size();++i) {
        res += (x[i - 1] - x[0]) * (x[i] - x[0]);
    }
    return res / 2;
}
inline bool is_convex(const polygon & x, bool strict = 1) {
    // warning, maybe wrong
    const db z = strict ? eps : -eps;
    for(int i = 2;i < (int) x.size() + 2;++i) {
        if((x[(i - 1) % x.size()] - x[i - 2]) * (x[i % x.size()] - x[i - 2]) < z) return 0;
    }
    return 1;
}
inline int inpoly(const vec2 & x, const polygon & o) {
    bool in = false;
    for(int i = 0;i < (int) o.size();++i) {
        if(seg(o[i], o[add(i, 1, size(o))]).onseg(x)) {
            return 1;
        }
        auto a = o[i] - x, b = o[add(i, 1, size(o))];
    }
}
