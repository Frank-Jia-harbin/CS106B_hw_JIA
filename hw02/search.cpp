// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"
#include "testing/SimpleTest.h"
using namespace std;


// TODO: This function is to 1.remove the punctuation in begin and end
//                           2. if there are no letter return null
//                           3.convert to little written pattern
string cleanToken(string s)
{
    while(ispunct(s[0])){
        s.erase(0,1);
    }                                //首尾标点符号去除
    while(ispunct(s[s.length()-1])){
        s.erase(s.length()-1,1);
    }

    bool letterExist = false;
    for(int i =0;i<s.length();i++){
        if(isalpha(s[i])){
            letterExist = true;
        }
    }
    if(!letterExist){
        return "";
    }

    return toLowerCase(s);
}

// TODO: This function is to get all nonrecur words.
Set<string> gatherTokens(string text)
{
    Set<string> tokens;
    Vector<string> wordSpilt;
    wordSpilt = stringSplit(text," ");
    for(string &elem:wordSpilt){
        string oneWord = cleanToken(elem);
        if (!tokens.contains(oneWord) && oneWord!=""){
            tokens.add(oneWord); //不包含并且非空字符就添加
        }
    }
    return tokens;
}

// TODO: This function is to 读取数据库内容并处理为反向索引的形式。
int buildIndex(string dbfile, Map<string, Set<string>>& index)
{
    ifstream in;

    if (!openFile(in, dbfile))
        error("Cannot open file named " + dbfile);

    Vector<string> lines;
    readEntireFile(in, lines);

    /* Now that the 网址和字符串 has been read into the Vector, populate
     * the maze grid.对字符串进行处理 处理偶数行。
     */
    int numRows = lines.size();
    Set<string> temporay;//临时中间变量 用于存放index中key对应的value
    for(int i=1;i<numRows;i=i+2){
        for(string elem:gatherTokens(lines[i])){
            if(!index.containsKey(elem)){
                temporay.add(lines[i-1]); //将elem和temporay连接起来
                index.put(elem,temporay);
            }
            if(!index.get(elem).contains(lines[i-1])){
                temporay = index.get(elem);
                temporay.add(lines[i-1]);//将已经有了key的elem移除，并重新建立索引
                index.remove(elem);
                index.put(elem,temporay);
            }
            temporay.clear();
        }
    }
    // rows is count of lines
//    int numCols = lines[0].length();   // cols is length of line
//    maze.resize(numRows, numCols);     // resize grid dimensions
    return lines.size()/2; //感觉不该这么写
}

// TODO: This function is to 输入搜索词（单个或多个）返回网址
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query){
    Set<string> result;
    Vector<string> keyword = stringSplit(query," ");
    for(string elem:keyword){
        if (elem.at(0) != '+' && elem.at(0) !='-' ){
            result.unionWith(index.get(elem));
        }
        if(elem.at(0) == '+'){
            elem.erase(0,1);
            result.intersect(index.get(elem));
        }
        if(elem.at(0) == '-'){
            elem.erase(0,1);
            result.difference(index.get(elem));
        }
    }
    // TODO: your code here
    return result;
}

// TODO: This function is to 构建一个搜索引擎
void searchEngine(string dbfile)
{
    // TODO: your code here
    Map<string, Set<string>> index;

    Set<string> URLs;
    cout << "Stand by while building index..."<<endl;
    cout << "Indexed " << buildIndex(dbfile, index) << " pages containing " << index.size() <<" unique terms"<<endl;
    string someKeywords = getLine("Enter query sentence (RETURN/ENTER to quit):");

    while(someKeywords !="" ){
        URLs = findQueryMatches(index, someKeywords);
        cout << "found " << URLs.size() << " mathching pages" << endl;
        cout << URLs << endl;
        someKeywords = getLine("Enter query sentence (RETURN/ENTER to quit):");
        URLs.clear();
    }
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on strings with no punctuation at beginning or end") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS*106B"), "cs*106b");
}

PROVIDED_TEST("cleanToken on strings with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
}

PROVIDED_TEST("cleanToken on non-word strings (no letters)"){
    EXPECT_EQUAL(cleanToken("106"), "");
    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs*106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 5 unique words, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 5);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 11);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here

STUDENT_TEST("cleanToken on strings with no letter or null") {
    EXPECT_EQUAL(cleanToken("!@#!#@#"), "");
    EXPECT_EQUAL(cleanToken(""), "");
}

STUDENT_TEST("cleanToken on strings with more than one punctua at beginning and end") {
    EXPECT_EQUAL(cleanToken("/??hello//"), "hello");

}
STUDENT_TEST("gatherTokens deal with nonletter") {
    Set<string> expected = {};
    EXPECT_EQUAL(gatherTokens("@#@#!192929 002029 213 //"), expected);
}
STUDENT_TEST("gatherTokens deal with nonletter") {
    Set<string> expected = {};
    EXPECT_EQUAL(gatherTokens(""), expected);
}
STUDENT_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;

    TIME_OPERATION(100,buildIndex("res/website.txt", index));
}
STUDENT_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 11);
    EXPECT_EQUAL(index.get("fish"),{"www.shoppinglist.com","www.dr.seuss.net","www.bigbadwolf.com"});
}

STUDENT_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}




