struct line {
    db a, b, c;
    // a * x + b * y + c (= or >) 0
	line() {}
    inline line(db A, db B, db C) : a(A), b(B), c(C) {}
    inline line(const vec2 & x, const vec2 & y) : a(x.y - y.y), b(y.x - x.x), c(x * y) { }
    // 左侧 > 0
    inline db operator ()(const vec2 & x) const { return a * x.x + b * x.y + c; }
    inline line perp() const { return line(b, -a, 0); }
    inline line para(const vec2 & o) { return line(a, b, c - (*this)(o)); }
	explicit operator vec2() const {
		return vec2(a, b);
	}
    inline db norm() const { return vec2(*this).norm(); }
};
inline vec2 operator & (const line & x, const line & y) { // 注意精度
    return vec2(vec2(x.c, x.b) * vec2(y.c, y.b), vec2(x.a, x.c) * vec2(y.a, y.c)) / -(vec2(x.a, x.b) * vec2(y.a, y.b));
}
inline vec2 proj(const vec2 & x, const line & l) {
    return x - vec2(l) * (l(x) / l.norm());
}
inline vec2 refl(const vec2 & x, const line & l) {
    return x - vec2(l) * (l(x) / l.norm()) * 2;
}
inline db dist(const line & l, const vec2 & x = vec2(0, 0)) { // with sign
	return l(x) / std::sqrt(l.norm());
}
inline bool is_para(const line & x, const line & y) {
    return std::fabs(vec2(x) * vec2(y)) < eps;
}
inline bool is_perp(const line & x, const line & y) {
    return std::fabs(vec2(x) % vec2(y)) < eps;
}
inline bool online(const vec2 & x, const line & l) {
    return std::fabs(l(x)) < eps;
}
inline int ccw(vec2 a, vec2 b, vec2 c) {
    int sign = sgn((b - a) * (c - a));
    if(sign == 0) {
        if(sgn((b - a) % (c - a)) == -1) return 2;
        if((c - a).norm() > (b - a).norm() + eps) return -2;
    }
    return sign;
}

// 三条直线关系
db det(line a, line b, line c) {
    vec2 A = vec2(a), B = vec2(b), C = vec2(c);
    return c.c * (A * B) + a.c * (B * C) + b.c * (C * A);
}
db check(line a, line b, line c) { // sgn same as c(a & b), 0 if error
    return sgn(det(a, b, c)) * sgn(vec2(a) * vec2(b));
}


