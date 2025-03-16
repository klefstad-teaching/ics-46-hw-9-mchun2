#include "dijkstras.h"
#include <algorithm>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = -1;
    std::priority_queue<pair<int,int>, vector<pair<int, int>>, std::greater<pair<int,int>>> minHeap;
    minHeap.push({0,source});
    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        int uDist = minHeap.top().first;
        minHeap.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && uDist + weight < distances[v]) {
                distances[v] = uDist + weight;
                previous[v] = u;
                minHeap.push({distances[v],v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) {
        return {};
    }

    for (int v = destination; v!= -1; v= previous[v]) {
        path.push_back(v);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "no path" << endl;
        return;
    }

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}

