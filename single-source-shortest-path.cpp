#include <iostream>
#include <map>
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <vector>

/// Finding shortest path using topological sort between two nodes in a DAG
namespace sssp {

    struct node
    {
        node( int dst, int weight );

        int dst;
        int weight;

        typedef boost::shared_ptr<node> ptr;

    };

    node::node( int dst, int weight ) :
        dst(dst), weight(weight)
    {}

    template <typename T>
    class graph
    {
    public:
        graph(const int size); // Number of nodes in the DAG
        void add_edge( int src, int dst, int weight ); /// Add edge from source to destination with weight
        void dfs( const int i );
        std::map<int, std::list<boost::shared_ptr<T>>> adj;
        std::vector<bool> visited;
        void topological_sort();
        void dag_shortest_path(int start);
        std::vector<int>  sorted; // topologically sorted
        std::vector<int> dist; // distance vector
    };

    template <typename  T>
    void graph<T>::dag_shortest_path(int start)
    {
        dist[start] = 0;
        /// iterate through topologically sorted nodes
        std::for_each(sorted.rbegin(), sorted.rend(), [&] (const int &  elem) {
            std::for_each( adj[elem].begin(), adj[elem].end(), [&] (const boost::shared_ptr<T> node) {
                if (dist[node->dst] > dist[elem] + node->weight)
                    dist[node->dst] = dist[elem] + node->weight;
            });
        });

        std::cout << "distance vector:" << std::endl;
        std::for_each(dist.begin(), dist.end(), [] (const int & distance) {
            std::cout << distance << " ";
        });
        std::cout << std::endl;
    }

    template <typename T>
    graph<T>::graph(const int size)
    {
        visited.resize(size, false);
        dist.resize(size, std::numeric_limits<int>::max());
    }

    template <typename T>
    void graph<T>::add_edge(const int src, const int dst, const int weight)
    {
        adj[src].push_back(boost::make_shared<T>(dst, weight));
    }

    template <typename T>
    void graph<T>::dfs( const int i )
    {
        if ( visited[i] == true )
            return;
        visited[i] = true;
        std::for_each( adj[i].begin(), adj[i].end(), [&] ( const boost::shared_ptr<T> & n )
        {
            if ( !visited[n->dst]) {
                dfs(n->dst);
                sorted.push_back(n->dst);
            }
        } );
    }

    template <typename T>
    void graph<T>::topological_sort() {
        /// Start at any node
        std::for_each(adj.begin(), adj.end(), [&] ( const std::pair<int, std::list<boost::shared_ptr<T>>> & itr)
        {
            if (!visited[itr.first])
            {
                dfs(itr.first);
                sorted.push_back(itr.first);
            }
        });
        std::cout << "topological sort: " << std::endl;
        std::for_each( sorted.rbegin(), sorted.rend(), [] ( const int & i ) {
            std::cout << i << " ";
        });
        std::cout << std::endl;
    }

    int main(int argc, char * argv[])
    {
        /// Create directed acyclic graph
        sssp::graph<sssp::node> g(8);
        g.add_edge(0, 1, 3);
        g.add_edge(0, 2, 6);
        g.add_edge(1, 2, 4);
        g.add_edge(1, 3, 4);
        g.add_edge(1, 4, 11);
        g.add_edge(2, 3, 8);
        g.add_edge(2, 6, 11);
        g.add_edge(3, 4, -4);
        g.add_edge(3, 5, 5);
        g.add_edge(3, 6, 2);
        g.add_edge(4, 7, 9);
        g.add_edge(5, 7, 1);
        g.add_edge(6, 7, 2);

        g.topological_sort();
        g.dag_shortest_path(0);
        return 0;
    }
}


