# small search engine
This is a small search engine.

Image there are many files which have more than 1 million lines and each line is a sentences.

For my program, it has a query operator, you can input some words and output all the line in those files which includes all those words.

At first, I can read the all files one by one and create all the word index as a txt file.
When user query, we can find the word`s index and output where is the line in the original file. This program can reduce I/O operator and make sure to use few memory.


How to compile:

Gcc-7 search engine.cpp -o search engine -lstdc++

How to run:

./search engine
