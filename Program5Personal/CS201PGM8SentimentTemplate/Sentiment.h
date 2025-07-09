#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

struct wordList {
    string word;
    double value;
};

struct replaceList {
    string origWord;
    double origValue;
    string newWord;
    double newValue;
};


int alphabeticalBinarySearch(const vector<wordList>& arr, const string& target);
//Binary Search Algorithm from Gemini LLM
//PRE: Vector arr must be sorted in ascending alphabetical order, containing string elements, with target as the string to find.
//POST: Returns the index of target if found in arr, otherwise returns -1, leaving both input parameters unchanged and executing in O(log n) time.


double sentimentVal(string in, vector<wordList> &words);
//SUPPORT FUNCTION TO FIND THE CURRENT WORD IN THE SENTEMENT VECTOR & RETURN THE SENTIMENT VALUE
//PRE:   accepts a string (in) and the words list
//POST:  returns the sentiment of the word if found or the value 0 if not

void   loadSentiment(vector<wordList>& sentList, vector<wordList>& posList, vector<wordList>& negList);
//PRE:   accepts an empty set of 3 <wordList> vectors
//POST:  loads all three vectors with data from sentiment.txt

void   processFile(ifstream& inFile, ofstream& outFile, string fileName,
                   vector<wordList>& words, vector<wordList>& posList, vector<wordList>& negList);
//PRE:   accepts the inFile (the current review file)  opened and verified in main 
//       the output file name (where all reviews are posted) opened and verified in main
//       a string containing the fileName (for printing to the output file)
//       and 3 <wordList> vectors with words loaded
//POST:  reviews the inFile and outputs to outFile the review sentiment, a more positive and more negative review (if possible)

void openForReview(int i, ofstream& outFile, vector<wordList>& sentList, vector<wordList>& posList, vector<wordList>& negList);

 
