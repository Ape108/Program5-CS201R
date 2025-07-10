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
/**
 PRE: The arr vector must be sorted in ascending alphabetical order, containing wordList elements. target is the string to be found.

 POST: Returns the index of target if found in arr; otherwise, it returns -1. The input parameters remain unchanged, and the function executes in O(log n) time.
 */

double sentimentVal(string in, vector<wordList> &words);
/**
 PRE: The function accepts a string in and a reference to a vector<wordList> named words.

 POST: Returns the sentiment value of the word if found in the words vector; otherwise, it returns 0.
 */

void   loadSentiment(vector<wordList>& sentList, vector<wordList>& posList, vector<wordList>& negList);
/**
 PRE: The function accepts three empty vector<wordList> references: sentList, posList, and negList.

 POST: The three vectors are loaded with data from the sentiment.txt file.
 */

void   processFile(ifstream& inFile, ofstream& outFile, string fileName,
                   vector<wordList>& words, vector<wordList>& posList, vector<wordList>& negList);
/**
 PRE: The function accepts an ifstream object inFile (the current review file) that has been opened and verified, an ofstream object outFile (where all reviews are posted) that has been opened and verified, a string containing the fileName, and three vector<wordList> references (words, posList, and negList) with the words loaded.

 POST: The inFile is reviewed, and the review's sentiment, along with more positive and more negative versions of the review (if possible), are output to outFile.
 */

void openForReview(int i, ofstream& outFile, vector<wordList>& sentList,
                   vector<wordList>& posList, vector<wordList>& negList);
/**
 PRE: The function accepts an integer i for the review number, an ofstream object outFile, and three vector<wordList> references (sentList, posList, and negList).

 POST: The corresponding review file is opened, processed by calling processFile, and then closed.
 */

void loadSentList(ifstream& inFile, vector<wordList>& sentList);
 /**
  PRE: The function accepts an ifstream object inFile that is open and a reference to a vector<wordList> named sentList.

  POST: The sentList vector is populated with wordList objects created from the data in the inFile.
  */


void sortWords(vector<wordList> sentList, vector<wordList>& posList,
               vector<wordList>& negList);
/**
 PRE: The function accepts a vector<wordList> named sentList and references to two vector<wordList> objects, posList and negList.

 POST: The posList and negList vectors are populated with words from sentList that have sentiment values greater than 1.25 and less than -1.25, respectively.
 */

void processList(ifstream& inFile,
                 vector<wordList>& words);
/**
 PRE: The function accepts an ifstream object inFile and a reference to a vector<wordList> named words.

 POST: The inFile is read word by word, and the sentiment of each word is analyzed and stored.*/

void resetValues(vector<wordList>& origWords,
                 vector<wordList>& negWords,
                 vector<wordList>& posWords,
                 vector<pair<string, wordList>>& origFullWords);
/**
 PRE: The function accepts references to three vector<wordList> objects (origWords, negWords, posWords) and a vector<pair<string, wordList>> named origFullWords.

 POST: All four input vectors are cleared of their elements.
 */

void originalReview(ofstream& outFile,
                    vector<pair<string, wordList>>& origFullWords,
                    double origScore);
/**
 PRE: The function accepts an ofstream object outFile, a vector<pair<string, wordList>> named origFullWords, and a double origScore.

 POST: The formatted original review and its sentiment score are written to the outFile.
 */

tuple<vector<pair<wordList, wordList>>, double, double,
      vector<pair<wordList, wordList>>, double, double> changeSentiment(double origScore,
                                                                        vector<wordList>& posWords,
                                                                        vector<wordList>& negWords,
                                                                        vector<wordList>& posList,
                                                                        vector<wordList>& negList);
/**
 PRE: The function accepts the original score as a double, and references to posWords, negWords, posList, and negList vectors.

 POST: Returns a tuple containing vectors of word pairs for more negative and more positive reviews, and their corresponding sentiment scores.
 */

void outputChanged(ofstream& outFile,
                   vector<pair<wordList, wordList>>& moreNeg,
                   vector<pair<wordList, wordList>>& morePos,
                   double& origScore,
                   double& beforeNeg,
                   double& beforePos,
                   double& afterNeg,
                   double& afterPos,
                   double& negScore,
                   double& posScore,
                   vector<pair<string, wordList>>& origFullWords);
/**
 PRE: The function accepts an ofstream object outFile, vectors of word pairs for more negative and positive reviews, the original score, and the before and after sentiment totals for both negative and positive changes.

 POST: The updated reviews (more negative and more positive) and their corresponding sentiment analysis are written to the outFile.
 */

void outputTable(ofstream& outFile,
                 vector<pair<wordList, wordList>> currentMore,
                 double currentBefore,
                 double currentAfter,
                 double currentScore,
                 string sentWord);

void writeReplacements(vector<pair<string, wordList>>& origFullWords,
                       vector<pair<wordList, wordList>>& currentMore,
                       ofstream& outFile);

void replaceWords(vector<wordList> currentWords,
                  vector<wordList> currentList,
                  double currentScore,
                  vector<pair<wordList, wordList>> currentMore,
                  double currentBefore,
                  double currentAfter);
