// -*-c++-*-


#pragma once

#include <iostream>
using namespace std;

class PlaylistNode {

  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;

public:
  PlaylistNode() // default constructor
  {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
  }
  //parametrized constructor
  PlaylistNode(string uniqueId, string name, string aName, int length) : uniqueID(uniqueId), songName(name), artistName(aName), songLength(length) 
  {
    nextNodePtr = nullptr;
  };
  void InsertAfter(PlaylistNode* nextNode)
  {
    PlaylistNode* temp = nextNodePtr;
    this->nextNodePtr = nextNode;
    nextNode->SetNext(temp); 
  }
  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  void SetNext(PlaylistNode* next) {this->nextNodePtr = next;}
  const void PrintPlaylistNode() const {
    cout << "Unique ID: " << uniqueID << '\n';
    cout << "Song Name: " << songName << '\n';
    cout << "Artist Name: " << artistName << '\n';
    cout << "Song Length (in seconds): " << songLength;
    cout << endl;
  }
};

class Playlist {
  PlaylistNode* head;
  PlaylistNode* tail;
public:
  Playlist()
    : head(nullptr),tail(nullptr)
  {}
  ~Playlist() //destructor
  {
    PlaylistNode* curr = head;
    while(curr != nullptr)
    {
      PlaylistNode* temp = curr->GetNext();
      delete curr;
      curr = temp;
    }
  }
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist(string title) const;
};

