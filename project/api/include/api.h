//#pragma once

#define X_H
#include <iostream>
#include <vector>
#include <string>
#include "curl/curl.h"
#include "json.hpp"

using json = nlohmann::json;
using std::string;
using std::vector;

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
    std::string playlistCreator;
    int playlistSize;
    std::vector<Song> songs;
    PlaylistPlatformsRefs Refs;

    virtual bool addSong(Song &s){};
    virtual bool removeSong(int number){};
    virtual bool swapSongs(int number1, int number2){};
    void deletePlaylist(){};

    //bool send(uint64_t chat_id);
    //void receive(int senderId, int platform);
};

class YoutubePlaylist:public Playlist{
public:
    bool addSong(Song &s) override{};
    bool removeSong(int number) override{};
    bool swapSongs(int number1, int number2) override{};
    //void deletePlaylist(){};
};

class SpotifyPlaylist:public Playlist{
public:
    bool addSong(Song &s) override{};
    bool removeSong(int number) override{};
    bool swapSongs(int number1, int number2) override{};
    //void deletePlaylist(){};
};

template<class T>
class PlaylistManager {
public:
    T createEmptyPlaylist();
    T createExistingPlaylist(string &URL, vector<string> &headers);
};

// class YoutubePlaylistManager{
// public:
//     //YoutubePlaylist createEmptyPlaylist() override{};
//     //void deletePlaylist() override{};
//     YoutubePlaylist createExistingPlaylist(RefsForURL &playlistRefs);
// };

// class SpotifyPlaylistManager:public PlaylistManager {
// public:
//     Playlist createEmptyPlaylist() override{};
//     void deletePlaylist() override{};
//     Playlist createExistingPlaylist(std::string &url);
// };

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int request(const string &URL, const vector<string> &EHeaders, string &readBuffer)
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl)
    {
        struct curl_slist *headers = NULL;
        const char *constURL = URL.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, constURL);
        for (int i = 0; i < EHeaders.size(); i++)
        {
            const char *constHeader = EHeaders[i].c_str();
            curl_slist_append(headers, constHeader);
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return -1;
        }
        return 1;
    }
}

string GetPlaylistItemsURLYoutube(RefsForURL &playlistRef){
    return playlistRef.ApiUrl + "?part=snippet&playlistId=" + playlistRef.playlistID + "&key=" + playlistRef.ApiKey;
}
void GetPlaylistItemsHeadersYoutube(vector<string> &headers){
    headers.push_back("Accept: application/json");
}
template<class T>
void ParseResponseGetPlaylistItemsYoutube(string &readBuffer, T &playlist){
    json responseJson = json::parse(readBuffer);
    json responseJsonItems = responseJson["items"];
    for (auto songItem : responseJsonItems)
    {
        const char separator = '-';
        std::string str = songItem["snippet"]["title"];
        Song song;
        song.songName = str.substr(0, str.find(separator));
        if (song.songName.size() != str.size())
        {
            str.erase(0, str.find(separator) + 1);
            song.artist = str;
        }
        playlist.songs.push_back(song);
    }
}

string GetPlaylistItemsURLSpotify(RefsForURL &playlistRef){
    return playlistRef.ApiUrl + playlistRef.playlistID;
}
void GetPlaylistItemsHeadersSpotify(vector<string> &headers, string &OAuthToken){
    headers.push_back("Accept: application/json");
    headers.push_back("Content-Type: application/json");
    string s = "Authorization: Bearer " + OAuthToken;
    //std::cout<< s <<std::endl;
    headers.push_back(s);
}
template<class T>
void ParseResponseGetPlaylistItemsSpotify(string &readBuffer, T &playlist){
    json responseJson = json::parse(readBuffer);
    json responseJsonItems = responseJson["tracks"]["items"];
    std::cout << readBuffer <<std::endl;
    for (auto songItem : responseJsonItems)
    {
        Song song;
        song.songName = songItem["track"]["album"]["artists"][0]["name"];
        song.artist = songItem["track"]["album"]["name"];
        playlist.songs.push_back(song);
    }
}


template<class T>
T PlaylistManager<T>::createEmptyPlaylist(){}

template<class T>
T PlaylistManager<T>::createExistingPlaylist(string &URL, vector<string> &headers)
{
    T ans;
    string readBuffer;
    int res = request(URL, headers, readBuffer);
    if (res == -1){
        std::cout << "error" << std::endl;
        return ans;
    }

    if(URL.find("youtube") < URL.size()){
        ParseResponseGetPlaylistItemsYoutube(readBuffer, ans);
        ans.Refs.YoutubeRef = URL;
    }
    if(URL.find("spotify") < URL.size()){
        ParseResponseGetPlaylistItemsSpotify(readBuffer, ans);
        ans.Refs.SpotifyRef = URL;
    }
    ans.playlistSize = ans.songs.size();
    return ans;
}