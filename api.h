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
    const string getApiKeyYoutube(){return ApiKeyYoutube;}
    const string getOAuthTokenYoutube(){return OAuthTokenYoutube;}
private:
    const string OAuthTokenSpotify = "BQD85RvXDm89wibT3-kh5YYpKqjfeQRoGOtSfiBzINiDCG3gkxOowsQ9yB8tTEvUj1bGk_sm8BJqGlk5VxhzI9K-S60SYlXb6TDSEtk6zuRgYYp9xQzsxP3fx7h96V9P4HX0ZdGBuKOsmY3CM0egkRDoetsmNfmCKKuPtiwq9_GPoiuf_TRLxiG9cQ213QzZzsFDlwB0kFZIzbn2W2D9-sVhKncPvQM";
    const string userIdSpotify = "8sseequ1nh63lrksvl8pqyxta";
    const string ApiKeyYoutube = "AIzaSyC3-MWvfyHVPjEVn8XYZd-HMVpc_mlxNHE";
    const string OAuthTokenYoutube = "ya29.a0ARrdaM8ORK_a9u7KTOjo5qi23HT6Ptu6yxqQ-D01wMo9zbpn41NKrQNZUVH3zHr1Z8Q9wXQVWoGcBPZT21lgNSpAS40KIoX5dPsBKSYSMIFirADejjgT9a7I4KWp1s948xXkl5cYHpONv_2fnqaVMqFiOI1T_w";

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