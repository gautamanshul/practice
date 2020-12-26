#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

/// A topological sort ordering is an ordering of the nodes in a directed graph where for each directed edge
/// from node A to node B, node A appears before bode B in the ordering.
/// The topological sort algorithm can find a topological ordering in O(V + E) time!
/// A graph which contains a cycle cannot have a valid ordering
/// The only type of graph which has a valid topological ordering is a Directed
/// Acyclic Graph (DAG). These are graphs with directed edges and no cycles.

/// Tarjan's strongly connected component cant be used to detect cycles
/// Topological sort algorithm:
/// 1. Pick any unvisited node
/// 2. Do a DFS exploring only unvisited nodes
/// 3. On the recursive callback of the DFS, add the current node to the topological ordering in reverse order

namespace topo_sort {

    class graph
    {
    public:
        graph( int size );
        void add_edge( int src, int dst ); // Add edge from source to destination
        void topo_sort();
        void dfs( int index );
        std::vector<int> sorted; // topologically sorted nodes
        std::vector<boost::shared_ptr<std::vector<int>>> adj;
        std::vector<int> visited;
    };

    graph::graph( int size )
    {
        adj.resize(size);
        visited.resize(size, false);
        std::for_each( adj.begin(), adj.end(), [] (boost::shared_ptr<std::vector<int>> &  node ) {
            node = boost::make_shared<std::vector<int>>();
        } );
    }

    void graph::add_edge( int src, int dst )
    {
        adj[src]->push_back(dst);
    }

    void graph::dfs( int index )
    {
        /// Explore neighbor and push onto the stack
        visited[index] = true;
        std::for_each ( adj[index]->begin(), adj[index]->end(), [&] (int & node ) {
            if ( !visited[node]) {
                dfs(node);
                sorted.push_back(node);
            }
        } );

    }

    void graph::topo_sort()
    {
        for ( int i = 0; i <  adj.size(); i++ )
        {
            if ( !visited[i] && adj[i]->size() != 0) {
                dfs(i);
                sorted.push_back(i);
            }
        }

        std::for_each( sorted.rbegin(), sorted.rend(), [] (const int & node ) { std::cout << node << " ";});
    }

    int main()
    {
        topo_sort::graph g( 7 );
        g.add_edge(0, 2);
        g.add_edge( 1, 2 );
        g.add_edge(2, 3);
        g.add_edge(3,5);
        g.add_edge(5, 6);
        g.add_edge(4, 5);

        g.topo_sort();
    }
}

