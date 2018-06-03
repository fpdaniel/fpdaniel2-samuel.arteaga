#ifndef	DocumentIndex_h
#define	DocumentIndex_h

#include	<fstream>
#include	<map>
#include	<set>
#include	<string>
#include 	<sstream>
#include 	<vector>

using namespace std;

struct	WordInfo {
	WordInfo();
	int count;								///< How many times the word appears.
	set<int> pageNums;						///< Stores sorted page number appearances for the word.
};

typedef	string::size_type	StringSize;

/// This class is a wrapper around an input file stream.
/// It is used to open a single file, and it keeps track of the current page number.
/// New pages are delimted by two blank lines.
/// This class also has member functions to perform certain operations using the stream.
/// It can also read a file that contains words which should not be included in the index.
class	DocumentFile
{
	public:

		/// Constructor that initializes the current page number to page 1.
		DocumentFile() : pageNumber_(1) { }

		/// Closes the document file.
		void	Close();

		/// Returns the current page number.
		int		GetPageNumber();

		/// Returns the next legal word not on the exception list;
		/// Returns an empty string if there are no more words in
		/// the line.
		string	GetWord();

		/// Loads a list of words to be excluded from the index
		/// from a file of the given name.
        /// Returns true iff the file opens properly.
		bool	LoadExclusions(const string& name);

		/// Opens a document file of the given name.
        /// Returns true iff the file opens properly.
		bool	Open(const string& name);

		/// Reads the next line of the document file, skipping over
		/// the double empty lines that mark page separations.
		/// Returns false if there are no more lines in the file.
		bool	Read();



	private:
		StringSize	beginPosition_;

		fstream		file_;					///< The file being read.

		int			pageNumber_;			///< Current page number of the document.

		string		text_;					///< The current line to be processed.

		istringstream iss;					///< Stream to read individual words from a read line.

		vector<string> exclusionVec;		///< Stores words to be excluded from the index.
};

/// This class creates the index from a given DocumentFile.
/// It stores the words and their page numbers in a binary search tree so that they
/// are automatically sorted and operations are performed quickly. It can then
/// write the index out to a text file.
class	DocumentIndex
{
	public:

		/// Creates an index for the given document file.
		void	Create(DocumentFile& documentFile);

		void	Show(ostream& stream);

		/// Writes the index to the given file.
		/// The argument is a stream so that this function
		/// can be called to wrtite its output to cout for
		/// test purposes.
		void	Write(ostream& indexFile);




	private:
		map<string, WordInfo> wordMap;		///< Stores words and WordInfo to be displayed in the index
};

#endif
