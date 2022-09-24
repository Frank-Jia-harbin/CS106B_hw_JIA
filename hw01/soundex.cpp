/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
#include "soundex.h"


using namespace std;


/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string removeNonLetters(string s) {
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}
/*
 * This function means to convert every letter to number
 */
string judgeGroup(char character){
//    string string0 = "AEIOUHWY";
//    string string1 = "BFPV";
//    string string2 = "CGJKQSXZ";
//    string string3 = "DT";
//    string string4 = "L";
//    string string5 = "MN";
//    string string6 = "R";
//    string::size_type idx;
    if(isalpha(character)){
          character = toUpperCase(character);
       }
    switch(character){
    case 'A':case'E':case'I':case'O':case'U':case'H':case'W':case'Y':
        return "0";
    case 'B':case'F':case'P':case'V':
        return "1";
    case 'C':case'G':case'J':case'K':case'Q':case'S':case'X':case'Z':
        return "2";
    case 'D':case'T':
        return "3";
    case 'L':
        return "4";
    case 'M':case'N':
        return "5";
    case 'R':
        return "6";
    }
    return 0;
/*
//    int i;
//    if(isalpha(character)){
//        character = toUpperCase(character);
//    }
//    vector<char> vec0 = {'A','E','I','O','U','H','W','Y'};
//    vector<char> vec1 = {'B','F','P','V'};
//    vector<char> vec2 = {'C','G','J','K','Q','S','X','Z'};
//    vector<char> vec3 = {'D','T'};
//    vector<char> vec4 = {'L'};
//    vector<char> vec5 = {'M','N'};
//    vector<char> vec6 = {'R'};
//    for(i = 0; i < vec0.size(); i++){
//        if(character == vec0[i]){
//            return "0";
//        }
//    }
//    for(i = 0; i < vec1.size(); i++){
//        if(character == vec1[i]){
//            return "1";
//        }
//    }
//    for(i = 0; i < vec2.size(); i++){
//        if(character == vec2[i]){
//            return "2";
//        }
//    }
//    for(i = 0; i < vec3.size(); i++){
//        if(character == vec3[i]){
//            return "3";
//        }
//    }
//    for(i = 0; i < vec4.size(); i++){
//        if(character == vec4[i]){
//            return "4";
//        }
//    }
//    for(i = 0; i < vec5.size();i++){
//        if(character == vec5[i]){
//            return "5";
//        }
//    }
//    for(i = 0; i < vec6.size(); i++){
//        if(character == vec6[i]){
//            return "6";
//        }
//    }
//    return 0;
*/
}


/*
 * This function means to remove the repetitive letters
 */
string removeSameLetters(string q ){
    int i;
    for (i = q.length() - 1;i>0;i--){
        if(q[i] == q[i-1]){
            q.erase(i,1);
        }
    }
    return q;
}

/*
 * This function is to make the string constranted in  four element.
 */
string fourNumbers(string q){

    if (q.length() >= 4){
        return q.substr(0,4);
    }
    else                {
        int i;
        int k = q.length();
        for(i=1;i <= 4 - k; i++){
            q.append("0");
        }
        return q;
    }
return 0;

}
/*
 * THis function means to remove all the zero element of input.
 */
string removeZero(string q){
//    if(q.rfind("0")){
//        q = q.erase(q.rfind("0"),1);
//        q = removeZero(q);
//    }else{
//        return q;
//    }
    while(q.rfind("0") && q.rfind("0") != q.npos){
        q = q.erase(q.rfind("0"),1);
    }

return q;
}
/*
 * This function means to convert all the letter to number
 */
string convertToNumber(string s){
    int i;
    string q;
    for(i=0;i<s.length();i++){
        q.append(judgeGroup(s[i]));
    }
    return q;
}
/*
 * This function means to find the first letter of a string and return its upper.
 */
//string findFirstLetter(string s){
//    int i;
//    for(i = 0; i < s.length();i++){
//        if(isalpha(tolower(s[i]))){
//            return toUpperCase(charToString(s[i]));
//        }
//    }
//    return "";
//}


/* TODO: This function means to deal with the inputing name to convert soundex step by step.
 * header comment.
 */
string soundex(string s) {
    /* TODO: Fill in this function. */
    string q = "";
    s = removeNonLetters(s);
    string first = toUpperCase(s.substr(0,1));
    q = convertToNumber(s);
    q = removeSameLetters(q);
    q.replace(0, 1, first);
    q = removeZero(q);
    q = fourNumbers(q);


    //cout << "q[i]" << q <<endl;
    return q;

}


/* TODO: This function using existed database to compare with inputting, it will return the name which have same soundex.
 *
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    string surName;
    Vector<string> databaseNames;
    Vector<string> sameNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames

    /* TODO: Fill in the remainder of this function. */

    string line = getLine("Enter a surname(Return to quit)");
    while(line != ""){
        surName = soundex(line);
        cout << "Soundex code is " << surName << endl;
        int i;
        for(i = 0;i <= databaseNames.size() - 1; i++ ){
            if(surName == soundex(databaseNames[i])){
                sameNames.add(databaseNames[i]);
            }
        }
        sameNames.sort();
        cout << "Matches from database: " << sameNames << endl << endl;
        line = getLine("Enter a surname(Return to quit)");
        sameNames.clear();

    }

}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here
STUDENT_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");

    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");

    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");

    s = " ABC";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "ABC");

    s = "";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "");

}



STUDENT_TEST("Test can a letter be redirect to a number") {

    EXPECT_EQUAL(judgeGroup('a'), "0");
    EXPECT_EQUAL(judgeGroup('b'), "1");

    EXPECT_EQUAL(judgeGroup('F'), "1");
    EXPECT_EQUAL(judgeGroup('A'), "0");


}

STUDENT_TEST("Test can a string can be convert to number") {

    EXPECT_EQUAL(convertToNumber("jack") , "2022");
    EXPECT_EQUAL(convertToNumber("B") , "1");
    EXPECT_EQUAL(convertToNumber("") , "");


}

STUDENT_TEST("Test can the nunber be removed the repetitive") {

    EXPECT_EQUAL(removeSameLetters("300256") , "30256");
    EXPECT_EQUAL(removeSameLetters("0322556") , "03256");
    EXPECT_EQUAL(removeSameLetters("003321") , "0321");
    EXPECT_EQUAL(removeSameLetters("3332") , "32");
    EXPECT_EQUAL(removeSameLetters("3333") , "3");

}

STUDENT_TEST("make the number be four"){

    EXPECT_EQUAL(fourNumbers("30232321"), "3023");//normal test
    EXPECT_EQUAL(fourNumbers("30"), "3000");
    EXPECT_EQUAL(fourNumbers("3"), "3000");
    EXPECT_EQUAL(fourNumbers(""), "0000");//edge test
}

//STUDENT_TEST("find the first number"){

//    EXPECT_EQUAL(findFirstLetter("033A"), "A");
//    EXPECT_EQUAL(findFirstLetter("Basd"), "B");
//    EXPECT_EQUAL(findFirstLetter("0100203"), "");
//    EXPECT_EQUAL(findFirstLetter(" 2A"), "A");
//}



STUDENT_TEST("finally test"){
    EXPECT_EQUAL(soundex("Curie") ,"C600");
    EXPECT_EQUAL(soundex("O'Conner") ,"O256");
    EXPECT_EQUAL(soundex("") ,"0000");
    EXPECT_EQUAL(soundex("003 **Cu rie") ,"C600");

}




