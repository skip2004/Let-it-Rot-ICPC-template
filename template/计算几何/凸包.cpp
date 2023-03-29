
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

