// CS201PGM8Sentiment 
// NAME:  Cameron Akhtar

#include "Sentiment.h"
using namespace std;

int main()
{
    srand(static_cast<int>(time(0)));
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
    for (unsigned int i = 1; i < 9; i++) {
        openForReview(i, outFile, sentList, posList, negList);
    }

    //close the output file
    outFile.close();
}
 

