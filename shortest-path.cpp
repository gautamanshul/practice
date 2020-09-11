#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <queue>
/// Shortest path can be found by using BFS algorithm on an unweighted graph
/// BFS
/// Finding the shortest path on unweighted graph
/// Time complexity is O(V + E)
/// Space complexity: is directly proportional to the size of the queue. In worst case, it will be O( n ) as the nodes
/// are in the single tree.
/// Explore node in layers
/// Uses queue to explore layers

namespace shortest_path {
    class graph
    {
    public:
        int V; /// Number of vertices in the graph
        void add( int src, int dst ); /// Add the source to the destination node
        graph( int v); /// Constructor
        void solve(int start);  /// BFS algorithm
        void reconstruct_path( int start, int end ); /// Reconstruct the path from start to the end.
        std::vector<boost::shared_ptr<std::vector<int>>> adj; /// Adjacency list representation of the graph
        std::queue<int>  q; /// Queue for enqueing and dequeuing vertexes
        std::vector<bool>  visited; /// Track visited nodes
        std::vector<int>  parent; /// Track parent of a node
    };

    graph::graph(int v)
    {
        adj.resize( v );
        std::for_each( adj.begin(), adj.end(), [] (boost::shared_ptr<std::vector<int>> &  node )
        {
            node = boost::make_shared<std::vector<int>>();
        } );
        visited.resize(v, false);
        parent.resize( v, -1);
    }

    void graph::add(int src, int dst)
    {
        adj[src]->push_back( dst );
    //    adj[dst]->push_back( src );
    }

    void graph::solve(int start)
    {
        /// Enqueue the start vertex in a queue
        q.push( start );
        visited[start] = true;
        while( !q.empty() )
        {
            /// pop the enqueued node
            int vertex = q.front();
            q.pop();
            std::for_each(adj[vertex]->begin(), adj[vertex]->end(), [&](int &ver)
            {
                if (!visited[ver]) {
                    q.push(ver);
                    parent[ver] = vertex;
                    visited[ver] = true;
                }
            });
        }
    }

    void graph::reconstruct_path( int start, int end )
    {
        int temp = end;
        std::cout << temp << "->";
        while ( parent[temp] != -1 )
        {
            std::cout << parent[temp] << "->";
            temp = parent[temp];
        }
        std::cout << "Parent array" << std::endl;
    }

    int main(int argc, char * argv[])
    {
        shortest_path::graph g(4);
        g.add(0, 1);
        g.add( 0 , 2 );
        g.add(1, 2 );
        g.add(2, 3);

        g.solve(0);
        g.reconstruct_path(0,3);
        return 0;
    }
}

