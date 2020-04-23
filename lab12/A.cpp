#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

class Edge {
public:
    int to, capacity, flow, rev;

    Edge(int to, int flow, int capacity, int rev) {
        this->to = to;
        this->capacity = capacity;
        this->flow = flow;
        this->rev = rev;
    }
};

int pushflow(vector<Edge> graph[], int u, int flow, int t, int level[]) {
    if (u == t) return flow;
    for (int i = 0; i < graph[u].size(); i++) {
        Edge &e = graph[u][i];
        if (level[e.to] == level[u] + 1 && e.flow < e.capacity) {
            int curFlow = min(flow, e.capacity - e.flow);
            int tempFlow = pushflow(graph, e.to, curFlow, t, level);
            if (tempFlow > 0) {
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
        int start[n + 1];
        while (int flow = pushflow(graph, s, INT_MAX, t, level))
            maxFlow += flow;
    }
    return maxFlow;
}

int main() {
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");
    int n, m;
    fin >> n >> m;
    int from, to, capacity;
    vector<Edge> graph[n];
    for (int i = 0; i < m; i++) {
        fin >> from >> to >> capacity;
        Edge a(to - 1, 0, capacity, graph[to - 1].size());
        Edge b(from - 1, 0, 0, graph[from - 1].size());
        graph[from - 1].push_back(a);
        graph[to - 1].push_back(b);
    }
    fout << dinic(graph, n, 0, n - 1);
    return 0;
}
