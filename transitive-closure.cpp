#include <vector>
#include <iostream>
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

/// Transitive closure is used to identify if a vertex v is reachable from a vertex u or not.
/// The reach-ability is called transitive closure
/// By using DFS, we traverse the nodes while
namespace closure {
    class graph {
    public:
        graph(int v);

        void add_edge(int src, int dst);

        void connections();

        void dfs_util(int src, int dst);

    private:
        std::vector<boost::shared_ptr<std::list<int>>> adj;
        std::vector<std::vector<bool>> visited;
    };

    graph::graph(int v) {
        adj.resize(v);
        visited.resize(v);
        std::for_each(visited.begin(), visited.end(),
                      [&](std::vector<bool> &p) { p.resize(v, false); });
        std::for_each(adj.begin(), adj.end(),
                      [](boost::shared_ptr<std::list<int>> &p) {
                          p = boost::make_shared<std::list<int>>();
                      });
    }

    void graph::dfs_util(int src, int dst) {
        visited[src][dst] = true;
        for (std::list<int>::iterator it = adj[dst]->begin();
             it != adj[dst]->end(); ++it) {
            if (!visited[src][*it]) {
                dfs_util(src, *it);
            }
        }
    }

    void graph::connections() {

        for (int i = 0; i < adj.size(); ++i) {
            dfs_util(i, i);
        }

        std::for_each(visited.begin(), visited.end(), [](std::vector<bool> &p) {
            std::for_each(p.begin(), p.end(), [](bool i) { std::cout << i << " "; });
            std::cout << "\n";
        });
    }

    void graph::add_edge(int src, int dst) {
        adj[src]->push_back(dst);
    }
    int main()
    {
        closure::graph g( 4 );
        g.add_edge(0, 1);
        g.add_edge( 0 , 2 );
        g.add_edge(1, 2 );
        g.add_edge(2, 0 );
        g.add_edge(2, 3);
        g.add_edge( 3, 3);

        std::cout << "transitive closure matrix is \n";
        g.connections();
        return 0;
    }

}

