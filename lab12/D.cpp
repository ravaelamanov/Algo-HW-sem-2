#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

ifstream fin("circulation.in");
ofstream fout("circulation.out");

class Edge {
public:
    int to, capacity, flow, rev;
    bool exists;

    Edge(int to, int flow, int capacity, int rev, bool exists) {
        this->to = to;
        this->capacity = capacity;
        this->flow = flow;
        this->rev = rev;
        this->exists = exists;
    }
};

int pushflow(vector<Edge> graph[], int u, int flow, int t, int level[]) {
    if (u == t) return flow;
    for (int i = 0; i < graph[u].size(); i++) {
        Edge &e = graph[u][i];
        if (level[e.to] == level[u] + 1 && e.flow < e.capacity) {
            int curFlow = min(flow, e.capacity - e.flow);
            int tempFlow = pushflow(graph, e.to, curFlow, t, level);
            if (tempFlow != 0) {
                e.flow += tempFlow;
                graph[e.to][e.rev].flow -= tempFlow;
                return tempFlow;
            }
        }
    }
    return 0;
}

bool bfs(vector<Edge> graph[], int level[], int n, int s, int t) {
    for (int i = 0; i < n; i++) {
        level[i] = -1;
    }
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < graph[cur].size(); i++) {
            Edge &e = graph[cur][i];
            if (level[e.to] < 0 && e.flow < e.capacity) {
                level[e.to] = level[cur] + 1;
                q.push(e.to);
            }
        }
    }
    return level[t] > 0;
}

int dinic(vector<Edge> graph[], int n, int s, int t) {
    if (s == t)
        return 0;
    int maxFlow = 0;
    int level[n];
    while (bfs(graph, level, n, s, t)) {
        while (int flow = pushflow(graph, s, INT_MAX, t, level))
            maxFlow += flow;
    }
    return maxFlow;
}


int main() {
    int n, m;
    fin >> n >> m;
    n += 2;
    vector<Edge> graph[n];
    vector<pair<int, int>> edges;
    vector<int> mc;
    for (int i = 0; i < m; i++) {
        int from, to, minCap, maxCap;
        fin >> from >> to >> minCap >> maxCap;
        Edge g(to, 0, minCap, graph[to].size(), true);
        Edge gRev(0, 0, 0, graph[0].size(), false);
        Edge h(to, 0, maxCap - minCap, graph[to].size() + 1, true);
        Edge hRev(from, 0, 0, graph[from].size(), false);
        Edge k(n - 1, 0, minCap, graph[n - 1].size(), true);
        Edge kRev(from, 0, 0, graph[from].size() + 1, false);
        graph[0].push_back(g);
        graph[to].push_back(gRev);
        graph[from].push_back(h);
        edges.emplace_back(from, graph[from].size() - 1);
        graph[to].push_back(hRev);
        graph[from].push_back(k);
        graph[n - 1].push_back(kRev);
        mc.push_back(minCap);
    }
    int maxFlow = dinic(graph, n, 0, n - 1);
    bool ok = true;
    for (int i = 0; i < graph[0].size(); i++) {
        if (graph[0][i].exists) {
            Edge e = graph[0][i];
            if (e.flow < e.capacity) {
                ok = false;
                break;
            }
        }
    }
    if (!ok)
        fout << "NO";
    else {
        fout << "YES\n";
        for (int i = 0; i < edges.size(); i++) {
            fout << mc[i] + graph[edges[i].first][edges[i].second].flow << "\n";
        }
    }
    return 0;
}
