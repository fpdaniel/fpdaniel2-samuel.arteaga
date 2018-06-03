# Simple Document Index Creator
The purpose of this program is to output a simple alphabetically ordered index containing the words from a file named "Document.txt". The file must have this name for reasons explained below in "Background Info."  
The program will produce a file called "ActualIndex.txt". This file will contain the index. The words will be in alphabetical order and are case-sensitive, so all words that begin with a capital letter will appear before all words that begin with a lowercase letter. Each word will be followed by a comma-separated list of numbers that indicate on which page(s) each word was found.

## Background Info:
This project was initially given to us by our Data Structures professors. We were supposed to use our new knowledge of data structures to find a solution to the problem they presented us with, which was to create an index from a given document. They gave us some "skeleton code" that guided us so that we could implement our program the way they wanted us to implement it so that they could test it easily. They also gave us specifications for which words could appear in the index, and what to do when we found words that were not supposed to be in the index. The file "Document.txt" included in this repository lists their specifications. It is also the file used in testing the program.  
The program's "Main.cpp" contains the code written by our professors that is used to test our program.  
This program was initially hosted in a private repository that only our professors and we could view, but we copied the files and put them on this repository. Our older git logs did not come with those files, so included in this repository is a file named "older_logs.txt" that contains the older commit-messages and other details from the older repository.

## Collaborators: 
Francisco Daniel fpdaniel2@csu.fullerton.edu  
Samuel Arteaga samuel.arteaga@csu.fullerton.edu

## Development Environments:
Vim8 & Notepad++  
Compiler used: g++ (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609

## Building the Program:
A Makefile is included with the project.  
Navigate to the project's directory from the command line. Run `make` from the command line while in that directory. A program named "a.out" will be produced.  
To run the program, while in the program's directory, type `./a.out` on the command line. This will run the tests from our teachers and will produce the index file.

## In this Repository:
Almost all of the files in this repository were given to us by our professors. Some of them were complete, and some of them contained skeleton code that we needed to complete. Details are given in the "Document.txt" file in this repository. More comments are given in most of the files. More information for each file is given below.

    * README.md: You are here.
    * DocumentIndex.h: This contains the class declaration for the DocumentIndex and DocumentFile class used in the main part of the program. This was mostly given to us, and we had to make only small changes to it.
    * DocumentFile.cpp: This contains the definitions for each of the class functions from DocumentIndex.h. These were implemented by us.
    * Getline.h: This contains declarations for two portable GetLine functions for our project. A professor wrote these functions, and they are used in Main.cpp for testing our code. They are also also used in the code in DocumentIndex.cpp.
    * GetLine.cpp: This contains the definitions for the GetLine functions.
    * Main.cpp: This is the testing code written by the professor(s). More information is given in a comment at the top of the file.
    * Document.txt: This file contains details about the professors' specifications for the project, and it is the file from which the index is created, as stated above.
    * ExcessiveAppearances.txt: This file is used to test if our program properly handles words that appear too many times. More details are given in "Document.txt".
    * ExclusionWords.txt: This file contains newline-separated words that should not be included in the index.
    * ExclusionTest.txt: This file was given to us and tests if our program properly skips words that are in "ExclusionWords.txt".
    * ExpectedIndex.txt: This file was given and shows exactly what the index should look like when the program is run with the given "Document.txt". The "Main.cpp" file tests the output "ActualIndex.txt" against this file to see if our program worked properly.
    * GetWord.txt: This file was given to us and is used to test if our GetWord() function functions properly.
    * Makefile: This file is used to build the project with `make`. More details are given above in "Building the Program."
    * PageNumber.txt: This file was given to us and is used to test whether or not our program properly detects the current page number of the document (Pages are delimited by two consecutive blank lines).
    * older_logs.txt: These are the older git logs mentioned above in "Background Info."
    * Doxyfile: This file is a configuration file for doxygen output that was generated by doxygen. It contains all of the default settings since I have not changed them yet and have not yet learned how to use doxygen properly. I know it is useful and I have seen nice doxygen-generated documentation before, but the documentation generated for this project as of right now is not exactly ideal. I hope to improve it once I learn how to better use doxygen.
    * Directories html/ and latex/: These were both generated by doxygen using the Doxyfile configuration file. It's not too pretty as of right now, but maybe someday it will be.
