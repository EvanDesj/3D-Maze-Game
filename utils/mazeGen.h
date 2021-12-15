/*
 * Maze Generator:
 *   Made by Jaden Peterson in 2016
 */

/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This program uses the Direct-First Search algorithm
 *   You can learn more about it at:
 *     https://en.wikipedia.org/wiki/Maze_generation_algorithm#Depth-first_search
 */

#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Maze_Path
{
private:
    int maze_size[2];

    int start_axis;
    int start_side;

    std::vector<std::vector<int>> dfs_path;

    /*
 * Structure of the maze vector:
 *                     |--> Filled in?
 *   Row --> Collumn --|
 *                     |--> Has been visited?
 */
    std::vector<std::vector<std::vector<bool>>> maze;
    bool randomMove(bool first_move);
    void normalizeInput();
    void initializeMaze();
    void setStart();
    void setEnd();
    void generateMaze();
    std::vector<std::vector<int>> convertOutput();

public:
    std::vector<std::vector<int>> getMaze(int size);
};

#endif