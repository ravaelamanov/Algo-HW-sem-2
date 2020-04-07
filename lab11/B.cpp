#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <climits>
using namespace std;

ifstream fin("pathsg.in");
ofstream fout("pathsg.out");

void floydWarshall(vector<pair<int, int>> graph[], int vertexes) {
    unsigned int dist[vertexes + 1][vertexes + 1];
    for (int i = 1; i <= vertexes; i++) {
        for (int j = 1; j <= vertexes; j++) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INT_MAX;

        }
    }
    for (int i = 1; i <= vertexes; i++) {
        for (int j = 0 ; j < graph[i].size(); j++) {
            dist[i][graph[i][j].first] = graph[i][j].second;
        }
    }
    for (int i = 1; i <= vertexes; i++) {
        for (int j = 1; j <= vertexes; j++) {
            for (int k = 1; k <= vertexes; k++) {
                if (dist[j][k] > dist[j][i] + dist[i][k]) {
                    dist[j][k] = dist[j][i] + dist[i][k];
                }
            }
        }
    }
    for (int i = 1; i <= vertexes; i++) {
        for (int j = 1; j <= vertexes; j++)
            fout << dist[i][j] << " ";
        fout << "\n";
    }
}


int main() {
    int vertexes, edges, n1, n2, weight;
    fin >> vertexes >> edges;
    vector<pair<int, int>> graph[vertexes + 1];
    while (edges--) {
        fin >> n1 >> n2 >> weight;
        graph[n1].emplace_back(n2, weight);
    }
    floydWarshall(graph, vertexes);
    return 0;
}
