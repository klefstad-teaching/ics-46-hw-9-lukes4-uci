#include "dijkstras.h"

std::string get_arg(int argc, char *argv[], string def) {
    return argc > 1 ? argv[1] : def;
}

// void file_to_graph(std::string filename, Graph & G) {
//     std::ifstream in(filename);
//     in >> G;

// }

int main(int argc, char *argv[]) {
    std::string filename = get_arg(argc, argv, "src/small.txt");
    Graph G;
    file_to_graph(filename, G);
    int num_verticies = G.numVertices;

    std::vector<int> previous(num_verticies, 0);
    std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    for(int i = 0; i < num_verticies; ++i) {
        std::vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }
}