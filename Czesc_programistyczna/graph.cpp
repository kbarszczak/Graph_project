#include "graph.h"

// ------------------------------------------ Edge class implementation

Edge::Edge(int _begin, int _end, double _value):begin(_begin),end(_end),value(_value){
    if(begin<0 || end<0) throw std::invalid_argument("Vertex index cannot be negative\n");
}
int Edge::get_begin()const{
    return begin;
}
int Edge::get_end()const{
    return end;
}
bool Edge::operator==(const Edge &e)const{
    return (begin == e.begin && end == e.end);
}
std::ostream &operator<<(std::ostream &os, const Edge&e){
    os<<e.begin<<" -> "<<e.end<<" ["<<e.value<<"]";
    return os;
}

// ------------------------------------------ Path class implementation

Path::~Path(){
    edges.clear();
}
bool Path::add_back(const Edge&e) {
    if(edges.empty()) edges.push_back(e);
    else{
        if(edges.back().get_end() == e.get_begin()) edges.push_back(e);
        else return false;
    }
    return true;
}
bool Path::add_front(const Edge&e) {
    if(edges.empty()) edges.insert(edges.begin(), e);
    else{
        if(edges.begin()->get_begin() == e.get_end()) edges.insert(edges.begin(), e);
        else return false;
    }
    return true;
}
double Path::path_weight()const{
    double path_weight = 0;
    for(const auto&e:edges) path_weight += e.value;
    return path_weight;
}
std::ostream &operator<<(std::ostream &os, const Path&p){
    if(p.edges.empty()){
        os<<"Path is empty";
        return os;
    }

    os<<"Path: ";
    int i=(int)p.edges.size();
    if(i>1) os<<p.edges[0].get_begin();
    else if(i==1) os<< p.edges[0].get_begin() <<" -> "<<p.edges[0].get_end();

    for(int j=1; j<i; j++){
        os<<" -> "<<p.edges[j].get_begin();
        if(j==i-1) os<<" -> "<<p.edges[j].get_end();
    }
    return os;
}

// ------------------------------------------ Graph class implementation

Graph::Graph():vertex_count(0), edge_count(0){}
Graph::Graph(const std::vector<Edge>&_edges):vertex_count(0), edge_count(0){
    for(const auto&e:_edges) add_edge(e);
}
Graph::~Graph() {
    clear();
}
int Graph::get_vertex_count()const{
    return vertex_count;
}
int Graph::get_edge_count()const{
    return edge_count;
}
bool Graph::is_vertex_in_graph(int _v)const{
    bool is_vertex = false;
    for(const auto &v:vertexes) {
        if(_v == v ) {
            is_vertex = true;
            break;
        }
    }
    return is_vertex;
}
void Graph::add_edge(Edge e) {
    if(!is_vertex_in_graph(e.begin)){
        ++vertex_count;
        vertexes.push_back(e.begin);
    }
    if(!is_vertex_in_graph(e.end)){
        ++vertex_count;
        vertexes.push_back(e.end);
    }
    ++edge_count;
    edges.push_back(e);
}
std::ostream &operator<<(std::ostream &os, const Graph&g){
    if(!g.get_vertex_count()){
        os<<"Empty";
        return os;
    }
    os<<"Loaded graph:\n";
    os<<"Number of vertexes: "<<g.get_vertex_count()<<std::endl;
    os<<"Number of egdes: "<<g.get_edge_count()<<std::endl;

    os<<"Vertexes: ";
    for(const auto &v:g.vertexes) os<<v<<" ";

    os<<"\nEdges:\n";
    for(const auto &v:g.vertexes)
        for(const auto&e:g.edges)
            if(v == e.get_begin()) os<<e<<std::endl;

    return os;
}
std::istream &operator>>(std::istream &is, Graph &g) {
    if(!is) return is;

    g.clear();
    std::string buf;
    int begin, end;
    char check_sign;
    double value;

    while(getline(is, buf, '\n')){
        if(!std::regex_match(buf, std::regex(R"(^[0-9]+:( [0-9]+ -?[0-9]+(\.[0-9]+)?)+$)"))) {
            throw std::domain_error("File has an incorrect format in line: \"" + buf + R"(". Problem may be with ' ' sign at the end of the line. Exact rules of file format are described in the main function and in the readme.md file)");
        }

        std::istringstream buf_stream(buf);
        buf_stream>>begin; // read beginning node
        buf_stream>>check_sign; // get : sign
        while(true){
            buf_stream>>end; // read ending node
            if(!buf_stream) break; // if !buf_stream is true that means the stream is empty after reading end, so there is no more values
            buf_stream>>value; // read edge weight
            g.add_edge(Edge(begin, end, value));
        }
    }
    return is;
}
std::vector<Path> Graph::ford_bellman(int starting_node) const { //------------------------------------------------------------------------------- ford-bellman algorithm
    std::vector<Path> paths;
    if(!is_vertex_in_graph(starting_node)) throw std::invalid_argument("Selected vertex does not belong to the graph");

    std::map<int, double> weights; // map<vertex, current_lowest_value>
    std::map<int, int> ancestor; // map<ancestor, current>

    for(const int &vertex:vertexes){ // set initial values
        ancestor[vertex] = -1;
        weights[vertex] = DBL_MAX;
    }
    weights[starting_node] = 0;

    for(const int &vertex:vertexes){ // relax edges vertex_count - 1 times
        if(vertex == starting_node) continue; // ignore 1 vertex
        for(const auto &e:edges) relax(e.get_begin(), e.get_end(), e.value, weights, ancestor); // relax every edge vertex_count - 1 times (relax method is implemented below)
    }
    for(const auto &e:edges){ // check if there is any negative cycle in the graph
        if(weights[e.get_end()] > weights[e.get_begin()] + e.value) throw std::logic_error("There are negative cycles in the graph");
    }

    for(const int &vertex:vertexes){ // create paths from gathered data (this is not the part of ford-bellman's algorithm)
        if(vertex == starting_node) continue;
        int end_node = vertex;
        Path p;
        bool to_add = true;

        while(end_node != starting_node){
            if(ancestor[end_node] == -1) { // path from starting_node to end_node does not exist
                to_add = false;
                break;
            }
            Edge tmp(ancestor[end_node], end_node);
            for(const auto&e:edges){
                if(e == tmp){
                    if(!p.add_front(e)) throw std::invalid_argument("Edge cannot be added to the path. Error in ford_bellman function");
                    break;
                }
            }
            end_node = ancestor[end_node];
        }
        if(to_add) paths.push_back(p);
    }

    return paths;
}
void Graph::relax(int starting_node, int ending_node, double path_value, std::map<int, double>& value, std::map<int, int>& ancestor) {
    if(value[ending_node] > value[starting_node] + path_value){
        value[ending_node] = value[starting_node] + path_value;
        ancestor[ending_node] = starting_node;
    }
}
void Graph::clear() {
    edges.clear();
    vertexes.clear();
    vertex_count=0;
    edge_count=0;
}