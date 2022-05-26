#pragma once

#include "api.h"

// class YoutubePlaylist:public Playlist{
// public:
//     bool addSong(Song &s) override{};
//     bool removeSong(int number) override{};
//     bool swapSongs(int number1, int number2) override{};
//     //void deletePlaylist(){};
// };

// class YoutubePlaylistManager{
// public:
//     //YoutubePlaylist createEmptyPlaylist() override{};
//     //void deletePlaylist() override{};
//     YoutubePlaylist createExistingPlaylist(RefsForURL &playlistRefs);
// };

template<typename ForwardIterator>
string createYoutubePlaylistFromSonglist(ForwardIterator begin, ForwardIterator end) {
    Playlist playlist;
    int missedSongsCount = 0;
    for (ForwardIterator it = begin; it != end; it++) {
        //if(!playlist.addSong(*it))
        //    missedSongsCount++;
        std::cout << (*it).songName << " - " << (*it).artist << std::endl;
    }
    string playlistURL = "";
    //playlist.Refs
    return playlistURL;
}


string GetPlaylistItemsURLYoutube(RefsForURL &playlistRef) {
    return playlistRef.ApiUrl + "?part=snippet&playlistId=" + playlistRef.playlistID + "&key=" + playlistRef.ApiKey;
}

void SetPlaylistItemsHeadersYoutube(vector<string> &headers) {
    headers.push_back("Accept: application/json");
}

void ParseResponseGetPlaylistItemsYoutube(string &readBuffer, Playlist &playlist) {
    json responseJson = json::parse(readBuffer);
    json responseJsonItems = responseJson["items"];
    for (auto songItem: responseJsonItems) {
        const char separator = '-';
        std::string str = songItem["snippet"]["title"];
        Song song;
        song.songName = str.substr(0, str.find(separator));
        if (song.songName.size() != str.size()) {
            str.erase(0, str.find(separator) + 1);
            song.artist = str;
        }
        playlist.songs.push_back(song);
    }
}

Playlist createPlaylistFromExistingYoutubePlaylist(string &URL, vector<string> &headers) {
    Playlist ans;
    string readBuffer;
    int res = requestAPI(URL, headers, readBuffer);
    if (res == -1) {
        std::cout << "error" << std::endl;
        return ans;
    }

    ParseResponseGetPlaylistItemsYoutube(readBuffer, ans);
    ans.Refs.YoutubeRef = URL;

    // if(URL.find("spotify") < URL.size()){
    //     ParseResponseGetPlaylistItemsSpotify(readBuffer, ans);
    //     ans.Refs.SpotifyRef = URL;
    // }
    ans.playlistSize = ans.songs.size();
    return ans;
}