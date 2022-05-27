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

    template<typename ForwardIterator1, typename ForwardIterator2>
    string createSpotifyPlaylistFromPlatformRefsAndSongsLists(ForwardIterator1 PlatformRefsBegin, ForwardIterator1 PlatformRefsEnd, ForwardIterator2 songListBegin, ForwardIterator2 songListEnd,const string &userId);
private:
    const string OAuthTokenSpotify;
    const string userIdSpotify;

    void SetHeadersSpotify(vector<string> &headers);
    Playlist createPlaylistFromExistingSpotifyPlaylist(string &playlistSpotifyId);
    string searchSongSpotify(Song &song);
    string createEmptyPlaylistSpotify(const string &userId);
    Song getSongByIdSpotify(string &songId);
    bool addSongSpotify(Song &song, string &playlistId);
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

template<typename ForwardIterator1, typename ForwardIterator2>
string PlaylistManagerSpotify::createSpotifyPlaylistFromPlatformRefsAndSongsLists(ForwardIterator1 PlatformRefsBegin, ForwardIterator1 PlatformRefsEnd, ForwardIterator2 songListBegin, ForwardIterator2 songListEnd,const string &userId){
    vector<Song> finalSongList;
    for(ForwardIterator1 it = PlatformRefsBegin; it != PlatformRefsEnd; it++){
        string playlistRef = (*it);

        if(playlistRef.find("spotify") < playlistRef.size()){
            string playlistId = getIdFromURL(playlistRef);
            Playlist helpPlaylist = createPlaylistFromExistingSpotifyPlaylist(playlistId);
            for(int i = 0; i < helpPlaylist.songs.size(); i++)
                finalSongList.push_back(helpPlaylist.songs[i]);
        }

        // if(playlistRef.find("youtube") < playlistRef.size()){
        //     string playlistId = getIdFromURL(playlistRef);
        //     Playlist helpPlaylist = createPlaylistFromExistingYoutubePlaylist(playlistId);
        //     for(int i = 0; i < helpPlaylist.songs.size(); i++)
        //         finalSongList.push_back(helpPlaylist.songs[i]);
        // }
    }
    for(ForwardIterator2 it = songListBegin; it != songListEnd; it++){
        string songRef = (*it);

        if(songRef.find("spotify") < songRef.size()){
            string songId = getIdFromURL(songRef);
            Song song =  getSongByIdSpotify(songId);
            if(song.artist.size()>0 || song.songName.size()>0)
                finalSongList.push_back(song);
        }

        // if(playlistRef.find("youtube") < playlistRef.size()){
        //     string playlistId = getPlaylistIdFromURL(playlistRef);
        //     Playlist heplPlaylist = createPlaylistFromExistingYoutubePlaylist(playlistId);
        //     for(int i = 0; i < heplPlaylist.songs.size(); i++)
        //         finalSongList.push_back(heplPlaylist.songs[i]);
        // }
    }
    if(finalSongList.size() > 99){
        return "Too many songs";
    }
    string ref = createSpotifyPlaylistFromSonglist(finalSongList.begin(), finalSongList.end(), userId);
    return ref;
}