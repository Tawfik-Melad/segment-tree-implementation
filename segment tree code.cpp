#define _CRT_SECURE_NO_DEPRECATE
#include <bits/stdc++.h>
#include <unordered_map>
#define ll long long
#define all(v) v.begin(),v.end()
#define sz(x) (ll)(x.size())
#define endl '\n'
#define Mask bitset<40>
using namespace std;
void fast() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
}

vector<ll>segTree, lazy;

bool is_power_of_two(ll n) {

    return !(n & (n - 1));
}

void propagation(ll ind, ll l, ll r) {

    if (lazy[ind]) {

        segTree[ind] += (r - l + 1) * lazy[ind];
        if (l != r) {
            lazy[2 * ind] += lazy[ind];
            lazy[2 * ind + 1] += lazy[ind];
        }
        lazy[ind] = 0;
    }
}

ll merge(ll left, ll right) {

    return left + right;
}

void build(vector<ll>& v) {

    ll n = sz(v);
    while (!is_power_of_two(n)) {
        n++;
        v.push_back(0);
    }
    segTree = lazy = vector<ll>(2 * n);
    for (ll i = 0; i < n; i++) {
        segTree[n + i] = v[i];
    }
    for (ll i = n - 1; i > 0; i--) {
        segTree[i] = merge(segTree[2 * i], segTree[2 * i + 1]);
    }

}

void update(ll s, ll e, ll ind, const ll query_low, const ll query_high, const ll value) {
    propagation(ind, s, e);

    if (s > query_high || e < query_low)
        return;

    if (s >= query_low && e <= query_high)
    {
        segTree[ind] += (e - s + 1) * value;
        if (s != e) {
            lazy[2 * ind] += value;
            lazy[2 * ind + 1] += value;
        }
        return;
    }
    update(s, (s + e) / 2, 2 * ind, query_low, query_high, value);
    update((s + e) / 2 + 1, e, 2 * ind + 1, query_low, query_high, value);
    segTree[ind] = merge(segTree[2 * ind], segTree[2 * ind + 1]);
}

ll query(ll s, ll e, ll ind, const ll query_low, const ll query_high) {

    if (s > query_high || e < query_low)
        return 0; // value dosnt change the restult (be careful)

    propagation(ind, s, e);

    if (s >= query_low && e <= query_high)
        return segTree[ind];

    ll left = query(s, (s + e) / 2, 2 * ind, query_low, query_high);
    ll right = query((s + e) / 2 + 1, e, 2 * ind + 1, query_low, query_high);
    return merge(left, right);
}


int main() {

    fast();

    ll tt; cin >> tt;
    while (tt--) {

        ll n; cin >> n;
        vector<ll>v(n);
        for (auto& i : v)
            cin >> i;


        build(v);
        n = sz(v);

        ll q; cin >> q;
        while (q--) {

            ll type; cin >> type;
            ll l, r; cin >> l >> r;
            if (type == 1) {
                cout << query(1, n, 1, l, r) << endl;
            }
            else {
                ll val; cin >> val;
                update(1, n, 1, l, r, val);
            }


        }
    }


    return 0;
}