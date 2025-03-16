#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("src/small.txt", G);
    int source = 0;
    int destination = 4;
    
    vector<int> previous(G.size(),-1);
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    vector<int> path = extract_shortest_path(distances, previous, destination);
    print_path(path, distances[destination]);

    return 0;
}