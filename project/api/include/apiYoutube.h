#pragma once
#include "api.h"

 class URLsSetterYoutube{
public:
    
    URLsSetterYoutube(const string &_ApiKeyYoutube, const string &_OAuthTokenYoutube):ApiKeyYoutube(_ApiKeyYoutube),OAuthTokenYoutube(_OAuthTokenYoutube){}
    ~URLsSetterYoutube(){};
    friend class PlaylistManagerYoutube;
private:
    const string ApiKeyYoutube;
    const string OAuthTokenYoutube;
    string URLYoutubeGetPlaylistItems(string &playlistYoutubeId);
    string URLYoutubeSearchSong(Song &song);
    string URLYoutubeCreateEmptyPlaylist();
    string URLYoutubeCreatePlaylistFromSonglist(string &playlistId);
    string URLYoutubeAddSong();
    string URLYoutubeGetSongById(string &songId);
};

class ResponseParserYoutube{
    friend class PlaylistManagerYoutube;
private:
    void ParseResponseYoutubeGetPlaylistItems(string &readBuffer, Playlist &playlist);
    string ParseResponseYoutubeGetSongId(string &readBuffer);
    string ParseResponseYoutubeCreateEmptyPlaylist(string &readBuffer);
    Song ParseResponseYoutubeGetSongById(string &readBuffer);
};

class PlaylistManagerYoutube : ResponseParserYoutube{
public:
    
    PlaylistManagerYoutube(const string &_ApiKeyYoutube, const string &_OAuthTokenYoutube)
        :
        ApiKeyYoutube(_ApiKeyYoutube),
         OAuthTokenYoutube(_OAuthTokenYoutube),
          URLsSetter(URLsSetterYoutube(ApiKeyYoutube,OAuthTokenYoutube)){}
    ~PlaylistManagerYoutube(){};
    template<typename ForwardIterator>
    string createYoutubePlaylistFromSonglist(ForwardIterator begin, ForwardIterator end);

    Playlist createPlaylistFromExistingYoutubePlaylist(string &playlistId);
    string searchSongYoutube(Song &song);
    string createEmptyPlaylistYoutube();
    Song getSongByIdYoutube(string &songId);
    bool addSongYoutube(Song &song, string &playlistId);
private:
    
    const string ApiKeyYoutube;
    const string OAuthTokenYoutube;
    URLsSetterYoutube URLsSetter;
    
    void SetHeadersYoutube(vector<string> &headers);
};

template<typename ForwardIterator>
string PlaylistManagerYoutube::createYoutubePlaylistFromSonglist(ForwardIterator begin, ForwardIterator end){
    string playlistId = createEmptyPlaylistYoutube();
    string URL = URLsSetter.URLYoutubeCreatePlaylistFromSonglist(playlistId);
    string readBuffer;
    vector<string> headers;
    SetHeadersYoutube(headers);
    int missedSongsCount = 0;
    for(ForwardIterator it = begin; it != end; it++){
        //string songId = searchSongYoutube(*it);
        if(addSongYoutube(*it, playlistId) == false){
            missedSongsCount++;
        }
    }
    std::cout << "Songs lost:" << missedSongsCount << std::endl;
    return "https://youtube.com/playlist?list=" + playlistId;
}

