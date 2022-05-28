#pragma once
#include "api.h"

class URLsSetterSpotify{
    friend class PlaylistManagerSpotify;
private:
    string URLSpotifyGetPlaylistItems(string &playlistSpotifyId);
    string URLSpotifySearchSong(Song &song);
    string URLSpotifyCreateEmptyPlaylist(const string &userId);
    string URLSpotifyCreatePlaylistFromSonglist(string &playlistId);
    string URLSpotifyAddSong(string &playlistId, string &songId);
    string URLSpotifyGetSongById(string &songId);
};

class ResponseParserSpotify{
    friend class PlaylistManagerSpotify;
private:
    void ParseResponseSpotifyGetPlaylistItems(string &readBuffer, Playlist &playlist);
    string ParseResponseSpotifyGetSongId(string &readBuffer);
    string ParseResponseSpotifyCreateEmptyPlaylist(string &readBuffer);
    Song ParseResponseSpotifyGetSongById(string &readBuffer);
};

class PlaylistManagerSpotify : private URLsSetterSpotify, ResponseParserSpotify{
public:
    
    PlaylistManagerSpotify(const string &_OAuthTokenSpotify, const string &_userIdSpotify):OAuthTokenSpotify(_OAuthTokenSpotify), userIdSpotify(_userIdSpotify){}
    ~PlaylistManagerSpotify(){};
    template<typename ForwardIterator>
    string createSpotifyPlaylistFromSonglist(ForwardIterator begin, ForwardIterator end,const string &userId);

    Playlist createPlaylistFromExistingSpotifyPlaylist(string &playlistSpotifyId);
    string searchSongSpotify(Song &song);
    string createEmptyPlaylistSpotify(const string &userId);
    Song getSongByIdSpotify(string &songId);
    bool addSongSpotify(Song &song, string &playlistId);
private:
    const string OAuthTokenSpotify;
    const string userIdSpotify;

    void SetHeadersSpotify(vector<string> &headers);
};

template<typename ForwardIterator>
string PlaylistManagerSpotify::createSpotifyPlaylistFromSonglist(ForwardIterator begin, ForwardIterator end,const string &userId){
    string playlistId = createEmptyPlaylistSpotify(userId);
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
    std::cout << "Songs lost:" << missedSongsCount << std::endl;
    int res = APIrequest(URL, headers, readBuffer, "post", postParameters);
    if (res == -1){
        std::cout << "error createSpotifyPlaylistFromSonglist" << std::endl;
        return "";
    }
    return "https://open.spotify.com/playlist/" + playlistId;
}
