/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "recursion.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * This function draws a filled, black triangle on the provided GWindow
 * that is defined by the corner GPoints one, two, and three. This
 * function has been provided for you and does not need to be modified.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

/*
 * TODO: 绘制一个有着三个定点和指定order定义的Sierpinski三角形
 * input：三个顶点和order
 * output：
 */
int drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    /* TODO: Implement this function. */
    if(order == 0){
        fillBlackTriangle( window,  one, two, three);
    }else{
        GPoint twoThree((three.x+two.x)/2,(three.y+two.y)/2);
        GPoint oneThree((three.x+one.x)/2,(three.y+one.y)/2);//按照顺序来确定下一次的点
        GPoint oneTwo((one.x+two.x)/2,(one.y+two.y)/2);
        drawSierpinskiTriangle(window, one, oneTwo, oneThree, order-1);
        drawSierpinskiTriangle(window, oneTwo, two, twoThree, order-1);
        drawSierpinskiTriangle(window, oneThree, twoThree, three, order-1);
    }
    return 0;
}


/* * * * * * Test Cases * * * * * */

/*
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all testing
 * via the interactive demo.
 */

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runInteractiveDemo();
}

