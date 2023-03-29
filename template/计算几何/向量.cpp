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


// 凸包 DP
struct pr { 
	int i, j;
	vec2 get() const {
		return a[j] - a[i];
	}
};
bool cmpseg(pr x, pr y) {
	vec2 A = x.get(), B = y.get();
	if(!cmp(A, B) && !cmp(B, A)) {
		return a[x.i] % A < a[y.i] % A;
	}
	return cmp(A, B);
}

