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

const string OAuthTokenSpotify = "BQBTQRJVGb-iV0Q-3hEAjkWUiHtwvQYonZLv3Pca9PLn13E8g_rq6Y9JHHqubCpuJyq8vNiwZP_DyE_Od5USQ4JrvQ74Xsm_C4NbiQqODYummzxEc5GKSW1KzaYfZBvpxXU4AdNYdCx4XaWdGUrFBSAlK6h9Tg2tsxY69MNILui3X67EIDUzI1qX2ovC6sD1maBTqvaC0yvaSwPLBXKK5-sbLn4H0jI";
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