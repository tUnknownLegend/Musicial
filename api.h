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

const string OAuthTokenSpotify = "BQAG8y0-_IHFyHu4KXG9v8hHRQG7EPMrxdLVqFTxZO_Lq_KJygwKgrVT1kOe7MSoS6ij4zcqz8JJEQHYtBHg8XXS8PBh_gLoM98cCn7cswfHXu8RS-7rHSyzo1FXAVBeVllgZqwb4NjcbWgLFcbQg-GX_Z-nX_yePda3RgSYu391uxvX-Y3MioSz_IJKHtiNqI2pZYGaBK2PLBkQfAapu1z3Tuy8CSY";
const string usedIdSpotify = "8sseequ1nh63lrksvl8pqyxta";


struct PlaylistPlatformsRefs{
    string SpotifyRef;
    string YoutubeRef;
};

struct Song{
    string songName;
    string artist;
};

struct RefsForURL{
    string ApiUrl;
    string ApiKey;
    string playlistID;
    string OAuthToken;
};

class Playlist{
public:
    Playlist(){
        playlistId = 0;
        playlistCreatorId = 0;
        playlistSize = 0;
        Refs = {"",""};
        playlistCreator = "";
    }   
    ~Playlist(){};
    int playlistId;
    int playlistCreatorId;
    string playlistCreator;
    int playlistSize;
    vector<Song> songs;
    PlaylistPlatformsRefs Refs;
    
    bool addSong(Song &s){};
    bool removeSong(int number){};
    bool swapSongs(int number1, int number2){};
    void deletePlaylist(){};

    //bool send(uint64_t chat_id);
    //void receive(int senderId, int platform);
};

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
int request(const string &URL, const vector<string> &EHeaders, string &readBuffer, string type = "get", string postParameters = "{}");