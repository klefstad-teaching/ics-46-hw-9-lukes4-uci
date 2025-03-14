#include "dijkstras.h"
#include <iostream>

class MinHeapComparator {
    public: 
        int operator() (const std::pair<int, int> a, const std::pair<int, int> b) {
            return a.second < b.second; // puts the lowest weight first
        }
};

std::vector<int> dijkstra_shortest_path(const Graph& G, int source, std::vector<int>& previous) {
    std::vector<int> distances(G.numVertices, INF);
    std::vector<bool> visited(G.numVertices, false);
    distances[source] = 0;
    previous[source] = -1; 
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, MinHeapComparator> minHeap;
    minHeap.push({source, 0});

    while(!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(Edge e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if(!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}

std::vector<int> extract_shortest_path(const std::vector<int>& distances, const std::vector<int>& previous, int destination) {
    std::stack<int> vertex_stack;
    for(int u = destination; u != -1; u = previous[u]) {
        vertex_stack.push(u);
    }
    // vertex_stack.push(0);
    std::vector<int> ret;
    while(!vertex_stack.empty()) {
        int u = vertex_stack.top();
        ret.push_back(u);
        vertex_stack.pop();
    }

    // std::vector<int> ret;
    // for(int u = destination; u != 0; u = previous[u]) {
    //     ret.push_back(u);
    // }
    // ret.push_back(0);
    return ret;
}
void print_path(const std::vector<int>& v, int total) {
    int size = v.size();
    for(int i = 0; i < size; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl << "Total cost is " << total << std::endl;
}
