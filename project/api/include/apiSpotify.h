#pragma once

#include "api.h"

string URLSpotifyGetPlaylistItems(string &playlistSpotifyId);

string URLSpotifySearchSong(Song &song);

string URLSpotifyCreateEmptyPlaylist(const string &userId);

string URLSpotifyCreatePlaylistFromSonglist(string &playlistId);

string URLSpotifyAddSong(string &playlistId, string &songId);

void SetHeadersSpotify(vector<string> &headers);

void ParseResponseSpotifyGetPlaylistItems(string &readBuffer, Playlist &playlist);

string ParseResponseSpotifyGetSongId(string &readBuffer);

string ParseResponseSpotifyCreateEmptyPlaylist(string &readBuffer);

Playlist createPlaylistFromExistingSpotifyPlaylist(string &playlistSpotifyId);

string searchSongSpotify(Song &song);

string createEmptyPlaylistSpotify(const string &userId);

bool addSongSpotify(Song &song, string &playlistId);

template<typename ForwardIterator>
string createSpotifyPlaylistFromSonglist(ForwardIterator begin, ForwardIterator end, const string &userId) {
    string playlistId = createEmptyPlaylistSpotify(usedIdSpotify);
    string URL = URLSpotifyCreatePlaylistFromSonglist(playlistId);
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    json postParametersJson;
    postParametersJson["uris"] = json::array();
    int missedSongsCount = 0;
    for (ForwardIterator it = begin; it != end; it++) {
        string songId = searchSongSpotify(*it);
        if (songId == "-1") {
            missedSongsCount++;
        } else {
            postParametersJson["uris"].push_back("spotify:track:" + songId);
            //std::cout <<  (*it).songName << " - " <<(*it).artist << std::endl; 
        }
    }
    string postParameters = postParametersJson.dump();
    std::cout << postParameters << std::endl;
    int res = requestAPI(URL, headers, readBuffer, "post", postParameters);
    if (res == -1) {
        std::cout << "error" << std::endl;
        return "";
    }
    return "https://open.spotify.com/playlist/" + playlistId;
}