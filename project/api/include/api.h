#pragma once
//#ifdef X_H
//#define X_H
#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

using json = nlohmann::json;
using std::string;
using std::vector;

class Settings{
public:

    const string getOAuthTokenSpotify(){return OAuthTokenSpotify;}
    const string getUserIdSpotify(){return userIdSpotify;}
private:
    const string OAuthTokenSpotify = "BQBA3DrzQL29F9qwkuG6mniTxTgNI_xPONAgDLCQwirZyREsgQh5zlks6rccIU5Z8OrCy0yHwY_6aBYiFKja3Fs3IVqhEfTH4RUziBE62OYYTp_d9wq0tNEsBnCdd_iO2gwBRSWoBqYlwhC5w0kIN23OWiINs7hpdi8SsNeEEAjljonMud22ySEazgX0g-CKwaKQumuRFZWiq4rfTV5y9r1PzJF13Gg";
    const string userIdSpotify = "8sseequ1nh63lrksvl8pqyxta";
    string ApiKey;
};

struct Song{
    string songName;
    string artist;
};

class Playlist{
public:
    Playlist(){
        playlistId = 0;
        playlistCreatorId = 0;
        playlistSize = 0;
        playlistCreator = "";
    }   
    ~Playlist(){};
    
    vector<Song> songs;
    
    bool addSong(Song &s){songs.push_back(s);};

private:
    int playlistId;
    int playlistCreatorId;
    string playlistCreator;
    int playlistSize;
};

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
int APIrequest(const string &URL, const vector<string> &EHeaders, string &readBuffer, string type = "get", string postParameters = "{}");

string getIdFromURL(string &playlistURL);