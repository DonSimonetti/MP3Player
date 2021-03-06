//
// Created by matteo on 16/06/18.
//

#ifndef MP3PLAYER_TRACK_H
#define MP3PLAYER_TRACK_H

class Album;

#include <string>
#include <fstream>
#include <memory>

using namespace std;

class Track {

public:

    Track(string path);

    string title;
    string artist;
    Album * album;
    string genre;
    //bool like;

    /*int getDuration() const{
        return duration;
    }

    string getDurationStr() const;*/
    const string & getDirectory() const{
        return directory;
    }

    bool operator==(shared_ptr<Track> other);

private:

    //int duration;
    string directory;
    string getAlbumString();
    string getArtistString();
    string getFrameContent(string tag);
    unsigned int getFrameContentSize(ifstream & file, string tag);
};


#endif //MP3PLAYER_TRACK_H
