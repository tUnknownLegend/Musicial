#include <gtest/gtest.h>
#include "api.h"


TEST(MusicialPlaylist, TestBasics) {
    Song b1 = {"one","two"};
    Song b2 = {"three","four"};
    MusicialPlaylist A;
    A.addSong(b1);
    EXPECT_EQ(A.playlistSize, A.songs.size());
    A.swapSongs(0,1);
    EXPECT_EQ(A.songs[0].songName, b2.songName);
    EXPECT_EQ(A.songs[0].artist, b2.artist);
    A.removeSong(1);
    EXPECT_EQ(A.playlistSize, A.songs.size());
    EXPECT_EQ(A.send(1), 1);
}

TEST(YoutubePlaylist, TestBasics) {
    Song b1 = {"one","two"};
    Song b2 = {"three","four"};
    YoutubePlaylist A;
    A.addSong(b1);
    EXPECT_EQ(A.playlistSize, A.songs.size());
    A.swapSongs(0,1);
    EXPECT_EQ(A.songs[0].songName, b2.songName);
    EXPECT_EQ(A.songs[0].artist, b2.artist);
    A.removeSong(1);
    EXPECT_EQ(A.playlistSize, A.songs.size());
    EXPECT_EQ(A.send(1), 1);
}

TEST(SpotifyPlaylist, TestBasics) {
    Song b1 = {"one","two"};
    Song b2 = {"three","four"};
    SpotifyPlaylist A;
    A.addSong(b1);
    EXPECT_EQ(A.playlistSize, A.songs.size());
    A.swapSongs(0,1);
    EXPECT_EQ(A.songs[0].songName, b2.songName);
    EXPECT_EQ(A.songs[0].artist, b2.artist);
    A.removeSong(1);
    EXPECT_EQ(A.playlistSize, A.songs.size());
    EXPECT_EQ(A.send(1), 1);
}

TEST(createEmptyPlaylist, TestFunc) {
    Playlist *A = PlaylistManager::createEmptyPlaylist();
    Playlist *B = YoutubePlaylistManager::createEmptyPlaylist();
    Playlist *C = SpotifyPlaylistManager::createEmptyPlaylist();
    EXPECT_EQ(A->playlistSize, 0);
    EXPECT_EQ(B->playlistSize, 0);
    EXPECT_EQ(C->playlistSize, 0);
}

TEST(createExistingPlaylist, TestFunc) {
    Playlist *B = YoutubePlaylistManager::createExistingPlaylist("a");
    Playlist *C = SpotifyPlaylistManager::createExistingPlaylist("a");
    EXPECT_EQ(B->playlistSize, C->playlistSize);
    if(B->playlistSize > 0 && C->playlistSize > 0){
        EXPECT_EQ(B->songs[0].songName, C->songs[0].songName);
        EXPECT_EQ(B->songs[0].artist, C->songs[0].artist);
    }
}

