#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <queue>
#include <array>
namespace maze {
    class graph {
    public:
        graph(int row, int columns); /// Create a matrix of Row x Column
        void update_cell(int row, int column, int value); /// Update the cell value

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
        bool reached_end;
        /// Direction vectors north, south, east and west
        std::array<int, 4> dr;
        std::array<int, 4> dc;
    };

    graph::graph(int rows, int columns) :
        move_count( 0 ),
        nodes_left_in_layer(1),
        nodes_in_next_layer(0),
        reached_end(false)
        {
        dr = {-1, 1, 0, 0};
        dc = { 0, 0, 1, -1};
        maze.resize(rows); /// Resize to number of rows
        std::for_each(maze.begin(), maze.end(),
                      [&](boost::shared_ptr<std::vector<int>> &col) /// Add columns
                      {
                          col->resize(columns, -1); /// initialize each cell with -1
                      });

        visited.resize(rows); /// Resize to number of rows
        std::for_each(maze.begin(), maze.end(),
                [&](boost::shared_ptr<std::vector<bool>> &col) /// Add columns
            {
                col->resize(columns, false); /// initialize each cell with false
            });

        }

    void graph::update_cell(int row, int column, int value) {
        maze[row]->at(column) = value;
    }

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
    g.update_cell(0,0,1);
    g.update_cell(0,0,1);
    g.update_cell(0,0,1);
}



