/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "testing/SimpleTest.h"
using namespace std;


/*
 * TODO: 判断是否一段队列的整数为从小到大
 * input：一个数组
 * output：真或假
 */

bool binaryFalse(Queue<int> binary){
    int binarySize = binary.size();
    for(int i=0;i< binarySize-1 ;i++){
        if(binary.dequeue() > binary.peek()){
            return true;
        }
    }
    return false;
}



/*
 * TODO: 这个函数将两个队列的数值从小到大合并到一个队列中，（输入数列本身排列也是从小到大的）
 * input：两个从小到大排列的数组
 * output：一个从小到大排列的数组
 */




Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    Queue<int> result;
        if(a.isEmpty()){
            return b;
        }
        if(b.isEmpty()){
            return a;
        }
        if(binaryFalse(a)||binaryFalse(b)){
            error("无序排列");
        }
    while(!a.isEmpty() && !b.isEmpty()){
        if(a.peek() > b.peek()){
            result.enqueue(b.dequeue());
        }else if(a.peek() < b.peek()){
            result.enqueue(a.dequeue());
        }else if(a.peek() == b.peek()){
            result.enqueue(a.dequeue());
            result.enqueue(b.dequeue());
        }
    }
    while(a.isEmpty() &&!b.isEmpty()){
        result.enqueue(b.dequeue());
    }
    while(!a.isEmpty() &&b.isEmpty()){
        result.enqueue(a.dequeue());
    }
    return result;
//    if(a.isEmpty()){
//        return b;
//    }
//    if(b.isEmpty()){
//        return a;
//    }
//    if(binaryFalse(a)||binaryFalse(b)){
//        error("无序排列");

//    }
//    int sizea = a.size();

//    for(int i=0;i<sizea;i++){
//        int value1 = a.dequeue();
////        if(i!=sizea-1 && value1 > a.peek()){
////            error("队列1不合理");
////        }
//        int sizeB = b.size();
//        bool change = false;
//        for(int j=0;j < sizeB;j++){
//            int value2 = b.dequeue();
////            if(j!=sizeB-1 && value2 > b.peek()){
////                error("队列2不合理");
////            }
//            if(value1 >= value2 && value1 <=b.peek() && change == false){
//                b.enqueue(value2);
//                b.enqueue(value1);
//                change = true;
//            }else if(value1 <= value2 && change == false){
//                b.enqueue(value1);
//                b.enqueue(value2);
//                change = true;
//            }else if(j==sizeB-1 && value1 >= value2 && change == false){
//                b.enqueue(value2);
//                b.enqueue(value1);
//                change = true;
//            }else{
//                b.enqueue(value2);
//            }
//        }
//    }
//    result = b;
    /* TODO: Implement this function. */

}
STUDENT_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 3, 4};
    Queue<int> b = {};
    Queue<int> expected = {2, 3, 4};
    EXPECT_NO_ERROR(binaryMerge(a, b));
    EXPECT_EQUAL(binaryMerge(a, b),expected);

}
STUDENT_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 3};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_ERROR(binaryMerge(a, b));
    EXPECT_ERROR(binaryMerge(b, a));
}
STUDENT_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 3, 3};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 3, 3};
    EXPECT_EQUAL(binaryMerge(a, b),expected);
    EXPECT_NO_ERROR(binaryMerge(a, b));
}
STUDENT_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 3, 3};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 3, 3};
    EXPECT_EQUAL(binaryMerge(a, b),expected);
    EXPECT_NO_ERROR(binaryMerge(a, b));
}


/*
 * This function assumes correct functionality of the previously
 * defined binaryMerge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented –
 * it does not need to modified at all.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

STUDENT_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_NO_ERROR(naiveMultiMerge(all));
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{},
                             {},
                             {5},
                             {},
                             {-5, -5},
                             {}
                            };
    Queue<int> expected = {-5, -5, 5};
    EXPECT_NO_ERROR(naiveMultiMerge(all));
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}


/*
 * TODO: 使用递归方法来将K个序列的向量分成两半
 * header comment.
 */
Queue<int> recMultiMerge(Vector<Queue<int>> &all) {
    Queue<int> result;
    Queue<int> result1;
    Queue<int> result2;

    if(all.size()==2){
        result = binaryMerge(all.get(0),all.get(1));
    }else if(all.size() == 1){
        result = all.get(0);
    }
    else{
        if(all.size() % 2 == 0){//偶数部分
            Vector<Queue<int>> allLeft = all.subList(0,all.size()/2);
            Vector<Queue<int>> allRight = all.subList(all.size()/2,all.size()/2);
            result1 = recMultiMerge(allLeft);
            result2 = recMultiMerge(allRight);
            result = binaryMerge(result1,result2);
        }else{//奇数部分
            Vector<Queue<int>> allLeft = all.subList(0,(all.size()-1)/2);
            Vector<Queue<int>> allRight = all.subList((all.size()-1)/2,(all.size()+1)/2);
            result1 = recMultiMerge(allLeft);
            result2 = recMultiMerge(allRight);
            result = binaryMerge(result1,result2);

        }
    }
    /* TODO: Implement this function. */
    return result;
}


STUDENT_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(recMultiMerge(all), expected);
}

/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}
STUDENT_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}


/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}
