#pragma once
#include "apiSpotify.h"
#include "apiYoutube.h"

template<typename ForwardIterator1, typename ForwardIterator2>
string createYoutubePlaylistFromPlatformRefsAndSongsLists(ForwardIterator1 PlatformRefsBegin, ForwardIterator1 PlatformRefsEnd, ForwardIterator2 songListBegin, ForwardIterator2 songListEnd){
    vector<Song> finalSongList;
    Settings S;
    PlaylistManagerYoutube ManagerYoutube(S.getApiKeyYoutube(), S.getOAuthTokenYoutube());
    PlaylistManagerSpotify ManagerSpotify(S.getOAuthTokenSpotify(), S.getUserIdSpotify());
    for(ForwardIterator1 it = PlatformRefsBegin; it != PlatformRefsEnd; it++){
        string playlistRef = (*it);

        if(playlistRef.find("spotify") < playlistRef.size()){
            string playlistId = getIdFromURL(playlistRef);
            Playlist helpPlaylist = ManagerSpotify.createPlaylistFromExistingSpotifyPlaylist(playlistId);
            for(int i = 0; i < helpPlaylist.songs.size(); i++)
                finalSongList.push_back(helpPlaylist.songs[i]);
        }

        if(playlistRef.find("youtube") < playlistRef.size()){
            string playlistId = getIdFromURL(playlistRef);
            Playlist helpPlaylist = ManagerYoutube.createPlaylistFromExistingYoutubePlaylist(playlistId);
            for(int i = 0; i < helpPlaylist.songs.size(); i++)
                finalSongList.push_back(helpPlaylist.songs[i]);
        }
    }
    for(ForwardIterator2 it = songListBegin; it != songListEnd; it++){
        string songRef = (*it);

        if(songRef.find("spotify") < songRef.size()){
            string songId = getIdFromURL(songRef);
            Song song =  ManagerSpotify.getSongByIdSpotify(songId);
            if(song.artist.size()>0 || song.songName.size()>0)
                finalSongList.push_back(song);
        }

        if(songRef.find("youtube") < songRef.size()){
            string songId = getIdFromURL(songRef);
            Song song =  ManagerYoutube.getSongByIdYoutube(songId);
            if(song.artist.size()>0 || song.songName.size()>0)
                finalSongList.push_back(song);
        }
    }
    if(finalSongList.size() > 10){
        return "Too many songs";
    }
    string ref = ManagerYoutube.createYoutubePlaylistFromSonglist(finalSongList.begin(), finalSongList.end());
    return ref;
}

template<typename ForwardIterator1, typename ForwardIterator2>
string createSpotifyPlaylistFromPlatformRefsAndSongsLists(ForwardIterator1 PlatformRefsBegin, ForwardIterator1 PlatformRefsEnd, ForwardIterator2 songListBegin, ForwardIterator2 songListEnd,const string &userId){
    vector<Song> finalSongList;
    Settings S;
    PlaylistManagerYoutube ManagerYoutube(S.getApiKeyYoutube(), S.getOAuthTokenYoutube());
    PlaylistManagerSpotify ManagerSpotify(S.getOAuthTokenSpotify(), S.getUserIdSpotify());
    for(ForwardIterator1 it = PlatformRefsBegin; it != PlatformRefsEnd; it++){
        string playlistRef = (*it);
        if(playlistRef.find("spotify") < playlistRef.size()){
            string playlistId = getIdFromURL(playlistRef);
            Playlist helpPlaylist = ManagerSpotify.createPlaylistFromExistingSpotifyPlaylist(playlistId);
            for(int i = 0; i < helpPlaylist.songs.size(); i++)
                finalSongList.push_back(helpPlaylist.songs[i]);
        }

        if(playlistRef.find("youtube") < playlistRef.size()){
            string playlistId = getIdFromURL(playlistRef);
            Playlist helpPlaylist = ManagerYoutube.createPlaylistFromExistingYoutubePlaylist(playlistId);
            for(int i = 0; i < helpPlaylist.songs.size(); i++)
                finalSongList.push_back(helpPlaylist.songs[i]);
        }
    }
    for(ForwardIterator2 it = songListBegin; it != songListEnd; it++){
        string songRef = (*it);
        if(songRef.find("spotify") < songRef.size()){
            string songId = getIdFromURL(songRef);
            Song song =  ManagerSpotify.getSongByIdSpotify(songId);
            if(song.artist.size()>0 || song.songName.size()>0)
                finalSongList.push_back(song);
        }

        if(songRef.find("youtube") < songRef.size()){
            string songId = getIdFromURL(songRef);
            Song song =  ManagerYoutube.getSongByIdYoutube(songId);
            if(song.artist.size()>0 || song.songName.size()>0)
                finalSongList.push_back(song);
        }
    }
    if(finalSongList.size() > 99){
        return "Too many songs";
    }
    string ref = ManagerSpotify.createSpotifyPlaylistFromSonglist(finalSongList.begin(), finalSongList.end(), userId);
    return ref;
}
