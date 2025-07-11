# Sentiment Analysis Program

## Overview

This program performs sentiment analysis on text reviews by analyzing the emotional content and providing alternative versions with more positive and negative sentiments. It's designed to process multiple review files and generate comprehensive sentiment analysis reports.

## Features

  - Analyzes text reviews for sentiment using a predefined sentiment dictionary.
  - Processes multiple review files (`review1.txt` through `review8.txt`) automatically.
  - Generates sentiment scores for each original review.
  - Creates alternative versions of reviews with more positive and negative sentiments by swapping words.
  - Outputs all results to a single, detailed `output.txt` file.

## How It Works: A Demonstration

The program reads a review, calculates its sentiment, and then rewrites it to be more positive or negative.

### Example 1: Making a Positive Review Negative

First, the program processes a positive review from `review1.txt`:

```
This was an amazing restaurant! The pizza crust was delicious, and I loved the pasta.
The atmosphere was wonderful and enchanting.
```

It analyzes the text and calculates its initial sentiment score:

```
ORIGINAL SENTIMENT: 7.95
```

Next, it identifies positive words and replaces them with negative ones from the sentiment dictionary to create a new, negative version of the review:

```
WORDS UPDATED TO BE MORE NEGATIVE:
  ORIGINAL WORD     VALUE       NEW WORD     VALUE
--------------------------------------------------
        amazing      1.26      miserable     -2.57
      delicious      2.20         guilty     -1.66
          loved      1.21         brutal     -2.09
      wonderful      2.76     everywhere     -1.74
--------------------------------------------------
UPDATED SENTIMENT (MORE NEGATIVE): -7.54
```

Here is the final, more negative review:

```
UPDATED REVIEW (MORE NEGATIVE):
This was an miserable restaurant! The pizza crust was guilty and I brutal the
pasta. The atmosphere was everywhere and enchanting.
```

### Example 2: Making a Negative Review Positive

The program can also reverse the sentiment of a negative review, like this one from `review3.txt`:

```
"Jennifer is very nice and responsive. The location of the apt is great. However
- the bed was small and smelled bad. The apt also smelled weird. We had to
sleep on a mattress on the floor - the building is very old. - the apt is
not clean and due to construction it was very noisy. However. We do appreciate
the stay and the location"
```

The initial sentiment is negative:

```
ORIGINAL SENTIMENT: -2.46
```

The program then swaps negative words for positive ones:

```
WORDS UPDATED TO BE MORE POSITIVE:
  ORIGINAL WORD     VALUE       NEW WORD     VALUE
--------------------------------------------------
        smelled     -2.44       striking      2.06
        smelled     -2.44        angular      1.35
          weird     -1.32        flowers      1.26
          clean     -1.06          marry      2.06
          noisy     -1.32        sharing      1.50
--------------------------------------------------
UPDATED SENTIMENT (MORE POSITIVE): 14.35
```

And here is the final, more positive version of the review:

```
UPDATED REVIEW (MORE POSITIVE):
"Jennifer is very nice and responsive. The location of the apt is great.
However - the bed was small and striking bad. The apt also striking flowers We
had to sleep on a mattress on the floor - the building is very old. - the apt
is not marry and due to construction it was very sharing However. We do
appreciate the stay and the location"
```

## Program Structure

  - `Sentiment.h`: Header file containing the program's data structures and function declarations.
  - `Sentiment.cpp`: Implementation of the sentiment analysis functionality.
  - `CS201PGM8SentimentTemplate.cpp`: The main program file that orchestrates the review processing.

## Author

Cameron Akhtar
