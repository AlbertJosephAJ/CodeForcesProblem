#include<bits/stdc++.h>
#define mod 100000007
#define inf 1e9
#define ll long long int
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL)
using namespace std;

class SegmentTree {
public:
	vector<ll> seg;
	SegmentTree(ll n) {
		this->seg.resize(4 * n + 1);
	}

	void build(int ind, int l, int r, vector<ll> &arr, bool flag) {
		if(l == r) {
			seg[ind] = arr[l];
			return;
		}
		int mid = l + (r - l) / 2;
		build(2 * ind + 1, l, mid, arr, !flag);
		build(2 * ind + 2, mid + 1, r, arr, !flag);
		
		if(flag) {
			seg[ind] = (seg[2 * ind + 1] ^ seg[2 * ind + 2]);
		} else {
			seg[ind] = (seg[2 * ind + 1] | seg[2 * ind + 2]);
		}
	}

	void update(int ind, int l, int r, int pos, int val, vector<ll> &arr, bool flag) {
		if(l == r) {
			seg[ind] = val;
			return;
		}

		int mid = l + (r - l) / 2;

		if(pos <= mid) update(2 * ind + 1, l, mid, pos, val, arr, !flag);
		else update(2 * ind + 2, mid + 1, r, pos, val, arr, !flag);

		if(flag) {
			seg[ind] = (seg[2 * ind + 1] ^ seg[2 * ind + 2]);
		} else {
			seg[ind] = (seg[2 * ind + 1] | seg[2 * ind + 2]);
		}
	}

	int query() {
		return seg[0];
	}
};

void solve() {
	int n, m;
	cin >> n >> m;
	ll size = pow(2, n);
	vector<ll> arr(size);
	for(int i = 0; i < size; i++) cin >> arr[i];

	SegmentTree s(size);
	if(n % 2 == 0) s.build(0, 0, size - 1, arr, true);
	else s.build(0, 0, size - 1, arr, false);

	while(m--) {
		int pos, val;
		cin >> pos >> val;
		if(n % 2 == 0) s.update(0, 0, size - 1, pos - 1, val, arr, true);
		else s.update(0, 0, size - 1, pos - 1, val, arr, false);

		cout << s.query() << endl;
	}
}

int main() {
	fast_io;
	#ifndef ONLINE_JUDGE
		//for getting Input from input.txt
		freopen("input1.txt", "r", stdin);
		//for writing Output from output.txt
		freopen("output1.txt", "w", stdout);
	#endif

	solve();
}