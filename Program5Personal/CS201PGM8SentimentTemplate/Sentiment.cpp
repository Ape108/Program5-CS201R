#include "Sentiment.h"

int alphabeticalBinarySearch(const vector<wordList>& arr,
                             const string& target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid].word == target) {
            return mid;
        } else if (arr[mid].word < target) {
            left = mid + 1;
            continue;
        }
        right = mid - 1;
    
    }

    return -1; // Target not found
}

double sentimentVal(string in,
                    vector<wordList> &words) {
    
    int index = alphabeticalBinarySearch(words, in);
    if (index == -1) { // binary didn't return an index
        return 0;
    }
    // return value of word at that index
    return words[index].value;
}

void loadSentiment(vector<wordList>& sentList,
                   vector<wordList>& posList,
                   vector<wordList>& negList) {
    //open sentiment.txt
    ifstream inFile;
    inFile.open("sentiment.txt");
    if (!inFile.is_open()) {
        cout << "Error opening input file" << endl;
        exit(1); // Terminate program
    }
    cout << "\"sentiment.txt\" opened successfully." << endl;

    //add the words to the sentList vector
    loadSentList(inFile, sentList);
    
    inFile.close(); // Done with the input file.
    
    //sort positive and negative words
    sortWords(sentList, posList, negList);
}

void processFile(ifstream& inFile,
                 ofstream& outFile,
                 string fileName,
                 vector<wordList>& words,               // vectors containing the word & sentiment
                 vector<wordList>& posList,
                 vector<wordList>& negList) {
 
    string inWord, newWord, origWord;
    vector<wordList> origWords, negWords, posWords;
    vector<pair<string, wordList>> origFullWords; // Store original words with punctuation and case
    double origScore = 0, negScore = 0, posScore = 0;
    
    cout << "\nPROCESSING FILE: " << fileName << endl;
    outFile << "\n\nPROCESSING FILE: " << fileName << endl << endl;

    // reset all vectors & values before processing inFile
    resetValues(origWords, negWords, posWords, origFullWords);
    
    // Read and process the file
    processList(inFile, words);
    
    // Output formatted review
    originalReview(outFile, origFullWords, origScore);
    
    // Process to make review more negative
    auto [moreNeg, beforeNeg, afterNeg, morePos, beforePos, afterPos] = changeSentiment(origScore, posWords, negWords, posList, negList);
    
    // Output results
    outputChanged(outFile, moreNeg, morePos, origScore, beforeNeg, beforePos, afterNeg, afterPos, negScore, posScore, origFullWords);
}

void openForReview(int i,
                   ofstream& outFile,
                   vector<wordList>& sentList,
                   vector<wordList>& posList,
                   vector<wordList>& negList) {
    string fileName;
    // open input file adding to_string(i) + ".txt" to review
    fileName = "review" + to_string(i) + ".txt";
    
    
    ifstream inFile;
    inFile.open(fileName);
    // if not able to open, print a message and continue
    if (!inFile.is_open()) {
        cout << "Error opening review file" << endl;
        exit(2); // Terminate program
    }

    // else process the file & close it
    processFile(inFile, outFile, fileName, sentList, posList, negList);
    inFile.close();
}

void loadSentList(ifstream& inFile,
                  vector<wordList>& sentList) {
    //add the words to the sentList vector
    string token, inLine;
    vector<string> tokens;
    wordList tempList;
    
    while (getline(inFile, inLine)) {
        istringstream inSS(inLine);
        
        tokens.clear();
        while (getline(inSS, token, ',')) // cutting up the sstream and putting the stuff into tokens vector
            tokens.push_back(token);
        
        try {
            tempList.word = tokens[0];
            tempList.value = stod(tokens[1]);
            
            sentList.push_back(tempList); // temporary wordList is good, add to real vector
        }
        catch (invalid_argument& err) {
            cout << err.what() << " : " << inLine << endl;
        }
    }
}

void sortWords(vector<wordList> sentList,
               vector<wordList>& posList,
               vector<wordList>& negList) {
    //if positive enough add to posList
    //if negative enough add to negList
    for (wordList wl : sentList) {
        if (wl.value > 1.25) { // positive
            posList.push_back(wl);
        } else if (wl.value < -1.25) { // negative
            negList.push_back(wl);
        }
    }
    
    cout << "Vectors loaded - "
         << sentList.size() << " total words, "
         << posList.size() << " positive words, "
         << negList.size() << " negative words." << endl;
}

void processList(ifstream& inFile,
                 vector<wordList>& words) {
    string inWord, newWord, origWord;
    char newChar;
    double origScore = 0;
    vector<wordList> origWords, negWords, posWords;
    vector<pair<string, wordList>> origFullWords; // Store original words with punctuation and case
    
    while (inFile >> inWord) {
        wordList tempList;
        origWord = inWord; // Store original word before any processing
        
        // Clean the word (remove punctuation and convert to lowercase)
        newWord = "";
        for (int i = 0, len = static_cast<int>(inWord.size()); i < len; i++) {
            if (isalpha(inWord[i])) {
                newChar = tolower(inWord[i]);
                newWord += newChar;
            }
        }
        
        // Get sentiment value for the cleaned word
        tempList.word = newWord;
        tempList.value = sentimentVal(newWord, words);
        origScore += tempList.value; // Add to original score
        
        // Store original word with its cleaned version and sentiment
        origFullWords.push_back(make_pair(origWord, tempList));
        
        // Add word to origWords for original review
        origWords.push_back(tempList);
        
        // Check if word is positive or negative enough for potential replacement
        if (tempList.value > 1) {
            posWords.push_back(tempList);
        } else if (tempList.value < -1) {
            negWords.push_back(tempList);
        }
    }
}

void resetValues(vector<wordList>& origWords,
                 vector<wordList>& negWords,
                 vector<wordList>& posWords,
                 vector<pair<string, wordList>>& origFullWords) {
    origWords.clear();
    negWords.clear();
    posWords.clear();
    origFullWords.clear();
}

void originalReview(ofstream& outFile,
                    vector<pair<string, wordList>>& origFullWords,
                    double origScore) {
    // Output formatted review
    int lineLength = 0;
    
    outFile << "FORMATTED REVIEW: " << endl;
    for (unsigned int i = 0; i < origFullWords.size(); i++) {
        lineLength += origFullWords[i].first.length() + 1; // +1 for space
        if (lineLength > 80) {
            outFile << endl;
            lineLength = static_cast<int>(origFullWords[i].first.length()) + 1;
        }
        outFile << origFullWords[i].first << " ";
    }
    outFile << endl << endl;
    outFile << "ORIGINAL SENTIMENT: " << fixed << setprecision(2) << origScore << endl << endl;

}

tuple<vector<pair<wordList, wordList>>, double, double,
      vector<pair<wordList, wordList>>, double, double> changeSentiment(double origScore,
                                                                        vector<wordList>& posWords,
                                                                        vector<wordList>& negWords,
                                                                        vector<wordList>& posList,
                                                                        vector<wordList>& negList) {
    vector<pair<wordList, wordList>> moreNeg, morePos;
    // Process to make review more negative
    double negScore, posScore;
    double beforeNeg, afterNeg, beforePos, afterPos;
    
    vector<wordList> currentList = negList;
    vector<wordList> currentWords = posWords;
    double currentScore = origScore;
    double currentBefore = 0;
    double currentAfter = 0;
    vector<pair<wordList, wordList>> currentMore = moreNeg;
    
    for (int i = 0; i < 2; i++) {
        // Replace positive words with negative words
        for (const wordList& word : currentWords) {
            // Choose a random negative word as replacement
            int randomIndex = rand() % currentList.size();
            wordList replacement = currentList[randomIndex];
            
            // Update the score - subtract positive value and add negative value
            currentScore = currentScore - word.value + replacement.value;
            
            // Store the original and replacement for output
            currentMore.push_back(make_pair(word, replacement));
            
            // Update totals for output
            currentBefore += word.value;
            currentAfter += replacement.value;
        }
        if (i == 0) { // More Negative Run
            beforeNeg = currentBefore;
            afterNeg = currentAfter;
            negScore = currentScore;
            
            currentScore = 0;
            currentBefore = 0;
            currentAfter = 0;
            currentMore = morePos;
        } else { // More Positive Run
            beforePos = currentBefore;
            afterPos = currentAfter;
            posScore = currentScore;
        }
        
    }
    return make_tuple(moreNeg, beforeNeg, afterNeg, morePos, beforePos, afterPos);
}

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
                   vector<pair<string, wordList>>& origFullWords) {
    
    string sentWord = "NEGATIVE";
    double currentScore = negScore;
    double currentBefore = beforeNeg;
    double currentAfter = afterNeg;
    vector<pair<wordList, wordList>> currentMore = moreNeg;
    
    for (int i=0; i<2; i++) {
        // Output results for making review more negative
        outFile << "WORDS UPDATED TO BE MORE " + sentWord + " :" << endl;
        if (currentMore.empty()) {
            outFile << "REVIEW NOT UPDATED TO BE MORE " + sentWord + ". THE SENTIMENT REMAINS: "
            << fixed << setprecision(2) << origScore << endl << endl;
            continue;
        }
        // Column headers
        outFile << setw(15) << "ORIGINAL WORD" << setw(10) << "VALUE"
        << setw(15) << "NEW WORD" << setw(10) << "VALUE" << endl;
        outFile << string(50, '-') << endl;
        
        for (const auto& pair : currentMore) {
            
            outFile << setw(15) << pair.first.word
            << setw(10) << fixed << setprecision(2) << pair.first.value
            << setw(15) << pair.second.word
            << setw(10) << fixed << setprecision(2) << pair.second.value << endl;
        }
        
        outFile << string(50, '-') << endl;
        outFile << "TOTALS:" << setw(24) << fixed << setprecision(2) << currentBefore
        << setw(25) << fixed << setprecision(2) << currentAfter << endl;
        outFile << "UPDATED SENTIMENT (MORE " + sentWord + "): " << fixed << setprecision(2) << currentScore << endl << endl;
        
        // Generate updated review with more negative words
        outFile << "UPDATED REVIEW (MORE " + sentWord + "):" << endl;
        int lineLength = 0;
        
        for (unsigned int i = 0; i < origFullWords.size(); i++) {
            string wordToWrite = origFullWords[i].first; // Default to original word
            
            // Check if this word is in our replacement list
            for (const auto& pair : currentMore) {
                if (origFullWords[i].second.word == pair.first.word) {
                    // Replace with negative word
                    wordToWrite = pair.second.word;
                    break;
                }
            }
            
            lineLength += wordToWrite.length() + 1; // +1 for space
            if (lineLength > 80) {
                outFile << endl;
                lineLength = static_cast<int>(wordToWrite.length()) + 1;
            }
            outFile << wordToWrite << " ";
        }
        outFile << endl << endl;
        
        sentWord = "POSITIVE";
        currentScore = posScore;
        currentBefore = beforePos;
        currentAfter = afterPos;
        currentMore = morePos;
    }
}
