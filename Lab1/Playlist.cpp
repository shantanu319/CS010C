#include "Playlist.h"


void Playlist::PrintMenu(const string& title) const {
  cout << title << " PLAYLIST MENU" << endl; 
  cout << "a - Add song\nd - Remove song\nc - Change position of song\ns - Output songs by specific artist\nt - Output total time of playlist (in seconds)"
          "\no - Output full playlist\nq - Quit" << endl; //written with endlines
  cout << endl;
  cout << "Choose an option:" << endl;
}

void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
  PlaylistNode* newSong = new PlaylistNode(id, song, artist, length);
  if (head == nullptr) //check empty list case, set head and tail pointers to new node
  {
    head = tail = newSong;
  }
  else //general case, pushes back songs
  {
    tail->SetNext(newSong);
    newSong->SetNext(nullptr);
    tail = newSong;
  }
}

void Playlist::RemoveSong() {
  string id;
  cout << "REMOVE SONG" << endl;
  cout << "Enter song's unique ID:";
  cin >> id;
  cout << endl;
  if (head == nullptr)
  {
   //if empty list, do nothing 
  }
  //removal sequence if at head
  else if (head->GetID() == id)
  {
    PlaylistNode* temp = head;
    head = head->GetNext();
    cout << '"' << temp->GetSongName() << '"' << " removed." << endl;
    delete temp;
    temp = nullptr;
  }
  else
  {
    //middle or tail cases
    PlaylistNode* prev = head;
    PlaylistNode* curr = head->GetNext();
    while(curr != nullptr) //iterate through list
    {
      if (curr->GetID() == id) //check each node if = to target id
      {
        cout << '"' << curr->GetSongName() << '"' << " removed." << endl;
        if (curr == tail) //tail case
        {
          prev->SetNext(nullptr);
          delete curr;
          break; 
        }
        else
        {
          prev->SetNext(curr->GetNext()); //middle case
          curr = prev->GetNext();
        }
      }
      prev = prev->GetNext();
      curr = curr->GetNext();
    }
  }
  cout << endl;
  
}

void Playlist::ChangePositionSong() { //not a good solution, 6 if elses
  cout << "CHANGE POSITION OF SONG" << endl;
  int Pos;
  cout << "Enter song's current position:" << endl;
  cin >> Pos;
  int newPos;
  cout << "Enter new position for song:" << endl;
  cin >> newPos;

  int index = 1;
  //input validation
  //getting list size for new > n
  int size = 0;
  for (const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext())
  {
    size++;
    //cout << size << endl;
  }
  if (newPos < 1) {newPos = 1;}
  if (newPos > size) {newPos = size;}

  //don't do anything if newPos and Pos are the same or list is empty
  if (newPos == Pos || head == nullptr)
  {
    return;
  }
  else //non-empty list case
  {
    //get pointer of node to move and prev node
    PlaylistNode* prev = nullptr; // if Pos > 1, holds node right before one we want to move
    PlaylistNode* toMove = head; //node we want to move
    index = 1;
    while (index != Pos)
    {
      prev = toMove;
      toMove = toMove->GetNext();
      index++;
    }

    //get node right before newPos (newPos - 1)
    index = 1;
    PlaylistNode*nMove_prev = nullptr;
    PlaylistNode*nMove = head;
    while (index != newPos)
    {
     nMove_prev =nMove;
     nMove =nMove->GetNext();
      index++;
    }

    //if head node is being moved
    if (Pos == 1)
    {
      head = head->GetNext();
      toMove->SetNext(nMove_prev->GetNext());
     nMove->SetNext(toMove);
    }
    // last node is being moved
    else if (toMove->GetNext() == nullptr)
    {
      if (nMove_prev == nullptr) //if moving tail to the front
      {
        toMove->SetNext(head);
        head = toMove;
        prev->SetNext(nullptr);
        tail = prev;
      }
      else
      {
        prev->SetNext(nullptr);
        tail = prev;
        toMove->SetNext(nMove_prev->GetNext());
       nMove_prev->SetNext(toMove);
      }
    }
    else //middle case
    {
      if (nMove_prev == nullptr) //moving to head
      {
        prev->SetNext(toMove->GetNext());
        toMove->SetNext(head);
        head = toMove;
      }
      else //general case(s)
      {
        prev->SetNext(toMove->GetNext());
        if (newPos < Pos) // in case that we are moving nodes backwards
        {
          toMove->SetNext(nMove);
         nMove_prev->SetNext(toMove);
        }
        else
        {
          toMove->SetNext(nMove->GetNext());
         nMove->SetNext(toMove);
        }
        
      }
      
    }

    cout << '"' << toMove->GetSongName() << '"' << " moved to position " << newPos << endl << endl;
  }
}
    
void Playlist::OutputSongsByArtist() const {
  string name;
  cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
  cout << "Enter artist's name:" << endl;
  getline(cin, name);
  cout << endl;
  int index = 1;
  // iterate and print if artist name equal to target
  for (const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext())
  {
    if (curr->GetArtistName() == name)
    {
      cout << index << "." << endl;
      curr->PrintPlaylistNode();
      cout << endl;
    }
    index++;
  }
}
    
void Playlist::OutputTotalTime() const {
  cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
  int time = 0;
  // iterate and accumulate total time
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    time += curr->GetSongLength();
  }

  cout << "Total time: " << time << " seconds" << endl;

}

void Playlist::OutputFullPlaylist(string title) const {
  cout << title << " - OUTPUT FULL PLAYLIST" << endl;
  if (head == nullptr) //check for empty
  {
    cout << "Playlist is empty" << endl << endl;
  }
  else
  {
    int i = 1; //numbering index, iterate through loop and print
    for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext())
    {
      cout << i << "." << endl;
      i++;
      curr->PrintPlaylistNode();
      cout << endl;
    }
  }

}