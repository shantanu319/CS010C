#include <list>
#include <string>

using std::list;
using std::string;

class WordLadder {

  private:
    list<string> dict;        //list of possible words in ladder
    string outputFile;        // output file name

    bool differenceCheck(string& lhs, const string& rhs) const; //helper function to check if there is a one letter difference between two words
    

  public:
    
    WordLadder(const string& filename);
    void outputLadder(const string &start, const string &end, const string &outputFile);
};
