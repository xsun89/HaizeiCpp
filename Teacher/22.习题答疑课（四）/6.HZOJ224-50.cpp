#include <cstdio>

long long nums[100001], seg[400004], plus[400004], times[400004], m, n, mod;

void update(long long idx) {
    seg[idx] = (seg[idx << 1] + seg[idx << 1 | 1]) % mod;
}

void mul_down(long long idx, long long p, long long r) {
    if (times[idx] == 1) return ;
    long long val = times[idx];
    seg[idx << 1] *= val;
    seg[idx << 1] %= mod;
    seg[idx << 1 | 1] *= val;
    seg[idx << 1 | 1] %= mod;
    times[idx << 1] *= val;
    times[idx << 1] %= mod;
    times[idx << 1 | 1] *= val;
    times[idx << 1 | 1] %= mod;
    plus[idx << 1] *= val;
    plus[idx << 1] %= mod;
    plus[idx << 1 | 1] *= val;
    plus[idx << 1 | 1] %= mod;
    times[idx] = 1;
    return ;
}

void add_down(long long idx, long long p, long long r) {
    if (plus[idx] == 0) return ;
    long long mid = (p + r) >> 1;
    long long val = plus[idx];
    seg[idx << 1] += val * (mid - p + 1);
    seg[idx << 1] %= mod;
    seg[idx << 1 | 1] += val * (r - mid);
    seg[idx << 1 | 1] %= mod;
    plus[idx << 1] += val;
    plus[idx << 1] %= mod;
    plus[idx << 1 | 1] += val;
    plus[idx << 1 | 1] %= mod;
    plus[idx] = 0;
    return ;
} 

void down(long long idx, long long p, long long r) {
    long long q = (p + r) >> 1;
    mul_down(idx, p, r);
    add_down(idx, p, r);
    return ;
}

void build(long long idx, long long p, long long r) {
	plus[idx] = 0;
	times[idx] = 1;
	if(p == r) {
	    seg[idx] = nums[p];
		return ;
	}
	long long q = (p + r) >> 1;
	build(idx << 1, p, q);
	build(idx << 1 | 1, q + 1, r);
	update(idx);
    return ;
}

void modify(long long idx, long long p, long long r, long long x, long long y, long long z, long long flag) {
	if(x <= p && r <= y) {
		if(flag == 2) {
		    seg[idx] = (seg[idx] + z * (r - p + 1)) % mod;
			plus[idx] = (plus[idx] + z) % mod;
		} else {
		    seg[idx] = seg[idx] * z % mod;
			plus[idx] = plus[idx] * z % mod;
			times[idx] = times[idx] * z % mod;
		}
		return;
	}
	down(idx, p, r);
	long long q = (p + r) >> 1;
	if(x <= q) {
	    modify(idx << 1, p, q, x, y, z, flag);
	}
	if(y > q) {
	    modify(idx << 1 | 1, q + 1, r, x, y, z, flag);
	}
	update(idx);
    return ;
}

long long query(long long idx, long long p, long long r, long long x, long long y) {
	if(x <= p && r <= y) return seg[idx];
	down(idx, p, r);
	long long q = (p + r) >> 1;
	long long sum = 0;
	if(x <= q) {
		sum += query(idx << 1, p, q, x, y);
	}
    sum %= mod;
	if(y > q) {
	    sum += query(idx << 1 | 1, q + 1, r, x, y);
	}
    sum %= mod;
	return sum;
}

int main() {
	scanf("%lld%lld%lld", &m, &n, &mod);
	for(long long i = 1; i <= m; ++i) {
	    scanf("%lld", nums + i);
	}
	build(1, 1, m);
	
	for(long long i = 0; i < n; ++i) {
	    long long a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		if(a == 3) {
		    printf("%lld\n", query(1, 1, m, b, c) % mod);
		} else {
		    long long d;
			scanf("%lld", &d);
			modify(1, 1, m, b, c, d, a);
		}
	}
	return 0;
}
