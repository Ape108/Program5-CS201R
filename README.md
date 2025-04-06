# Sentiment Analysis Program

## Overview
This program performs sentiment analysis on text reviews by analyzing the emotional content and providing alternative versions with more positive and negative sentiments. It's designed to process multiple review files and generate comprehensive sentiment analysis reports.

## Features
- Analyzes text reviews for sentiment using a predefined sentiment dictionary
- Processes multiple review files (review1.txt through review8.txt)
- Generates sentiment scores for each review
- Creates alternative versions of reviews with more positive and negative sentiments
- Outputs results to a single output file (output.txt)

## Program Structure
- `Sentiment.h`: Header file containing the program's data structures and function declarations
- `Sentiment.cpp`: Implementation of the sentiment analysis functionality
- `CS201PGM8SentimentTemplate.cpp`: Main program file that orchestrates the review processing

## Data Structures
- `wordList`: Stores words and their associated sentiment values
- `replaceList`: Stores word replacement information for generating alternative reviews

## Key Functions
- `loadSentiment()`: Loads sentiment data from sentiment.txt into three vectors (general, positive, and negative words)
- `processFile()`: Processes individual review files and generates sentiment analysis
- `sentimentVal()`: Calculates sentiment value for individual words
- `alphabeticalBinarySearch()`: Efficiently searches for words in the sentiment dictionary

## Input Files
- `sentiment.txt`: Contains the sentiment dictionary with words and their associated values
- `review1.txt` through `review8.txt`: Input review files to be analyzed
- `reviewsPart1.txt` and `reviewsPart2.txt`: Additional review files

## Output
- `output.txt`: Contains the analysis results for all processed reviews, including:
  - Original review sentiment
  - More positive version of the review (if possible)
  - More negative version of the review (if possible)

## Author
Cameron Akhtar 
