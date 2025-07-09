#include "Sentiment.h"

//PRE: Vector arr must be sorted in ascending alphabetical order, containing wordList elements, with target as the string to find.
//POST: Returns the index of target if found in arr, otherwise returns -1, leaving both input parameters unchanged and executing in O(log n) time.
int alphabeticalBinarySearch(const vector<wordList>& arr, const string& target) {
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

//SUPPORT FUNCTION TO FIND THE CURRENT WORD IN THE SENTEMENT VECTOR & RETURN THE SENTIMENT VALUE
//PRE:   accepts a string (in) and the words list
//POST:  returns the sentiment of the word if found or the value 0 if not
double sentimentVal(string in, vector<wordList> &words) {
    
    int index = alphabeticalBinarySearch(words, in);
    if (index != -1) { // binary search returned an index
        return words[index].value; // return value of word at that index
    }
    return 0;
}

//PRE:   accepts an empty set of 3 <wordList> vectors
//POST:  loads all three vectors with data from sentiment.txt
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
    
    inFile.close(); // Done with the input file.

    
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

//PRE:  positive & negative word lists are sent
//POST: Open the input file & output file (infile+Output
//      'Clean' the input by removing syntax and setting all to lower case
//       Get the sentiment value for the edited word
//        store unedited word in vector with sentiment value
//         if sentiment < -1  find a positive word to replace it
//         if sentiment > 1   find a negative word to replace
void processFile(ifstream& inFile, ofstream& outFile, string fileName,
                    vector<wordList>& words,               // vectors containing the word & sentiment
                    vector<wordList>& posList,
                    vector<wordList>& negList) {
 
    string inWord, newWord, origWord;
    char newChar;
    vector<wordList> origWords, negWords, posWords;
    vector<pair<wordList, wordList>> moreNeg, morePos;
    vector<pair<string, wordList>> origFullWords; // Store original words with punctuation and case
    double origScore = 0, negScore = 0, posScore = 0;
    
    cout << "\nPROCESSING FILE: " << fileName << endl;
    outFile << "\n\nPROCESSING FILE: " << fileName << endl << endl;

    // reset all vectors & values before processing inFile
    origWords.clear();
    negWords.clear();
    posWords.clear();
    moreNeg.clear();
    morePos.clear();
    origFullWords.clear();
    origScore = 0;
    
    // Read and process the file
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
    
    // Output formatted review
    outFile << "FORMATTED REVIEW: " << endl;
    int lineLength = 0;
    for (unsigned int i = 0; i < origFullWords.size(); i++) {
        lineLength += origFullWords[i].first.length() + 1; // +1 for space
        if (lineLength > 80) {
            outFile << endl;
            lineLength = static_cast<int>(origFullWords[i].first.length()) + 1;
        }
        outFile << origFullWords[i].first << " ";
    }
    outFile << endl << endl;
    
    // Output original sentiment
    outFile << "ORIGINAL SENTIMENT: " << fixed << setprecision(2) << origScore << endl << endl;
    
    // Process to make review more negative
    double beforeNeg = 0, afterNeg = 0;
    negScore = origScore; // Start with original score
    
    // Replace positive words with negative words
    for (const wordList& posWord : posWords) {
        // Choose a random negative word as replacement
        int randomIndex = rand() % negList.size();
        wordList negReplacement = negList[randomIndex];
        
        // Update the score - subtract positive value and add negative value
        negScore = negScore - posWord.value + negReplacement.value;
        
        // Store the original and replacement for output
        moreNeg.push_back(make_pair(posWord, negReplacement));
        
        // Update totals for output
        beforeNeg += posWord.value;
        afterNeg += negReplacement.value;
    }
    
    

    
    // Output results for making review more negative
    outFile << "WORDS UPDATED TO BE MORE NEGATIVE:" << endl;
    if (moreNeg.empty()) {
        outFile << "REVIEW NOT UPDATED TO BE MORE NEGATIVE. THE SENTIMENT REMAINS: " << fixed << setprecision(2) << origScore << endl << endl;
    } else {
        // Column headers
        outFile << setw(15) << "ORIGINAL WORD" << setw(10) << "VALUE" 
                << setw(15) << "NEW WORD" << setw(10) << "VALUE" << endl;
        outFile << string(50, '-') << endl;
        
        for (const auto& pair : moreNeg) {

            outFile << setw(15) << pair.first.word 
                    << setw(10) << fixed << setprecision(2) << pair.first.value
                    << setw(15) << pair.second.word 
                    << setw(10) << fixed << setprecision(2) << pair.second.value << endl;
        }
        
        outFile << string(50, '-') << endl;
        outFile << "TOTALS:" << setw(24) << fixed << setprecision(2) << beforeNeg 
                << setw(25) << fixed << setprecision(2) << afterNeg << endl;
        outFile << "UPDATED SENTIMENT (MORE NEGATIVE): " << fixed << setprecision(2) << negScore << endl << endl;
        
        // Generate updated review with more negative words
        outFile << "UPDATED REVIEW (MORE NEGATIVE):" << endl;
        lineLength = 0;
        
        for (unsigned int i = 0; i < origFullWords.size(); i++) {
            string wordToWrite = origFullWords[i].first; // Default to original word
            
            // Check if this word is in our replacement list
            for (const auto& pair : moreNeg) {
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
    }
    
    // Process to make review more positive
    double beforePos = 0, afterPos = 0;
    posScore = origScore; // Start with original score
    
    // Replace negative words with positive words
    for (const wordList& negWord : negWords) {
        // Choose a random positive word as replacement
        int randomIndex = rand() % posList.size();
        wordList posReplacement = posList[randomIndex];
        
        // Update the score - subtract negative value and add positive value
        posScore = posScore - negWord.value + posReplacement.value;
        
        // Store the original and replacement for output
        morePos.push_back(make_pair(negWord, posReplacement));
        
        // Update totals for output
        beforePos += negWord.value;
        afterPos += posReplacement.value;
    }
    
    // Output results for making review more positive
    outFile << "WORDS UPDATED TO BE MORE POSITIVE:" << endl;
    if (morePos.empty()) {
        outFile << "REVIEW NOT UPDATED TO BE MORE POSITIVE. THE SENTIMENT REMAINS: " << fixed << setprecision(2) << origScore << endl << endl;
    } else {
        // Column headers
        outFile << setw(15) << "ORIGINAL WORD" << setw(10) << "VALUE" 
                << setw(15) << "NEW WORD" << setw(10) << "VALUE" << endl;
        outFile << string(50, '-') << endl;
        
        for (const auto& pair : morePos) {
            outFile << setw(15) << pair.first.word 
                    << setw(10) << fixed << setprecision(2) << pair.first.value
                    << setw(15) << pair.second.word 
                    << setw(10) << fixed << setprecision(2) << pair.second.value << endl;
        }
        
        outFile << string(50, '-') << endl;
        outFile << "TOTALS:" << setw(24) << fixed << setprecision(2) << beforePos 
                << setw(25) << fixed << setprecision(2) << afterPos << endl;
        outFile << "UPDATED SENTIMENT (MORE POSITIVE): " << fixed << setprecision(2) << posScore << endl << endl;
        
        // Generate updated review with more positive words
        outFile << "UPDATED REVIEW (MORE POSITIVE):" << endl;
        lineLength = 0;
        
        for (unsigned int i = 0; i < origFullWords.size(); i++) {
            string wordToWrite = origFullWords[i].first; // Default to original word
            
            // Check if this word is in our replacement list
            for (const auto& pair : morePos) {
                if (origFullWords[i].second.word == pair.first.word) {
                    // Replace with positive word
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
    }
}

void openForReview(int i, ofstream& outFile, vector<wordList>& sentList, vector<wordList>& posList, vector<wordList>& negList) {
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
