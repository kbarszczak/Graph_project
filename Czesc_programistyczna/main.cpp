#include "graph.h"

using namespace std;

int main() {
    // reading graph from file using >> operator:
    // operator >> reads graph from adjacency lists format.
    // format of the file has to be like: "starting_node:( ending_node edge_value)*". Remember that ' ' cannot be the last sign. "2: 1 -34.2"->ok | "2: 1 -34.2 "->this will occur error.
    // ()* star means that string in the brackets can be repeated many times
    // ending node and starting_node are positive integer values.
    // edge_value is a any double value.
    // example:
    // "1: 2 12.34 5 -2.3 8 2.2"            (edges: 1->2 [12.34], 1->5 [-2.3], 1->8 [2.2])
    // "2: 1 2"                             (edges: 2->1 [2])
    // "5: 1 12.3"                          (edges: 5->1 [12.3])

    try{
        string file_name;
        int starting_node = 0;
        cout<<"File name: ";
        cin>>file_name;

        ifstream file(file_name.c_str()); // creating file input stream
        if(!file) throw invalid_argument("File \""+file_name+"\" was not found\n"); // check if file was opened well

        Graph g1; // creating graph
        file>>g1; // reading from loaded file

        do{ // read starting vertex
            cout<<"Starting vertex: ";
            cin>>starting_node;
            if(starting_node<0) cout<<"Wrong vertex index. Vertex should be positive integer value.";
        }while(starting_node<0);

        vector<Path> paths=g1.ford_bellman(starting_node); // find paths from starting vertex to every other vertex
        cout<<g1<<endl; // printing graph
        for(const auto&p:paths) cout<<p<<" weight: "<<p.path_weight()<<endl; // display found paths with their weights
    }
    catch(const exception &e){
        cerr<<"Error: "<<e.what()<<endl;
    }
    cout<<endl;
    system("pause");

    return 0;
}


