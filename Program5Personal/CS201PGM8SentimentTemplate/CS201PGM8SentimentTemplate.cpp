// CS201PGM8Sentiment 
// NAME:  Cameron Akhtar

#include "Sentiment.h"
using namespace std;

int main()
{
    srand(time(0));
    vector<wordList> sentList, posList, negList;

    // load vectors 
    loadSentiment(sentList, posList, negList);
    // open output file
    ofstream outFile;
    outFile.open("output.txt");
    if (!outFile.is_open()) {
        cout << "Error opening output file" << endl;
        exit(1); // Terminate program
    }
    
    // open review files

    string fileName;
    for (unsigned int i = 1; i < 9; i++) {
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

    //close the output file
    outFile.close();
}
 
