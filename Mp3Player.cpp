//
// Created by matteo on 14/06/18.
//

#include "Mp3Player.h"

unique_ptr<Mp3Player> Mp3Player::currentPlayer(nullptr);
const float Mp3Player::defaultVolume=1;

Mp3Player::Mp3Player() : mainLibrary("#mainLibrary")
{
    srand(time(nullptr));
    Settings::Istantiate();
    setVolume(Settings::getIstance()->getSavedVolume());
    requestUpdate();
}

Mp3Player::~Mp3Player()
{

}

void Mp3Player::setVolume(float val)
{
    if(val<0 || val >100)
        val =100;
    volume=val;
}

Track& Mp3Player::getRandomTrackFromPlaylist(PlayList &list)
{
    return list.getTrack(rand());
}

void Mp3Player::setTrackPlayPoint(int seconds)
{
    currentTrackTiming=seconds;
    requestUpdate();
}