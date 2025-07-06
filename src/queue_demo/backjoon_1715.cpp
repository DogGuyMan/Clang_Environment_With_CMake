#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define FASTIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

priority_queue<long long, vector<long long>, greater<long long>> pq;

int N;
int main() {
    FASTIO;
    cin >> N;
    if(N <= 1) {
        cout << 0 << '\n'; return 0;
    }

    for(int i = 0 ; i < N; i++) {
        long long c;
        cin >> c;
        pq.push(c);
    }


    long long res = 0;
    while(pq.size() > 1) {
        long long f = pq.top(); pq.pop();
        long long s = pq.top(); pq.pop();
        // cout << "+ (" << f << " + " << s << ")" << '\n';
        res += (f + s);
        pq.push(f + s);
    }
    cout << res << '\n';
    return 0;
}
