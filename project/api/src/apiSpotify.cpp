#include "apiSpotify.h"
#include <string.h>


string URLsSetterSpotify::URLSpotifyGetPlaylistItems(string &playlistSpotifyId){
    string ApiUrl = "https://api.spotify.com/v1/playlists/";
    return ApiUrl + playlistSpotifyId;
}

string URLsSetterSpotify::URLSpotifySearchSong(Song &song){
    string ApiUrl = "https://api.spotify.com/v1/search";
    string type = "type=track";
    string market = "market=ES";
    string limit = "limit=1";
    string filter = "";
    char *helpString = new char[song.songName.size() + 1];
    strcpy(helpString, song.songName.c_str());
    char *p = strtok(helpString, " ");
    while(p != NULL){
        filter += string(p);
        p = strtok(NULL, " ");
        if(p != NULL)
            filter += "%20";
    }
    delete [] helpString;
    filter += "%20";
    char *helpString2 = new char[song.artist.size() + 1];
    strcpy(helpString2, song.artist.c_str());
    p = strtok(helpString2, " ");
    while(p != NULL){
        filter += string(p);
        p = strtok(NULL, " ");
        if(p != NULL)
            filter += "%20";
    }
    string queryString = filter + "&" + type + "&" + market + "&" + limit;
    delete [] helpString2;
    return ApiUrl + "?q=" + queryString;
}

string URLsSetterSpotify::URLSpotifyCreateEmptyPlaylist(const string &userId){
    string ApiUrl = "https://api.spotify.com/v1/users/";
    return ApiUrl + userId + "/playlists";
}

string URLsSetterSpotify::URLSpotifyCreatePlaylistFromSonglist(string &playlistId){
    string ApiUrl = "https://api.spotify.com/v1/playlists/";
    return ApiUrl + playlistId + "/tracks";
}

string URLsSetterSpotify::URLSpotifyAddSong(string &playlistId, string &songId){
    string ApiUrl = "https://api.spotify.com/v1/playlists/";
    string queryString = "uris=spotify%3Atrack%3A" + songId;
    return ApiUrl + playlistId + "/tracks" + "?" + queryString;
}

string URLsSetterSpotify::URLSpotifyGetSongById(string &songId){
    string ApiUrl = "https://api.spotify.com/v1/tracks/";
    return ApiUrl + songId;
}

void PlaylistManagerSpotify::SetHeadersSpotify(vector<string> &headers){
    headers.push_back("Accept: application/json");
    headers.push_back("Content-Type: application/json");
    headers.push_back("Authorization: Bearer " + OAuthTokenSpotify);
}

void ResponseParserSpotify::ParseResponseSpotifyGetPlaylistItems(string &readBuffer, Playlist &playlist){
    //std::cout << readBuffer << std::endl;
    try{
        json responseJson = json::parse(readBuffer);
        json responseJsonItems = responseJson["tracks"]["items"];
        for (auto &songItem : responseJsonItems) {
            Song song;
            song.songName = songItem["track"]["album"]["artists"][0]["name"];
            song.artist = songItem["track"]["album"]["name"];
            playlist.songs.push_back(song);
        }
        return;
    } catch(...){
        std::cout << "Parsing error ParseResponseSpotifyGetPlaylistItems" << std::endl;
        return;
    }
}

string ResponseParserSpotify::ParseResponseSpotifyGetSongId(string &readBuffer){
    //std::cout << readBuffer << std::endl;
    try{
        json responseJson = json::parse(readBuffer);
        string songId = responseJson["tracks"]["items"][0]["id"];
        string href = responseJson["tracks"]["items"][0]["href"];
        return songId;
    } catch(...){
        std::cout << "Parsing error ParseResponseSpotifyGetSongId" << std::endl;
        return "-1";
    }
}

string ResponseParserSpotify::ParseResponseSpotifyCreateEmptyPlaylist(string &readBuffer){
    //std::cout << readBuffer << std::endl;
    try{
        json responseJson = json::parse(readBuffer);
        string playlistId = responseJson["id"];
        string href = responseJson["href"];
        return playlistId;
    } catch(...){
        std::cout << "Parsing error ParseResponseSpotifyCreateEmptyPlaylist" << std::endl;
        return "";
    }
}
Song ResponseParserSpotify::ParseResponseSpotifyGetSongById(string &readBuffer){
    //std::cout << readBuffer << std::endl;
    Song song = {"",""};
    try{
        json responseJson = json::parse(readBuffer);
        song.songName = responseJson["name"];
        song.artist = responseJson["artists"][0]["name"];
        return song;
    } catch(...){
        std::cout << "Parsing error ParseResponseSpotifyGetSongById" << std::endl;
        return song;
    }
    return song;
}


Playlist PlaylistManagerSpotify::createPlaylistFromExistingSpotifyPlaylist(string &playlistSpotifyId) {
    Playlist ans;
    string URL = URLSpotifyGetPlaylistItems(playlistSpotifyId);
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    int res = APIrequest(URL, headers, readBuffer);
    if (res == -1){
        std::cout << "error createPlaylistFromExistingSpotifyPlaylist" << std::endl;
        return ans;
    }
    ParseResponseSpotifyGetPlaylistItems(readBuffer, ans);
    return ans;
}

string PlaylistManagerSpotify::searchSongSpotify(Song &song) {
    string URL = URLSpotifySearchSong(song);
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    int res = APIrequest(URL, headers, readBuffer);
    if (res == -1){
        std::cout << "error searchSongSpotify" << std::endl;
        return "-1";
    }
    string songId = ParseResponseSpotifyGetSongId(readBuffer);
    return songId;
}

Song PlaylistManagerSpotify::getSongByIdSpotify(string &songId) {
    string URL = URLSpotifyGetSongById(songId);
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    Song song ={"",""};
    int res = APIrequest(URL, headers, readBuffer);
    if (res == -1){
        std::cout << "error getSongByIdSpotify" << std::endl;
        return song;
    }
    song = ParseResponseSpotifyGetSongById(readBuffer);
    return song;
}

string PlaylistManagerSpotify::createEmptyPlaylistSpotify(const string &userId) {
    string URL = URLSpotifyCreateEmptyPlaylist(userId);
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    json postParametersJson;
    postParametersJson["name"] = "New";
    postParametersJson["description"] = "desc";
    postParametersJson["public"] = "true";
    string postParameters = postParametersJson.dump();
    int res = APIrequest(URL, headers, readBuffer, "post", postParameters);
    if (res == -1){
        std::cout << "error createEmptyPlaylistSpotify" << std::endl;
        return "-1";
    }
    string playlistId = ParseResponseSpotifyCreateEmptyPlaylist(readBuffer);
    return playlistId;
}

bool PlaylistManagerSpotify::addSongSpotify(Song &song, string &playlistId) {
    string readBuffer;
    vector<string> headers;
    SetHeadersSpotify(headers);
    string songId = searchSongSpotify(song);
    string URL = URLSpotifyAddSong(playlistId, songId);
    int res = APIrequest(URL, headers, readBuffer, "post");
    if (res == -1){
        std::cout << "error addSongSpotify" << std::endl;
        return false;
    } 
    return true;
}
