#include <string>
#include <iostream>
// Binary search tree. Insertion time is log v and finding an element takes O ( log v ) time
#include <set>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace graph_set {
    class graph {
    public:
        graph(int v);

        void add_edge(int src, int dst);

        void print();

    private:
        std::vector<boost::shared_ptr<std::set<int, std::greater<int>>>> adj;

    };

    graph::graph(int v) {
        adj.resize(v);
        for (int i = 0; i < adj.size(); ++i) {
            adj[i] = boost::make_shared<std::set<int, std::greater<int>>>();
        }
    }

    void graph::print() {
        int i = 0;

        for (std::vector<boost::shared_ptr<std::set<int, std::greater<int>>>>::iterator it = adj.begin();
             it != adj.end(); ++it) {

            std::cout << "Source vertex: " << i << std::endl;
            for (std::set<int, std::greater<int>>::iterator itr = (*it)->begin();
                 itr != (*it)->end(); ++itr) {
                std::cout << "Destination vertex: " << *itr << std::endl;
            }
            ++i;
        }
    }

    void graph::add_edge(int src, int dst) {
        adj[src]->insert(dst);
        adj[dst]->insert(src);
    }
    int main()
    {
        graph_set::graph  g( 5 );
        g.add_edge( 0, 1);
        g.add_edge( 0, 4);
        g.add_edge(  1, 2);
        g.add_edge( 1, 3);
        g.add_edge( 1, 4);
        g.add_edge( 2, 3);
        g.add_edge( 3, 4);

        g.print();
    }
}
