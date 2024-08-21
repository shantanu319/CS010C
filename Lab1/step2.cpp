#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <sstream>

#include "testhelpers.h"

// Step 2 says that the main should read in and prompt for
// the playlist name.  The starter main.cpp I give you will
// also call the stub for PrintMenu and print out the
// fake menu I put in there.  It then hits end-of-file
// and quits

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
    fake_execute(fake_main,

		 "JAMZ\n",
		 
		 "Enter playlist's title:\n"
		 "print menu JAMZ\n"
		 "Program did not exit cleanly\n",

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
		 "Program did not exit cleanly\n"
		 );

  }
  catch (const std::runtime_error& e) {
    std::cerr << "Something broke:\n" << e.what() << std::endl;
    return 1;
  }
  return 0;
}
