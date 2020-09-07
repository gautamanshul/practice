#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <stack>

namespace dfs_itr {
    class graph {
    private:
        std::vector<boost::shared_ptr<std::list<int>>> adj;
        std::stack<int> st;
        std::vector<bool> visited;
    public:
        graph(int v);

        void add_edge(int src, int dst);

        void dfs_util(int v);
    };

    graph::graph(int v) {
        adj.resize(v);
        std::for_each(adj.begin(), adj.end(), [](boost::shared_ptr<std::list<int>> &p) {
            p = boost::make_shared<std::list<int>>();
        });

        visited.resize(v, false );
    }

    void graph::add_edge(int src, int dst) {
        adj[src]->push_back(dst);
    }

    void graph::dfs_util(int v) {

        st.push(v);
        while (!st.empty()) {
            v = st.top();
            st.pop();

            if (!visited[v]) {
                std::cout << v << " ";
                visited[v] = true;
            }
            /// Explore the adjacent vertices.
            ///
            for_each(adj[v]->begin(), adj[v]->end(), [&](int &node) {
                if (!visited[node])
                    st.push(node);
            });
        }
    }
    int main()
    {
        dfs_itr::graph g(5); // Total 5 vertices in graph
        g.add_edge(1, 0);
        g.add_edge(0, 2);
        g.add_edge(2, 1);
        g.add_edge(0, 3);
        g.add_edge(1, 4);

        std::cout << "Following is Depth First Traversal\n";
        g.dfs_util(0);

        return 0;
    }

}
