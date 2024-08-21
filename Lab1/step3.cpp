#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "testhelpers.h"

// Step 3 says that the main should read in and prompt for
// the playlist name.  It should be able to exit cleanly
// since we've implemented.  We also test to make sure we
// get our "stub" messages for each letter and cleanly
// handle any invalid commands


#define cout fake_cout
#define cin fake_cin
#define main fake_main
#include "Playlist.h"
#include "Playlist.cpp"
#include "main.cpp"
#undef main
#undef cout
#undef cin

int main() {
  try {
    // See if the menu works with just 'q' for quit
    fake_execute(fake_main,

		"JAMZ\n"
		"q\n",

		"Enter playlist's title:\n"
		"JAMZ PLAYLIST MENU\n"
		"a - Add song\n"
		"d - Remove song\n"
		"c - Change position of song\n"
		"s - Output songs by specific artist\n"
		"t - Output total time of playlist (in seconds)\n"
		"o - Output full playlist\n"
		"q - Quit\n"
		"\n"
		"Choose an option:\n"
	      );

    // Try every letter of the alphabet, it should reprompt for those
    // that don't occur and print the fake message for those that do
    {
      std::map<char,std::string> messages;
      messages['a'] = "add song";
      messages['d'] = "remove song";
      messages['c'] = "change position song";
      messages['s'] = "output songs by artist";
      messages['t'] = "output total time";
      messages['o'] = "Playlist is empty";

      std::string menu(
		       "JAMZ PLAYLIST MENU\n"
		       "a - Add song\n"
		       "d - Remove song\n"
		       "c - Change position of song\n"
		       "s - Output songs by specific artist\n"
		       "t - Output total time of playlist (in seconds)\n"
		       "o - Output full playlist\n"
		       "q - Quit\n"
		       "\n"
		       "Choose an option:\n"
		       );
      
      std::string input("JAMZ\n");
      std::string expected("Enter playlist's title:\n");
      for(int i=0; i<26; ++i) {
	char c = 'a'+i;
	if (c == 'q') continue;
	
	// For each command, we'll get a "Choose an option:" line
	expected += menu;

	// Add the command (or bad command) to the input string
	input += c;
	input += '\n';

	if (messages[c].size() > 0) {
	  expected += messages[c];
	  expected += '\n';
	}
      }
      expected += menu;
      input += "q\n";

      fake_execute(fake_main,input,expected);
    }
  }
  catch (const std::runtime_error& e) {
    std::cerr << "Something broke:\n" << e.what() << std::endl;
    return 1;
  }
  return 0;
}
