//
// Created by matteo on 16/06/18.
//

#include <iostream>
#include "Track.h"

Track::Track(string path) : directory(path)
{
    title=path;
    title.erase(0,title.find_last_of("/")+1);
    //TODO Retrieve other infos (album name, artists, duration ...)
    artist=getArtistString();
}


//FIXME
string Track::getFrameContent(string tag)
{
    string content;
    try
    {
        ifstream mainFile;
        mainFile.open(directory, ios::out | ios::binary | ios::app);

        if (mainFile) {
            size_t posCounter = 0;

            while (mainFile.good()) {
                string line;
                getline(mainFile, line);
                size_t tagPos = line.find(tag);

                if (tagPos != string::npos) {
                    unsigned int siz = getFrameContentSize(mainFile, tag);
                    tagPos++;//Points to 'T'
                    size_t seekPos = tagPos + posCounter;

                    //Retrieve string
                    mainFile.seekg(seekPos + 4 + 4 + 2);

                    char *string1 = new char[siz];
                    mainFile.read(string1, siz);

                    content = string(string1);
                    delete[] string1;
                    content.erase(siz, content.length());

                    break;
                } else {
                    posCounter += line.length() + 1;
                }
            }
        }
    }
    catch (std::exception &e)
    {
        cerr<<"Exception occurred with \""<<directory<<"\""<<endl;
        cerr<<e.what()<<endl;
    }
    return content;
}

string Track::getAlbumString()
{
    return getFrameContent("TALB");
}

string Track::getArtistString()
{
    return getFrameContent("TPE1");
}

unsigned int Track::getFrameContentSize(ifstream & file, string tag)
{
    unsigned int result=0;
    size_t posCounter=0;
    file.seekg(0);
    while (file.good())
    {
        string line;
        getline(file,line);
        size_t tagPos=line.find(tag);

        if(tagPos!=string::npos)
        {
            size_t seekPos=tagPos+posCounter;
            seekPos+=4;
            file.seekg(seekPos);

            char sizePtr[4];
            file.read(sizePtr, sizeof(sizePtr));

            for (int i = 0; i <4; ++i)
                result += sizePtr[i] << (24 - i * 8);
        }
        else
        {
            posCounter+=line.length()+1;
        }
    }
    file.seekg(0);
    return --result;
}
bool Track::operator==(shared_ptr<Track> other)
{
    bool isequal = true;
    if((title!=other->title) || (artist!=other->artist))
        isequal = false;
    return isequal;
}