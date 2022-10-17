/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

/*
 * TODO: 接收一个字符串并返回只包含括号操作符的字符串。
 * input：一个随便的字符串
 * ouput：返回其中的括号
 */
string operatorsFrom(string str) {
    if (str.empty()) {
            return "";
        }else{
            if(startsWith(str,'[')||startsWith(str,']')||startsWith(str,'(')||startsWith(str,')')||startsWith(str,'{')||startsWith(str,'}')) {
            return  str[0] + operatorsFrom(str.substr(1));
            }
            return operatorsFrom(str.substr(1));
        }
}
/*Test case
 *
 */
STUDENT_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
    EXPECT_EQUAL(operatorsFrom("vec"), "");//边界测试
    EXPECT_EQUAL(operatorsFrom("{}{}[]]]{"), "{}{}[]]]{");//边界测试
}


/*
 * TODO: 判断字符串中的括号是否平衡
 * input：一个包含多个括号的字符串
 * output：判断字符串的括号是否是平衡的
 */
bool operatorsAreMatched(string ops) {
    /* TODO: Implement this function. */
    if(ops.empty()){
        return true;
    }else{
        if(stringContains(ops,"()")){
            return operatorsAreMatched(ops.erase(stringIndexOf(ops,"()"),2));
        }else if (stringContains(ops,"[]")){
            return operatorsAreMatched(ops.erase(stringIndexOf(ops,"[]"),2));
        }else if (stringContains(ops,"{}")){
            return operatorsAreMatched(ops.erase(stringIndexOf(ops,"{}"),2));
        }else{
            return false;
        }
    }
}

/*
 * Test case
 */
STUDENT_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
    EXPECT(!operatorsAreMatched("{[[)]}"));
    EXPECT(!operatorsAreMatched("asd"));
    EXPECT(operatorsAreMatched(""));
    EXPECT(operatorsAreMatched("((([[()]]))){{}}"));
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}
