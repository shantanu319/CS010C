#include <iostream>
#include <exception>
#include <string>
#include <sstream>

#include "testhelpers.h"

// Step 1 says to create these three files.  I do some #define trickery to read them in
#define cout fake_cout
#include "Playlist.h"
#include "Playlist.cpp"
#undef cout

int main() {
  try {
  // Check if I can use a default constructor... 
  // fix or add it to the playlist node.
  PlaylistNode n;
  if (n.GetID() != "none") {
    throw std::runtime_error("broken default constructor: id");
  }
  if (n.GetSongName() != "none") {
    throw std::runtime_error("broken default constructor: song name");
  }
  if (n.GetArtistName() != "none") {
    throw std::runtime_error("broken default constructor: artist name");
  }
  if (n.GetSongLength() != 0) {
    throw std::runtime_error("broken default constructor: song length");
  }
  if (n.GetNext() != nullptr) {
    throw std::runtime_error("broken default constructor: next");
  }

  // Check if the const parts work correctly
  const PlaylistNode& const_n = n;
  if (const_n.GetID() != "none") {
    throw std::runtime_error("for const, broken default constructor: id");
  }
  if (const_n.GetSongName() != "none") {
    throw std::runtime_error("for const, broken default constructor: song name");
  }
  if (const_n.GetArtistName() != "none") {
    throw std::runtime_error("for const, broken default constructor: artist name");
  }
  if (const_n.GetSongLength() != 0) {
    throw std::runtime_error("for const, broken default constructor: song length");
  }
  if (const_n.GetNext() != nullptr) {
    throw std::runtime_error("for const, broken default constructor: next");
  }

  // Check if I can add the parameterized constructor...
  PlaylistNode n2("SD123","Peg","Steely Dan",237);
  if (n2.GetID() != "SD123") {
    throw std::runtime_error("broken parameterized constructor: id");
  }
  if (n2.GetSongName() != "Peg") {
    throw std::runtime_error("broken parameterized constructor: song name");
  }
  if (n2.GetArtistName() != "Steely Dan") {
    throw std::runtime_error("broken parameterized constructor: artist name");
  }
  if (n2.GetSongLength() != 237) {
    throw std::runtime_error("broken parameterized constructor: song length");
  }
  if (n2.GetNext() != nullptr) {
    throw std::runtime_error("broken parameterized constructor: next");
  }

  // See if printing works (for const node!)
  fake_cout.clear();
  n2.PrintPlaylistNode();
  const std::string expected("Unique ID: SD123\nSong Name: Peg\nArtist Name: Steely Dan\nSong Length (in seconds): 237");
  if (fake_cout.str() != expected) {
    // Maybe it just has a newline on it
    if (fake_cout.str() == expected+'\n') {
      throw std::runtime_error("don't end output with a newline");
    } else if (strip_white(expected) == strip_white(fake_cout.str())) {
      throw std::runtime_error("probably have a whitespace issue");
    } else {
      throw std::runtime_error(WHERE+"expected:\n"+expected+"\ngot:\n"+fake_cout.str());
    }
  }

  }
  catch (const std::runtime_error& e) {
    std::cerr << "Something broke:\n" << e.what() << std::endl;
    return 1;
  }
  return 0;
}
