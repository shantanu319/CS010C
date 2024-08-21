#include <iostream>
#include <string>

#include "Playlist.h"

using namespace std;

int main() {
  
  string title;
  cout << "Enter playlist's title:" << endl;
  getline(cin, title);
  cout << endl;
  // Build a playlist which we will use to execute the commands
  // in the loop below
  Playlist P;

  while(true) {
    P.PrintMenu(title);

    // Read commands until error or end-of-file
    // It is much better to read a string here than a character
    // because it will read a single "chunk" of characters and
    // we don't have to deal with problems reading a character
    // without a newline, or when we make a mistake and don't
    // prompt for something that we needed.
    string command;
    if (!(cin >> command)) break;
    cin.ignore();
    
    if (command == "a") {
      string I;
      string S;
      string A;
      int L;
      cout << "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      getline(cin, I);
      cout << "Enter song's name:" << endl;
      getline(cin, S);
      cout << "Enter artist's name:" << endl;
      getline(cin, A);
      cout << "Enter song's length (in seconds):" << endl;
      cin >> L;
      cout << endl;
      cin.ignore();

      P.AddSong(I, S, A, L);
    } else if (command == "d") {
      P.RemoveSong();
    } else if (command == "c") {
      P.ChangePositionSong();
    } else if (command == "s") {
      P.OutputSongsByArtist();
    } else if (command == "t") {
      P.OutputTotalTime();
      cout << endl;
    } else if (command == "o") {
      P.OutputFullPlaylist(title);
    } else if (command == "q") {
      break;
    }
    else{
      cout << "Enter a valid input" << endl;
    }
  }

  // If cin is in an error state (even end-of-file), then
  // something went wrong
  if (!cin) {
    cout << "Program did not exit cleanly" << endl;
    return 1;
  }
  
  
  return 0;
}
