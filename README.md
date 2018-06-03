# Simple Document Index Creator
The purpose of this program is to output a simple alphabetically orderd index containing the words from a file named "Document.txt". The file must have this name for reasons explained below in "Background Info."  
The program will produce a file called "ActualIndex.txt". This file will contain the index. The words will be in alphabetical order, but all words that begin with a capital letter will appear before all words that begin with lowercase letters.

## Background Info:
This project was initially given to us by our Data Structures professors. We were supposed to use our new knowledge of data structures to find a solution to the problem they presented us with, which was to create an index from a given document. They gave us some "skeleton code" that guided us so that we could implement our program the way they wanted us to implement it so that they could test it easily. They also gave us specifications for which words could appear in the index, and what to do when we found words that were not supposed to be in the index. The file "Document.txt" included in this repository lists their specifications. It is also the file used in testing the program.  
The program's "Main.cpp" contains the code used to test our program by our professors.

## Collaborators: 
Francisco Daniel fpdaniel2@csu.fullerton.edu  
Samuel Arteaga samuel.arteaga@csu.fullerton.edu

## Development Environments:
Vim8 & Notepad++

## Building the Program:
A Makefile is included with the project.  
Navigate to the project's directory from the command line. Run `make` from the command line while in that directory. A program named "a.out" will be produced.  
To run the program, while in the program's directory, type `./a.out` on the command line. This will run the tests from our teachers and will produce the index file.

## In this Repository:
The repository contains two header files, DocumentIndex.h and GetLine.h, and three cpp files, DocumentIndex.cpp,
GetLine.cpp, and main.cpp. There are also numerous text files which are read by the header and cpp files as well
as written to. The main.cpp tests the output of the other header and cpp files. GetLine.h declares a couple of getline functions, 
while it's cpp file complement implements the two different types of getline functions, called dependent on the parameters. 
DocumentIndex.h defines and implements two different classes and one struct, and their public and private members. One of the classes
is used to open a single file and keep track of it's current page number, the other class creates an index for the given document
file and writes the index to the given file. Finally, the struct keeps track of how many times a word appears and stores
sorted page number appearances for a given word. 
