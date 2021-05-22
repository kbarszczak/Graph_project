#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cfloat>
#include <exception>
#include <regex>

#ifndef PROJEKT_GRAPH_H
#define PROJEKT_GRAPH_H


// ------------------------------------------ Edge class declaration
class Edge{
private:
    friend class Graph;
    friend class Path;
    int begin; // beginning node
    int end; // ending node
    double value; // weight of the edge (value)

public:
    explicit Edge(int _begin=0, int _end=0, double _value=0);
    ~Edge()=default;
    [[nodiscard]] int get_begin()const;
    [[nodiscard]] int get_end()const;
    bool operator==(const Edge&e)const; // operator that checks if two edges are equal (doesnt compare values of edges)
    friend std::ostream &operator<<(std::ostream &os, const Edge&e); // operator that prints edge in format "begin -> end [value]"
};
// ------------------------------------------ Path class declaration
class Path{
    std::vector<Edge> edges; // edges which belongs to the path
public:
    ~Path();
    [[nodiscard]] bool add_back(const Edge&e); // function that adds the edge at the ending of the path (if it is possible)
    [[nodiscard]] bool add_front(const Edge&e); // function that adds the edge at the beginning of the path (if it is possible)
    [[nodiscard]] double path_weight()const; // returns path weight
    friend std::ostream &operator<<(std::ostream &os, const Path&p); // operator prints path to output stream in format "1node->2node->...->knode"
};
// ------------------------------------------ Graph class declaration
class Graph{
private:
    std::vector<Edge> edges;
    std::vector<int> vertexes;
    int vertex_count;
    int edge_count;

public:
    Graph(); // standard constructor
    explicit Graph(const std::vector<Edge>&_edges); // additional constructor that takes vector of edges
    ~Graph(); // default

    [[nodiscard]] int get_vertex_count()const;
    [[nodiscard]] int get_edge_count()const;
    [[nodiscard]] bool is_vertex_in_graph(int _v)const; // function that checks if the vertex is in the graph
    void add_edge(Edge e); // function that adds edge to graph and updates count values
    friend std::ostream &operator<<(std::ostream &os, const Graph&g); // operator that prints whole graph to output stream
    friend std::istream &operator>>(std::istream &is, Graph&g); // operator that reads graph from the input stream from adjacency lists(layout is described in the readme.md file and below in the main function)

    [[nodiscard]] std::vector<Path> ford_bellman(int starting_node)const; // ford-bellman algorithm

protected:
    static void relax(int starting_node, int ending_node, double path_value, std::map<int, double>& value, std::map<int, int>& ancestor); // helping method to ford-bellman algorithm
    void clear();
};

#endif
