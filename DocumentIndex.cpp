#include	<fstream>
#include	<iostream>
#include	<string>

#include	"DocumentIndex.h"
#include	"GetLine.h"

using namespace std;

typedef	string::size_type	StringSize;

//****************************************************************************************
//
//	DocumentFile::Close
//
//	This function closes the file associated with the object and writes to the file if 
//	there is a pending output sequence. Any error state flags are cleared in order to 
// 	be able to return void. 
//****************************************************************************************
void	DocumentFile::Close()
{
	file_.close();
	file_.clear();

	return;
}

//****************************************************************************************
//
//	DocumentFile::GetPageNumber
//
//	This function simply returns the current page number. 
//****************************************************************************************
int	DocumentFile::GetPageNumber()
{
	return(pageNumber_);
}

//****************************************************************************************
//
//	DocumentFile::GetWord
//
//	This function reads a single word from the istringstream in class DocumentFile.
//	If an excluded word is present, then the word is deleted.
//	If a character that invalidates the word is present, then the word is deleted.
//	If a banned character is present that does not invalidate the word, then the
//	character is stripped to form a valid word.
//	If a word was deleted, then the function is called recursively to test the next word.
//	The function returns either a valid word or an empty string.
//
//****************************************************************************************
string	DocumentFile::GetWord()
{
	string	word;

	if (iss >> word) {
		for (int i = 0; i < exclusionVec.size(); ++i) {
			if (word == exclusionVec[i]) {
				word.erase();
				break;
			}
		}

		size_t found = word.find_first_of("0123456789-_=+/@#$%^&*~`[]{}\\|");
		while (found != word.npos) {
			word.erase();
			break;
		}

		found = word.find_first_of(".,;:?!\"()");
		while (found != word.npos) {
			if (found == 0 || found == word.size() - 1) {
				word.erase(word.begin() + found);
				found = word.find_first_of(".,;:?!\"()", found);
			}
			else {
				word.erase();
				break;
			}
		}

		found = word.find_first_of("\'");
		while (found != word.npos) {
			if (found == word.size() - 2) {
				word.erase(word.begin() + found, word.end());
				break;
			}
			else if (found == 0 || found == word.size() - 1) {
				word.erase(word.begin() + found);
				found = word.find_first_of("\'", found);
			}
			else {
				word.erase();
				break;
			}
		}
		if (word.empty()) {
			word = GetWord();
		}
	}
	else {
		word.erase();
		iss.clear();
	}

	return(word);
}

//****************************************************************************************
//
//	DocumentFile::LoadExclusions
//
//	This function reads excluded words from the file with the passed filename and inserts
//	those words into the vector member that stores the excluded words.
//	The function returns true if the file opens properly.
//
//****************************************************************************************
bool	DocumentFile::LoadExclusions(const string& name)
{
	bool	success;

	success = false;
	ifstream myFile {name};
	if (!myFile.fail())
	{
		success = true;
		string word;
		while (myFile >> word)
			exclusionVec.push_back(word);
	}
	myFile.close();

	return(success);
}

//****************************************************************************************
//
//	DocumentFile::Open
//
//	This function opens a given file. If the file opens, it returns true, but if it doesn't 
//	open, it returns false.
//****************************************************************************************
bool	DocumentFile::Open(const string& name)
{
	file_.open(name, ios::in);
	if (!file_.fail())
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

//****************************************************************************************
//
//	DocumentFile::Read
//
//	This function reads a line using GetLine() and increments the pageNumber if there are
//	two subsequent empty lines.
//	The line read from GetLine() is stored in the text_ member, which is used to create
//	a string stream to be used in GetWord().
//	The function returns true if Getline() returns true.
//
//****************************************************************************************
bool	DocumentFile::Read()
{
	bool	success;

	success = GetLine(file_, text_);
	if (success) {
		if (text_.empty()) {
			success = GetLine(file_, text_);
			if (text_.empty()) {
				++pageNumber_;
				success = GetLine(file_, text_);
			}
		}
		iss.str(text_);
	}

	return(success);
}

//****************************************************************************************
//
//	DocumentIndex::Create
//
//	This function creates the map that is used to form the index in Write().
//	If a line read is successful, then valid words will be taken one at a time and
//	inserted into the map. If the received word is already in the map, the count of the
//	word is increased and the word is inserted into the map. If the word is not in the
//	map, a new WordInfo object is created to store the count of the word and its page
//	number appearances, and the word is also inserted into the map. Lines are read until
//	there are no more lines to read (when Read() fails).
//	After the map is formed, the map is looped through, deleting any word that appears
//	more than 10 times, the maximum amount of times a word can appear to be in the index.
//
//****************************************************************************************
void	DocumentIndex::Create(DocumentFile& documentFile)
{
	string word;
	map<string, WordInfo>::iterator itr;
	const int maxCount = 10;

	while (documentFile.Read()) {
		while (true) {
			word = documentFile.GetWord();
			if (!word.empty()) {
				itr = wordMap.find(word);
				if (itr != wordMap.end()) {
					++(itr->second.count);
					itr->second.pageNums.insert(documentFile.GetPageNumber());
				}
				else {
					WordInfo wordInfo;
					wordInfo.pageNums.insert(documentFile.GetPageNumber());
					wordMap[word] = wordInfo;
				}
			}
			else
				break;
		}
	}
	for (map<string, WordInfo>::const_iterator it = wordMap.cbegin(); it != wordMap.cend(); ) {
		if (it->second.count > maxCount) {
			it = wordMap.erase(it);
		}
		else {
			++it;
		}
	}

	return;
}

//****************************************************************************************
//
//	DocumentIndex::Write
//
//	This function loops through the map, reading out to the passed ostream each word in
//	the map in alphabetical/capital order, along with each word's page number appearances.
//
//****************************************************************************************
void	DocumentIndex::Write(ostream& indexStream)
{
	map<string, WordInfo>::iterator mapItr;
	set<int>::iterator setItr;
	set<int>::iterator lastSetElemItr;

	for (mapItr = wordMap.begin (); mapItr != wordMap.end(); ++mapItr) {
		indexStream << mapItr->first << ' ';
		lastSetElemItr = mapItr->second.pageNums.end();
		--lastSetElemItr;
		for (setItr = mapItr->second.pageNums.begin(); setItr != lastSetElemItr; ++setItr) {
			indexStream << *setItr << ", ";
		}
		indexStream << *(lastSetElemItr) << endl;
	}

	return;
}

WordInfo::WordInfo() :count{1} {}			// Called when a new word is put into the map
											// A new word appears one time at its creation
