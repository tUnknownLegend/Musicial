#include "apiSpotify.h"
#include <string.h>


string URLSpotifyGetPlaylistItems(string &playlistSpotifyId) {
    string ApiUrl = "https://api.spotify.com/v1/playlists/";
    return ApiUrl + playlistSpotifyId;
}

string URLSpotifySearchSong(Song &song) {
    string ApiUrl = "https://api.spotify.com/v1/search";
    string type = "type=track";
    string market = "market=ES";
    string limit = "limit=1";
    string filter = "";
    char *helpString = new char[song.songName.size() + 1];
    strcpy(helpString, song.songName.c_str());
    char *p = strtok(helpString, " ");
    while (p != NULL) {
        filter += string(p);
        p = strtok(NULL, " ");
        if (p != NULL)
            filter += "%20";
    }
    delete[] helpString;
    filter += "%20";
    char *helpString2 = new char[song.artist.size() + 1];
    strcpy(helpString2, song.artist.c_str());
    p = strtok(helpString2, " ");
    while (p != NULL) {
        filter += string(p);
        p = strtok(NULL, " ");
        if (p != NULL)
            filter += "%20";
    }
    string queryString = filter + "&" + type + "&" + market + "&" + limit;
    delete[] helpString2;
    return ApiUrl + "?q=" + queryString;
}

string URLSpotifyCreateEmptyPlaylist(const string &userId) {
    string ApiUrl = "https://api.spotify.com/v1/users/";
    return ApiUrl + userId + "/playlists";
}

string URLSpotifyCreatePlaylistFromSonglist(string &playlistId) {
    string ApiUrl = "https://api.spotify.com/v1/playlists/";
    return ApiUrl + playlistId + "/tracks";
}

string URLSpotifyAddSong(string &playlistId, string &songId) {
    string ApiUrl = "https://api.spotify.com/v1/playlists/";
    string queryString = "uris=spotify%3Atrack%3A" + songId;
    return ApiUrl + playlistId + "/tracks" + "?" + queryString;
}

void SetHeadersSpotify(vector<string> &headers) {
    headers.push_back("Accept: application/json");
    headers.push_back("Content-Type: application/json");
    headers.push_back("Authorization: Bearer " + OAuthTokenSpotify);
}

void ParseResponseSpotifyGetPlaylistItems(string &readBuffer, Playlist &playlist) {
    //std::cout << readBuffer << std::endl;
    try {
        json responseJson = json::parse(readBuffer);
        json responseJsonItems = responseJson["tracks"]["items"];
        for (auto songItem: responseJsonItems) {
            Song song;
            song.songName = songItem["track"]["album"]["artists"][0]["name"];
            song.artist = songItem["track"]["album"]["name"];
            playlist.songs.push_back(song);
        }
        return;
    } catch (...) {
        std::cout << "Parsing error // ParseResponseSpotifyGetPlaylistItems" << std::endl;
        return;
    }
}

string ParseResponseSpotifyGetSongId(string &readBuffer) {
    //std::cout << readBuffer << std::endl;
    try {
        json responseJson = json::parse(readBuffer);
        string songId = responseJson["tracks"]["items"][0]["id"];
        string href = responseJson["tracks"]["items"][0]["href"];
        //std::cout << songId << std::endl;
        //std::cout << href << std::endl;
        return songId;
    } catch (...) {
        std::cout << "Parsing error // ParseResponseSpotifyGetSongId" << std::endl;
        return "-1";
    }
}

string ParseResponseSpotifyCreateEmptyPlaylist(string &readBuffer) {
    //std::cout << readBuffer << std::endl;
    try {
        json responseJson = json::parse(readBuffer);
        string playlistId = responseJson["id"];
        string href = responseJson["href"];
        //std::cout << playlistId << std::endl;
        //std::cout << href << std::endl;
        return playlistId;
    } catch (...) {
        std::cout << "Parsing error // ParseResponseSpotifyCreateEmptyPlaylist" << std::endl;
        return "";
    }
}

Playlist createPlaylistFromExistingSpotifyPlaylist(string &playlistSpotifyId) {
    Playlist ans;
    string URL = URLSpotifyGetPlaylistItems(playlistSpotifyId);
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    int res = requestAPI(URL, headers, readBuffer);
    if (res == -1) {
        std::cout << "error" << std::endl;
        return ans;
    }
    ParseResponseSpotifyGetPlaylistItems(readBuffer, ans);
    ans.playlistSize = ans.songs.size();
    return ans;
}

string searchSongSpotify(Song &song) {
    string URL = URLSpotifySearchSong(song);
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    int res = requestAPI(URL, headers, readBuffer);
    if (res == -1) {
        std::cout << "error" << std::endl;
        return "-1";
    }
    string songId = ParseResponseSpotifyGetSongId(readBuffer);
    return songId;
}

string createEmptyPlaylistSpotify(const string &userId) {
    string URL = URLSpotifyCreateEmptyPlaylist(userId);
    //std::cout << URL << std::endl;
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    json postParametersJson;
    postParametersJson["name"] = "New";
    postParametersJson["description"] = "desc";
    postParametersJson["public"] = "true";
    string postParameters = postParametersJson.dump();
    int res = requestAPI(URL, headers, readBuffer, "post", postParameters);
    if (res == -1) {
        std::cout << "error" << std::endl;
        return "-1";
    }
    string playlistId = ParseResponseSpotifyCreateEmptyPlaylist(readBuffer);
    return playlistId;
}

bool addSongSpotify(Song &song, string &playlistId) {
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    string songId = searchSongSpotify(song);
    string URL = URLSpotifyAddSong(playlistId, songId);
    int res = requestAPI(URL, headers, readBuffer, "post");
    if (res == -1) {
        std::cout << "error" << std::endl;
        return false;
    }
    return true;
}

/*
 template<typename ForwardIterator>
 string createSpotifyPlaylistFromSonglist(ForwardIterator begin, ForwardIterator end, const string &userId){
     string playlistId = createEmptyPlaylistSpotify(usedIdSpotify);
     string URL = URLSpotifyCreatePlaylistFromSonglist(playlistId);
     string readBuffer;
     vector<string> headers;
     SetHeadersSpotify(headers);
     json postParametersJson;
     postParametersJson["uris"] = json::array();
     int missedSongsCount = 0;
     for(ForwardIterator it = begin; it != end; it++){
         string songId = searchSongSpotify(*it);
         if(songId == "-1"){
             missedSongsCount++;
         }
         else{
             postParametersJson["uris"].push_back("spotify:track:"+ songId);
             //std::cout <<  (*it).songName << " - " <<(*it).artist << std::endl;
         }
     }
     string postParameters = postParametersJson.dump();
     std::cout << postParameters << std::endl;
     int res = requestAPI(URL, headers, readBuffer, "post", postParameters);
     if (res == -1){
         std::cout << "error" << std::endl;
         return "";
     }
     return "https://open.spotify.com/playlist/" + playlistId;
 }
 */