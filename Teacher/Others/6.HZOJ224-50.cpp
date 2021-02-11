#include <cstdio>

int nums[100001], seg[400004], plus[400004], times[400004], m, n, mod;

void update(int idx) {
    seg[idx] = (seg[idx << 1] + seg[idx << 1 | 1]) % mod;
}

void down(int idx, int p, int r) {
    int q = p + r >> 1;
	seg[idx << 1] = (seg[idx << 1] * times[idx] + (q - p + 1) * plus[idx]) % mod;
	times[idx << 1] = times[idx << 1] * times[idx] % mod;
	plus[idx << 1] = (plus[idx << 1] * times[idx] + plus[idx]) % mod;
	
	seg[idx << 1 | 1] = (seg[idx << 1 | 1] * times[idx] + (r - q) * plus[idx]) % mod;
	times[idx << 1 | 1] = times[idx << 1 | 1] * times[idx] % mod;
	plus[idx << 1 | 1] = (plus[idx << 1 | 1] * times[idx] + plus[idx]) % mod;
	
	times[idx] = 1;
	plus[idx] = 0;
}

void build(int idx, int p, int r) {
	if(p == r) {
	    seg[idx] = nums[p];
		return;
	}
	int q = p + r >> 1;
	build(idx << 1, p, q);
	build(idx << 1 | 1, q + 1, r);
	update(idx);
	plus[idx] = 0;
	times[idx] = 1;
}

void modify(int idx, int p, int r, int x, int y, long long z, int flag) {
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
	
	int q = p + r >> 1;
	if(x <= q) {
	    modify(idx << 1, p, q, x, y, z, flag);
	}
	if(y > q) {
	    modify(idx << 1 | 1, q + 1, r, x, y, z, flag);
	}
	update(idx);
}

long long query(int idx, int p, int r, int x, int y) {
	if(x <= p && r <= y) return seg[idx];
	down(idx, p, r);
	int q = p + r >> 1;
	long long sum = 0;
	if(x <= q) {
		sum += query(idx << 1, p, q, x, y);
	}
	if(y > q) {
	    sum += query(idx << 1 | 1, q + 1, r, x, y);
	}
	return sum;
}

int main() {
	scanf("%d%d%d", &m, &n, &mod);
	for(int i = 1; i <= m; ++i) {
	    scanf("%d", nums + i);
	}
	build(1, 1, m);
	
	for(int i = 0; i < n; ++i) {
	    int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if(a == 3) {
		    printf("%d\n", query(1, 1, m, b, c) % mod);
		} else {
		    int d;
			scanf("%d", &d);
			modify(1, 1, m, b, c, d, a);
		}
	}
	return 0;
}
