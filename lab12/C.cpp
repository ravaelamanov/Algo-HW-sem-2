#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <list>
using namespace std;

ifstream fin("decomposition.in");
ofstream fout("decomposition.out");

class Edge {
public:
    int from, to, capacity, flow, rev, num;

    Edge(int from, int to, int flow, int capacity, int rev, int num) {
        this->from = from;
        this->to = to;
        this->capacity = capacity;
        this->flow = flow;
        this->rev = rev;
        this->num = num;
    }
};

int pushflow(vector<Edge> graph[], int u, int flow, int t, int level[], int start[]) {
    if (u == t) return flow;
    for (; start[u] < graph[u].size(); start[u]++) {
        Edge &e = graph[u][start[u]];
        if (level[e.to] == level[u] + 1 && e.flow < e.capacity) {
            int curFlow = min(flow, e.capacity - e.flow);
            int tempFlow = pushflow(graph, e.to, curFlow, t, level, start);
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
        for (int i = 0; i < n + 1; i++) {
            start[i] = 0;
        }
        while (int flow = pushflow(graph, s, INT_MAX, t, level, start))
            maxFlow += flow;
    }
    return maxFlow;
}

pair<int, list<Edge>> decomposition_aux(int cur, vector<Edge> graph[], int n, int t) {
    vector<bool> visited(n, false);
    list<Edge> path;
    int v = cur;
    vector<int> adjNum;
    while (!visited[v]) {
        if (v == t) break;
        Edge* e = nullptr;
        for (int u = 0; u < graph[v].size(); u++) {
            if (graph[v][u].num != -1) {
                if (graph[v][u].flow > 0) {
                    e = &graph[v][u];
                    adjNum.push_back(u);
                    break;
                }
            }
        }
        if (!e) {
            return make_pair(0, list<Edge>());
        }
        visited[v] = true;
        path.push_back(*e);
        v = e->to;
    }
    if (visited[v]) {
        while (path.begin()->from != v) {
            path.pop_front();
        }
    }
    int minFlow = INT_MAX;
    for (auto &p : path) {
        if (p.flow < minFlow)
            minFlow = p.flow;
    }
    int i = 0;
    for (auto &p : path) {
        graph[p.from][adjNum[i++]].flow -= minFlow;
    }
    return make_pair(minFlow, path);
}

void decomposition(vector<Edge> graph[], int n, int s, int t) {
    int maxFlow = dinic(graph, n, s, t);
    vector<pair<int, list<Edge>>> dec;
    pair<int, list<Edge>> path;
    path = decomposition_aux(s, graph, n, t);
    while (!path.second.empty()) {
        dec.push_back(path);
        path = decomposition_aux(s, graph, n, t);

    }
    for (int u = 0; u < n - 1; u++) {
        path = decomposition_aux(u, graph, n, t);
        while (!path.second.empty()) {
            dec.push_back(path);
            path = decomposition_aux(u, graph, n, t);
        }
    }

    fout << dec.size() << "\n";
    for (int i = 0; i < dec.size(); i++) {
        fout << dec[i].first << " " << dec[i].second.size() << " ";
        for (auto &e : dec[i].second) {
            fout << e.num << " ";
        }
        fout << "\n";
    }
}

int main() {
    int n, m;
    fin >> n >> m;
    int from, to, capacity;
    vector<Edge> graph[n];
    for (int i = 0; i < m; i++) {
        fin >> from >> to >> capacity;
        Edge a(from - 1, to - 1, 0, capacity, graph[to - 1].size(), i + 1);
        Edge b(to - 1, from - 1, 0, 0, graph[from - 1].size(), -1);
        graph[from - 1].push_back(a);
        graph[to - 1].push_back(b);
    }
    decomposition(graph, n, 0, n - 1);
    return 0;
}
