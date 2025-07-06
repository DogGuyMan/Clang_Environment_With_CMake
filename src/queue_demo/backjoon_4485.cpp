#include <iostream>
#include <queue>
#include <vector>
#define Y first
#define X second
using namespace std;

int N = 0;

struct HEAP {
    int dist;
    int x;
    int y;

    bool operator < (const HEAP &a) const {
        return dist > a.dist;
    }
};

int MV[4][2] {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
};


vector<vector<int>> M(125, vector<int>(125, 123456789));
vector<vector<int>> DIST(125, vector<int>(125, 123456789));

bool IsBound(int SZ, int x, int y) {
    bool xBound = 0 <= x && x < SZ;
    bool yBound = 0 <= y && y < SZ;
    return xBound && yBound;
}

void Clear(int SZ) {
    for(int i = 0; i < SZ; i++) {
        for(int j = 0; j < SZ; j++) {
            M[i][j] = 123456789;
            DIST[i][j] = 123456789;
        }
    }
}

int solve(int pcount) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> M[i][j];
        }
    }
    priority_queue<HEAP> PQ;
    DIST[0][0] = M[0][0];
    PQ.push({M[0][0], 0 ,0});

    while(!PQ.empty()) {
        HEAP top = PQ.top(); PQ.pop();
        if(top.x == N-1 && top.y == N-1) break;
        for(int i = 0; i < 4; i++) {
            int nxt_x = top.x + MV[i][1], nxt_y = top.y + MV[i][0];
            if(IsBound(N, nxt_x, nxt_y)) {
                int newDist = top.dist + M[nxt_y][nxt_x];
                if(DIST[nxt_y][nxt_x] > newDist) {
                    DIST[nxt_y][nxt_x] = newDist;
                    PQ.push({newDist, nxt_x, nxt_y});
                }
            }
        }
    }
    cout << "Problem " << pcount << ": " << DIST[N-1][N-1] << '\n';
    Clear(N);
    return 0;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int pcount = 0;
    while(true) {
        cin >> N;
        if(N == 0) break;
        solve(++pcount);
    }
    return 0;
}
