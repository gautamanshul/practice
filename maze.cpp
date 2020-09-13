#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <queue>
#include <array>
namespace maze {
    class graph {
    public:
        graph(int row, int columns); /// Create a matrix of Row x Column
        void update_cell(int row, int column, int value); /// Update the cell value
        int solve();
        void explore_neighbors( const int r, const int c); /// Explore neighbors of a cell
    private:
        int rows; // number of rows in the maze
        int columns; // number of columns in the maze
        std::vector<boost::shared_ptr<std::vector<int>>> maze;
        std::vector<boost::shared_ptr<std::vector<bool>>> visited; /// Track if a cell was visited
        std::queue<int> row_que; /// Row queue to track and explore row coordinate
        std::queue<int> col_que; /// Column queue to track and explore column coordinate

        /// Variables used to track the number of steps taken
        int move_count;
        int nodes_left_in_layer;
        int nodes_in_next_layer;
        int sr, sc; /// Symbol row and column values
        bool reached_end;
        /// Direction vectors north, south, east and west
        std::array<int, 4> dr;
        std::array<int, 4> dc;
    };

    graph::graph(int rows, int columns) :
        move_count( 0 ),
        nodes_left_in_layer(1),
        nodes_in_next_layer(0),
        reached_end(false),
        sr(0),
        sc( 0 )
        {
        dr = {-1, 1, 0, 0};
        dc = { 0, 0, 1, -1};
        maze.resize(rows); /// Resize to number of rows
        std::for_each(maze.begin(), maze.end(),
                      [&](boost::shared_ptr<std::vector<int>> &col) /// Add columns
                      {
                          col = boost::make_shared<std::vector<int>>();
                          col->resize(columns, -1); /// initialize each cell with -1
                      });

        visited.resize(rows); /// Resize to number of rows
        std::for_each(visited.begin(), visited.end(),
                [&](boost::shared_ptr<std::vector<bool>> & col) /// Add columns
            {
                col = boost::make_shared<std::vector<bool>>();
                col->resize(columns, false); /// initialize each cell with false
            });

        }

    void graph::update_cell(int row, int column, int value) {
        maze[row]->at(column) = value;
    }

    void graph::explore_neighbors( const int r, const int c)
    {
        for ( int i = 0; i < 4; i++ )
        {
            int rr = r + dr[i];
            int cc = c + dc[i];
            if ( rr < 0 || rr >= 5) continue;
            if ( cc < 0 || cc >= 7) continue;
            if ( visited[rr]->at(cc) ) continue;
            if ( maze[rr]->at(cc ) == '2') continue;

            row_que.push( rr );
            col_que.push( cc );
            visited[rr]->at(cc) = true;
            nodes_in_next_layer++;
        }
    }

    int graph::solve()
    {
        int r = -1, c = -1;
        /// Enqueue the first cell
        row_que.push(sr);
        col_que.push(sc);

        visited[sr]->at(sc) = true;
        while( row_que.size() > 0 ) /// While cells exist in queue for processing
        {
            r = row_que.front();
            c = col_que.front();
            row_que.pop();
            col_que.pop();
            if ( maze[r]->at(c) == 3 ) {
                reached_end = true;
                break;
            }
            explore_neighbors(r, c);
            nodes_left_in_layer--;
            if (nodes_left_in_layer == 0)
            {
                nodes_left_in_layer = nodes_in_next_layer;
                nodes_in_next_layer = 0;
                move_count++;
            }
        }
        if ( reached_end ) return move_count;
        return -1;
    }

    int main()
    {
        /// 1 - Cells to be explored
        /// 2 - End cell / Destination cell
        /// 3 - Can't be explored
        maze::graph g(5, 7);
        g.update_cell(0,0,1);
        g.update_cell(0,1,1);
        g.update_cell(0,2,1);
        g.update_cell(0,3,2);
        g.update_cell(0,4,1);
        g.update_cell(0,5,1);
        g.update_cell(0,6,1);
        g.update_cell(0,0,1);
        g.update_cell(1,0,1);
        g.update_cell(1,1,2);
        g.update_cell(1,2,1);
        g.update_cell(1,3,1);
        g.update_cell(1,4,1);
        g.update_cell(1,5,2);
        g.update_cell(1,6,1);
        g.update_cell(2,0,1);
        g.update_cell(2,1,2);
        g.update_cell(2,2,1);
        g.update_cell(2,3,1);
        g.update_cell(2,4,1);
        g.update_cell(2,5,1);
        g.update_cell(2,6,1);
        g.update_cell(3,0,1);
        g.update_cell(3,1,1);
        g.update_cell(3,2,2);
        g.update_cell(3,3,2);
        g.update_cell(3,4,1);
        g.update_cell(3,5,1);
        g.update_cell(3,6,1);
        g.update_cell(4,0,2);
        g.update_cell(4,1,1);
        g.update_cell(4,2,2);
        g.update_cell(4,3,3);
        g.update_cell(4,4,1);
        g.update_cell(4,5,2);
        g.update_cell(4,6,1);

        std::cout << g.solve() << std::endl;
    }

}




