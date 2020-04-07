#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

class Edge {
public:
    int from, to, weight;
};

ifstream fin("negcycle.in");
ofstream fout("negcycle.out");

void bellmanFord(vector<Edge> &e, int vertexes) {
    long long dist[vertexes];
    int parent[vertexes];
    for (int i = 0; i < vertexes; i++) {
        parent[i] = -1;
        dist[i] = 1;
    }
    dist[0] = 0;
    int x;
    for (int i = 0; i < vertexes; i++) {
        x = -1;
        bool changed = false;
        for (int j = 0; j < e.size(); j++) {
            if (dist[e[j].to] > dist[e[j].from] + e[j].weight) {
                dist[e[j].to] = dist[e[j].from] + e[j].weight;
                parent[e[j].to] = e[j].from;
                x = e[j].to;
                changed = true;
            }
        }
        if (!changed)
            break;
    }

    if (x != -1) {
        fout << "YES\n";
        for (int i = 0; i < vertexes - 1; i++) {
            x = parent[x];
        }
        vector<int> path;
        for (int i = x;; i = parent[i]) {
            path.push_back(i);
            if (i == x && path.size() > 1) break;
        }
        reverse(path.begin(), path.end());
        fout << path.size() << "\n";
        for (int i = 0; i < path.size(); i++) {
            fout << path[i] + 1 << " ";
        }
    } else
        fout << "NO";
}

int main() {
    int vertexes, weight;
    fin >> vertexes;
    vector<Edge> e;
    for (int i = 0; i < vertexes; i++) {
        for (int j = 0; j < vertexes; j++) {
            fin >> weight;
            if (weight <= 10007) {
                e.push_back({i, j, weight});
            }
        }
    }
    bellmanFord(e, vertexes);
    return 0;
}
