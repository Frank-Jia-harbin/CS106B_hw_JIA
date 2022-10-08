// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "maze.h"
#include "mazegraphics.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;


/* TODO: Find all neiborhood position of current position.
 * 寻找当前位置的所有相邻位置的函数
 */
Set<GridLocation> generateValidMoves(Grid<bool>& maze, GridLocation cur) {
    Set<GridLocation> neighbors;

    /* TODO: Fill in the remainder of this function. */

//穷举所有边界条件
//    if (cur.row == 0 & cur.col ==0){
//        neighbors = {{1,0},{0,1}};
//    }
//    else if(cur.row ==0 & cur.col !=0){
//        neighbors = {{1,cur.col},{0,cur.col+1},{0,cur.col-1}};
//    }
//    else if(cur.row !=0 & cur.col ==0){
//        neighbors = {{cur.row,1},{cur.row+1,0},{cur.row-1,0}};
//    }
//    else if(cur == exit){
//        neighbors = {{cur.row-1,cur.col},{cur.row,cur.col-1}};
//    }
//    else if(cur.row ==exit.row & cur.col !=exit.col){
//        neighbors = {{exit.row-1,cur.col},{exit.row,cur.col+1},{exit.row,cur.col-1}};
//    }
//    else if(cur.row !=exit.row& cur.col == exit.col){
//        neighbors = {{cur.row,exit.col-1},{cur.row+1,exit.col},{cur.row-1,exit.col}};
//    }
//    else{
//    neighbors = {{cur.row,cur.col - 1},{cur.row - 1,cur.col},{cur.row + 1,cur.col},{cur.row,cur.col + 1}};
//    }
// 斯坦福库有判断边界函数（stanford have a funciton to judge the boundary）
    Set<GridLocation>neighbors_all = {{cur.row,cur.col - 1},{cur.row - 1,cur.col},{cur.row + 1,cur.col},{cur.row,cur.col + 1}};//还未判断的四个位置点
    for (GridLocation elem:neighbors_all){
        if (maze.inBounds(elem) && maze.get(elem)){      //是否在边界内 AND 逻辑值为真
            neighbors.add(elem);
        }
    }
    return neighbors;
}

/* TODO: This function is to validate the path is the good path from the begin to the end
 * header comment.
 */
void validatePath(Grid<bool>& maze, Stack<GridLocation> path) {
    GridLocation mazeExit = {maze.numRows()-1,  maze.numCols()-1};
    GridLocation mazeBegin = {0,  0};

    if(maze.isEmpty()){
        error("This is a null ");
    }
    if (path.peek() != mazeExit) {
        error("Path does not end at maze exit");
    }
    int n = path.size();

    Set<GridLocation> path_old;//记录栈中的所有路径点并保存为Set

    path_old.add(path.peek());

    for(int i=1;i<n;i++){
        if(!generateValidMoves(maze, path.pop()).contains(path.peek())){
            error("Each step must be a regular move"); //判断栈第二层元素是否是第一层元素的有效移动
        }
        if (i==n-1 && path.peek() != mazeBegin) {
            error("Path does not begin at maze begin"); //判断栈最底下的元素是否是迷宫的起点
        }
        if(path_old.contains(path.peek())){
            error("Path can not be 重复");//判断之前保存的路径点（已经pop出去的）是否包含现在栈中第一个路径点，如果包含即有重复路径
        }
        path_old.add(path.peek());
    }




    /* TODO: Fill in the remainder of this function. */

    /* If you find a problem with the path, call error() to report it.
     * If the path is a valid solution, then this function should run to completion
     * without throwing any errors.
     */
}

/* TODO: This function is to find the shortest path from the begin to the end.
 * 从1逐步变大，去搜寻最短的迷宫解
 *
 */
Stack<GridLocation> solveMaze(Grid<bool>& maze) {
    MazeGraphics::drawGrid(maze);
    Stack<GridLocation> path;
    Queue<Stack<GridLocation>> path_all;//所有可能路径的队列
    GridLocation mazeExit = {maze.numRows()-1,  maze.numCols()-1};
    path_all.enqueue({{0,0}}); //初始化迷宫入口

    while(!path_all.isEmpty()){
        GridLocation cur = path_all.peek().peek();

        for (GridLocation point_new:generateValidMoves(maze, cur)){  //遍历周围的点
            if (point_new == mazeExit){
                path = path_all.peek();//如果周围点有出口点，那么就把当前的路径加上point_new输出
                path.push(point_new);
                return path;
            }
            path = path_all.peek();
            path.pop();//取出当前点以便于观察前一个是否重复
            if(!path.isEmpty()){//边界条件 第一步时
                if(path.peek() != point_new){
                    path.push(cur);                 //回头现象，必定在位置n和位置n+2处进行重合，先吐出一个，就可以将n处和n+2处进行判断是否相等
                    path.push(point_new);
                    path_all.enqueue(path);         //如果不相等就还原并加入新的point，并加入到path_all 总路径中待处理
                    path.clear();
                }
                else{
                    path.push(cur);                 //如果相等 就还原 然后待处理
                }
            }
            else{
                path.push(cur);                      //如果取出一个之后，路径就空了，那么必定没有重复的，属于初始阶段。
                path.push(point_new);
                path_all.enqueue(path);
                path.clear();
            }

        }
        MazeGraphics::highlightPath(path_all.peek(),"red", 1000);            //高亮显示当前操作的一个路径
        path_all.dequeue(); //剔除当前的路径

    }
    /* TODO: Fill in the remainder of this function. */
    return path;
}

/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readMazeFile(string filename, Grid<bool>& maze) {
    /* The following code reads data from the file into a Vector
     * of strings representing the lines of the file.
     */
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines;
    readEntireFile(in, lines);

    /* Now that the file data has been read into the Vector, populate
     * the maze grid.
     */
    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    for (int r = 0; r < numRows; r++) {
        if (lines[r].length() != numCols) {
            error("Maze row has inconsistent number of columns");
        }
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            } else {
                error("Maze location has invalid character: '" + charToString(ch) + "'");
            }
        }
    }
}

/* The given readSolutionFile correctly reads a path from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readSolutionFile(string filename, Stack<GridLocation>& soln) {
    ifstream in;

    if (!openFile(in, filename)) {
        error("Cannot open file named " + filename);
    }

    if (!(in >> soln)) {// if not successfully read
        error("Maze solution did not have the correct format.");
    }
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("generateValidMoves on location in the center of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation center = {1, 1};
    Set<GridLocation> expected = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, center), expected);
}

PROVIDED_TEST("generateValidMoves on location on the side of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation side = {0, 1};
    Set<GridLocation> expected = {{0,0}, {0,2}, {1, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, side), expected);
}

PROVIDED_TEST("generateValidMoves on corner of 2x2 grid with walls") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    GridLocation corner = {0, 0};
    Set<GridLocation> expected = {{1, 0}};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}

PROVIDED_TEST("validatePath on correct solution") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Stack<GridLocation> soln = { {0 ,0}, {1, 0}, {1, 1} };

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on correct solution loaded from file for medium maze") {
    Grid<bool> maze;
    Stack<GridLocation> soln;
    readMazeFile("res/5x7.maze", maze);
    readSolutionFile("res/5x7.soln", soln);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on correct solution loaded from file for large maze") {
    Grid<bool> maze;
    Stack<GridLocation> soln;
    readMazeFile("res/25x33.maze", maze);
    readSolutionFile("res/25x33.soln", soln);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on invalid path should raise error") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Stack<GridLocation> not_end_at_exit = { {1, 0}, {0, 0} };
    Stack<GridLocation> not_begin_at_entry = { {1, 0}, {1, 1} };
    Stack<GridLocation> go_through_wall = { {0 ,0}, {0, 1}, {1, 1} };
    Stack<GridLocation> teleport = { {0 ,0}, {1, 1} };
    Stack<GridLocation> revisit = { {0 ,0}, {1, 0}, {0, 0}, {1, 0}, {1, 1} };

    EXPECT_ERROR(validatePath(maze, not_end_at_exit));
    EXPECT_ERROR(validatePath(maze, not_begin_at_entry));
    EXPECT_ERROR(validatePath(maze, go_through_wall));
    EXPECT_ERROR(validatePath(maze, teleport));
    EXPECT_ERROR(validatePath(maze, revisit));
}

PROVIDED_TEST("solveMaze on file 5x7") {
    Grid<bool> maze;
    readMazeFile("res/5x7.maze", maze);
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("solveMaze on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

// TODO: add your test cases here

STUDENT_TEST("for no way to go") {
    Grid<bool> maze = {{true, false,false},
                       {true, false, true},
                       {true,false,false}};
    GridLocation corner = {1, 2};
    Set<GridLocation> expected = {};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}
STUDENT_TEST("for null maze") {
    Grid<bool> maze = {};
    GridLocation corner = {0,0};
    Set<GridLocation> expected = {};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}
STUDENT_TEST("for non equal row and col") {
    Grid<bool> maze = {{true, false},
                       {true, true},
                       {true,false}};
    GridLocation corner = {0, 1};
    Set<GridLocation> expected = {{0, 0},{1,1}};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}

STUDENT_TEST("validatePath on false solution loaded from file for small maze") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Stack<GridLocation> soln = { {0 ,0}, {0, 1}, {1, 1} };

    EXPECT_ERROR(validatePath(maze, soln));
}
STUDENT_TEST("validatePath on correct solution loaded from file for 重复路线") {
    Grid<bool> maze;
    Stack<GridLocation> soln;
    readMazeFile("res/17x37.maze", maze);
    readSolutionFile("res/17x37_copy.soln", soln);

    EXPECT_ERROR(validatePath(maze, soln));
}
STUDENT_TEST("validatePath on correct solution loaded from file for null path") {
    Grid<bool> maze = {};
    Stack<GridLocation> soln = {};

    EXPECT_ERROR(validatePath(maze, soln));
}
STUDENT_TEST("solveMaze on file 2x2") {
    Grid<bool> maze;
    readMazeFile("res/2x2.maze", maze);  //边界测试
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

void stress_test(Grid<bool>& maze,int calNumber){
    for (int i = 1;i<calNumber;i++){
        solveMaze( maze);

    }
}

STUDENT_TEST("stress") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    TIME_OPERATION(100  ,stress_test(maze,100));
}
