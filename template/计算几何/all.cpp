#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = long double;
const db eps = 1e-10;

inline int add(int a, int b, int p) {
    return a += b, a >= p ? a - p : a;
}

inline db sgn(db x) {
    return x < -eps ? -1 : x > eps;
}
struct vec2 {
    db x, y;
    inline vec2() { }
    inline vec2(db a, db b) : x(a), y(b) { }
    inline db norm() const {
        return x * x + y * y;
    }
    inline db abs() const {
        return std::sqrt(x * x + y * y);
    }
};
inline vec2 operator + (const vec2 & x, const vec2 & y) {
    return vec2(x.x + y.x, x.y + y.y);
}
inline vec2 operator - (const vec2 & x, const vec2 & y) {
    return vec2(x.x - y.x, x.y - y.y);
}
inline vec2 operator / (const vec2 & x, db y) {
    return vec2(x.x / y, x.y / y);
}
inline db operator * (const vec2 & x, const vec2 & y) {
    return x.x * y.y - x.y * y.x;
}
inline vec2 operator * (const db & x, const vec2 & y) {
    return vec2(x * y.x, x * y.y);
}
inline vec2 operator * (const vec2 & y, const db & x) {
    return vec2(x * y.x, x * y.y);
}
inline db operator % (const vec2 & x, const vec2 & y) {
    return x.x * y.x + x.y * y.y;
}
inline db dist(const vec2 & x, const vec2 & y) {
    return (x - y).abs();
}

// 逆时针极角排序
inline int half(const vec2 & x) {
    return x.y < 0 || (x.y == 0 && x.x <= 0);
}
inline bool cmp(const vec2 & A, const vec2 & B) {
    if(half(A) != half(B)) return half(B);
    return A * B > 0;
}
bool cmp_eq(vec2 A, vec2 B) {
	return half(A) == half(B) && A * B == 0;
}
// 判断 A, B, C 三个向量是否是逆时针顺序
// 如果是，返回 1
// 如果 (A, B), (C, B) 同方向共线，返回 -1
// 如果是顺时针，返回 0
bool cmp_ct(vec2 A, vec2 B, vec2 C) {
	if(cmp_eq(A, B)) return -1;
	if(cmp_eq(C, B)) return -1;
	if(cmp(A, B)) {
		return cmp(B, C) || cmp(C, A);
	} else {
		return cmp(B, C) && cmp(C, A);
	}
}


bool eql(db x, db y) {
	return fabs(x - y) < eps;
}
db cross(vec2 x, vec2 y, vec2 z) {
	return (y.x - x.x) * (z.y - x.y) - (y.y - x.y) * (z.x - x.x);
}
std::vector<vec2> gethull(std::vector<vec2> o) {
	iter_swap(o.begin(), min_element(o.begin(), o.end(), [](vec2 x, vec2 y) {
		return eql(x.x, y.x) ? x.y < y.y : x.x < y.x;
	}));
	sort(o.begin() + 1, o.end(), [&](vec2 x, vec2 y) {
		db c = cross(o[0], x, y);
		if(fabs(c) > eps) {
			return c > 0;
		}
		return (x - o[0]).norm() < (y - o[0]).norm();
	});
	std::vector<vec2> stack;
	for(vec2 x : o) {
		for(;stack.size() >= 2 && cross(stack.rbegin()[1], stack.back(), x) <= eps;) {
			stack.pop_back();
		}
		stack.push_back(x);
	}
	for(;stack.size() > 2 && cross(stack.rbegin()[1], stack.back(), o[0]) <= eps;) {
		stack.pop_back();
	}
	return stack;
}

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
inline vec2 operator & (const line & x, const line & y) {
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


bool paraS(line a, line b) {
	return is_para(a, b) && vec2(a) % vec2(b) > 0;
}
std::vector<vec2> HalfPlaneI(std::vector<line> vs) {
    auto cmp = [](line a, line b) {
        if(paraS(a, b)) {
            return dist(a) < dist(b);
        }
        return ::cmp(vec2(a), vec2(b));
    };
    sort(vs.begin(), vs.end(), cmp);
    int ah = 0, at = 0, n = size(vs);
    std::vector<line> deq(n + 1);
    std::vector<vec2> ans(n);
    deq[0] = vs[0];
    for(int i = 1;i <= n;++i) {
        line o = i < n ? vs[i] : deq[ah];
        if(paraS(vs[i - 1], o)) {
            continue;
        }
        for(;ah < at && check(deq[at - 1], deq[at], o) < 0;) -- at;
        if(i != n)
        for(;ah < at && check(deq[ah], deq[ah + 1], o) < 0;) ++ ah;
        if(!is_para(o, deq[at])) {
            ans[at] = o & deq[at];
            deq[++at] = o;
        }
    }
    if(at - ah <= 2) return {};
    return {ans.begin() + ah, ans.begin() + at};
}
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


int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
}
