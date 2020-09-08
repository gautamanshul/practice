#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <list>
/// Find the connected components in a graph
/// Use DFS algorithm to identify the connected components
/// Uses the components vector to classify elements of each component
/// Time complexity of DFS O( V + E )
namespace  connected_components
{
    class graph
    {
    public:
        explicit graph(int v);
        void add( int src, int dst ); /// Add nodes to a graph
        void print( const std::string &  lhs, int value ); /// Print function
        void find_components(); /// Find the components in a graph
        void dfs( int index );  /// DFS algorithm
        std::vector<boost::shared_ptr<std::vector<int>>>  adj; /// Adjacency list
        std::vector<int>  components;   /// component identifier
        std::vector<bool> visited;      /// Visited array
        int count;                      ///  Number of components
    };

    void graph::dfs( int index )
    {
        visited[index] = true;
        components[index] = count;
        std::for_each( adj[index]->begin(), adj[index]->end(), [&] (int & node )
        {
            if (!visited[node]) dfs(node);
        } );
    }

    graph::graph(int v)
    {
        count = 0;
        adj.resize( v );
        components.resize(v);
        visited.resize(v, false);
        std::for_each( adj.begin(), adj.end(), [] (boost::shared_ptr<std::vector<int>> & vec_node )
        {
           vec_node = boost::make_shared<std::vector<int>>();
        });
    }

    void graph::add( int src, int dst )
    {
        adj[src]->push_back( dst );
        adj[dst]->push_back( src );
    }

    void graph::print( const std::string &  lhs, int value )
    {
        std::cout << lhs << value << std::endl;
    }
    void graph::find_components()
    {
        for( int i = 0; i < adj.size(); ++i )
        {
            if ( !visited[i] )
            {
                count++;
                dfs(i);
            }
        }

        print( "Number of components: ", count );
        for( int i = 0; i < components.size(); ++i )
        {
            std::cout << "Node " << i << " belongs to component " << components[i] << std::endl;
        }
    }
    int main(int argc, char *argv[])
    {
        connected_components::graph g(18);
        g.add(0, 4);
        g.add(0, 13);
        g.add( 0, 14);
        g.add(0, 8);
        g.add(6, 11);
        g.add(6, 7);
        g.add( 3, 9);
        g.add( 9, 15);
        g.add( 9, 2);
        g.add( 2, 10);
        g.add( 1,5);
        g.add(5, 16);
        g.add(5, 17);

        g.find_components();
    }
}




