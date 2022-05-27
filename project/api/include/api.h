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

const string OAuthTokenSpotify = "BQCOfWlq_1Q2rUd9xCEPBJg8_1WNNnbh5cUiAJHJCeVBIbIVPSgg-HP-q64wuZrlr5zE9tQ-spXJL5yCdOlELvDGHBA3FKsAHbk2VyUKVJgh2mm2tEIs7G_VAuw1ONf9q704np3P_l73wOmbQ-VDO9X8rLWrf9YJeMgIDqLzAVtc--xncHo74tkIymaOrcPP8BkyEwhIoyOhLWQHVVwlw1WgR5Gav7U";
const string usedIdSpotify = "8sseequ1nh63lrksvl8pqyxta";


struct PlaylistPlatformsRefs {
    string SpotifyRef;
    string YoutubeRef;
};

struct Song {
    string songName;
    string artist;
};

struct RefsForURL {
    string ApiUrl;
    string ApiKey;
    string playlistID;
    string OAuthToken;
};

class Playlist {
public:
    Playlist() {
        playlistId = 0;
        playlistCreatorId = 0;
        playlistSize = 0;
        Refs = {"", ""};
        playlistCreator = "";
    }

    ~Playlist() {};
    int playlistId;
    int playlistCreatorId;
    string playlistCreator;
    int playlistSize;
    vector<Song> songs;
    PlaylistPlatformsRefs Refs;

    bool addSong(Song &s) {};

    bool removeSong(int number) {};

    bool swapSongs(int number1, int number2) {};

    void deletePlaylist() {};

    //bool send(uint64_t chat_id);
    //void receive(int senderId, int platform);
};

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

int requestAPI(const string &URL, const vector<string> &EHeaders, string &readBuffer, string type = "get",
               string postParameters = "{}");