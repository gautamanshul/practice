#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <list>

namespace topological_sort {

    class graph
    {
    public:
        void add_edge(int src, int dst);
        graph(int v);
        void topo_sort();

    private:
        std::vector<boost::shared_ptr<std::list<int>>>  adj;
    };

    graph::graph( int v )
    {
        adj.resize( v );
        std::for_each( adj.begin(), adj.end(), [](boost::shared_ptr<std::list<int>> & p)
        {
            p = boost::make_shared<std::list<int>>();
        });
    }

    void graph::topo_sort() {
        // add vertex to visited list
        // explore neighbors
    }
    void graph::add_edge(int src, int dst) {
        adj[src]->push_back(dst);
    }
    int main()
    {
        topological_sort::graph g( 7 );
        g.add_edge(1, 3);
        g.add_edge( 2, 3 );
        g.add_edge(3, 4);
        g.add_edge(4,6);
        g.add_edge(6, 7);
        g.add_edge( 5, 6 );

        for( int i = 0; i < 7; i++)
        {
         //   topo_sort( g);
        }

    }
}

