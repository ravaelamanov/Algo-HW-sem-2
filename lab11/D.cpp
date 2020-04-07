#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
const long long INF = 9e18;

ifstream fin("path.in");
ofstream fout("path.out");

class Edge {
public:
    int to;
    long long weight;
    Edge(int to, long long weight) {
        this->to = to;
        this->weight = weight;
    }
};

void dfs(int v, vector<Edge> graph[], bool visited[]) {
    visited[v] = true;
    for (int i = 0; i < graph[v].size(); i++) {
        if (!visited[graph[v][i].to])
            dfs(graph[v][i].to, graph, visited);
    }
}

void bellmanFord(vector<Edge> graph[], int vertexes, int start) {
    vector<long long> dist(vertexes, INF);
    int parent[vertexes];
    bool noPath[vertexes];
    bool reachable[vertexes];
    for (int i = 0; i < vertexes; i++) {
        reachable[i] = false;
        noPath[i] = false;
        parent[i] = -1;
    }
    dist[start] = 0;
    dfs(start, graph, reachable);
    int x = -1;
    for (int i = 0; i < vertexes; i++) {
        bool changed = false;
        x = -1;
        for (int j = 0; j < vertexes; j++) {
            for (int k = 0; k < graph[j].size(); k++) {
                if (dist[j] < INF && dist[graph[j][k].to] > dist[j] + graph[j][k].weight) {
                    dist[graph[j][k].to] = max(-INF, dist[j] + graph[j][k].weight);
                    parent[graph[j][k].to] = j;
                    x = graph[j][k].to;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }
    if (x != -1) {
        for (int i = 0; i < vertexes; i++)
            x = parent[x];
        dfs(x, graph, noPath);
    }
    for (int i = 0; i < vertexes; i++) {
        if (!reachable[i])
            fout << "*" << "\n";
        else if (noPath[i])
            fout << "-" << "\n";
        else
            fout << dist[i] << "\n";
    }
}

int main() {
    int vertexes, edges, start, from, to;
    long long weight;
    fin >> vertexes >> edges >> start;
    vector<Edge> graph[vertexes];
    while (edges--) {
        fin >> from >> to >> weight;
        graph[from - 1].emplace_back(to - 1, weight);
    }
    bellmanFord(graph, vertexes, start - 1);
    return 0;
}
