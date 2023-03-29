struct seg {
    vec2 x, y;
    inline seg() {}
    inline seg(const vec2 & A, const vec2 & B) : x(A), y(B) {}
    inline bool onseg(const vec2 & o) const {
        return (o - x) % (o - y) < eps && std::fabs((o - x) * (o - y)) < eps;
    }
    inline line to_l() const {
        return line(x, y);
    }
};
inline bool is_isc(const seg & x, const seg & y) {
    return
        ccw(x.x, x.y, y.x) * ccw(x.x, x.y, y.y) <= eps &&
        ccw(y.x, y.y, x.x) * ccw(y.x, y.y, x.y) <= eps;
}
inline db dist(const seg & o, const vec2 & x) {
    vec2 z = proj(x, o.to_l());
    if(o.onseg(z)) {
        return dist(x, z);
    } else {
        return std::min(dist(o.x, x), dist(o.y, x));
    }
}
inline db dist(const seg & x, const seg & y) {
    if(is_isc(x, y)) return 0;
    return std::min({ dist(y, x.x), dist(y, x.y), dist(x, y.x), dist(x, y.y), });
}
