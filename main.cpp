#include <list>
#include <iostream>
#include <vector>
#include <boost/make_shared.hpp>

namespace mother {
    class graph {
    private:
        int v; // no of vertices

        std::vector<boost::shared_ptr<std::list<int>>> adj; // adjacency list
        void dfs_util(int i, std::vector<bool> &visited);

    public:
        graph(int v);

        void add_edge(int v, int w);

        int find_mother();
    };

    graph::
    graph(int v) {
        adj.resize(v);
        for (int i = 0; i < adj.size(); ++i)
            adj[i] = boost::make_shared<std::list<int>>();
        this->v = v;
    }

    void
    graph::
    add_edge(int v, int w) {
        // if ( adj[v] == nullptr )
        //     adj[v] = boost::make_shared<std::list<int>>();
        adj[v]->push_back(w);
    }

///
    void
    graph::
    dfs_util(int i, std::vector<bool> &visited) {
        std::cout << "vertex is: " << i << std::endl;
        visited[i] = true;
        for (std::list<int>::iterator it = adj[i]->begin();
             it != adj[i]->end(); ++it) {
            if (!visited[*it]) {
                std::cout << "Itr is: " << *it << std::endl;
                dfs_util(*it, visited);
            }
        }
    }

    int
    graph::find_mother() {
        int j = 0;
        std::vector<bool> visited(v, false);

        for (int i = 0; i < v; i++) {
            if ( !visited[i]) {
                dfs_util(i, visited);
                j = i;
            }
        }
        std::cout << "Indx is: " << j << std::endl;
        std::fill(visited.begin(), visited.end(), false);
        dfs_util(j, visited);
        for (int i = 0; i < v; i++) {
            if (visited[i] == false)
                return -1;
        }
        return j;
    }

    int main() {

        mother::graph g(7);
        g.add_edge(0, 1);
        g.add_edge(0, 2);
        g.add_edge(1, 3);
        g.add_edge(4, 1);
        g.add_edge(6, 4);
        g.add_edge(5, 6);
        g.add_edge(5, 2);
        g.add_edge(6, 0);

        std::cout << "Mother is: " << g.find_mother() << std::endl;
        return 0;
    }
}

