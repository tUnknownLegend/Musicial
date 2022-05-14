// #include <gtest/gtest.h>
// #include "api.h"


// TEST(Playlist, TestBasics) {
//     Song b1 = {"one","two"};
//     Song b2 = {"three","four"};
//     Playlist A;
//     A.addSong(b1);
//     EXPECT_EQ(A.playlistSize, A.songs.size());
//     A.swapSongs(0,1);
//     EXPECT_EQ(A.songs[0].songName, b2.songName);
//     EXPECT_EQ(A.songs[0].artist, b2.artist);
//     A.removeSong(1);
//     EXPECT_EQ(A.playlistSize, A.songs.size());
//     //EXPECT_EQ(A.send(1), 1);
// }

// TEST(YoutubePlaylist, TestBasics) {
//     Song b1 = {"one","two"};
//     Song b2 = {"three","four"};
//     YoutubePlaylist A;
//     A.addSong(b1);
//     EXPECT_EQ(A.playlistSize, A.songs.size());
//     A.swapSongs(0,1);
//     EXPECT_EQ(A.songs[0].songName, b2.songName);
//     EXPECT_EQ(A.songs[0].artist, b2.artist);
//     A.removeSong(1);
//     EXPECT_EQ(A.playlistSize, A.songs.size());
//     //EXPECT_EQ(A.send(1), 1);
// }

// TEST(SpotifyPlaylist, TestBasics) {
//     Song b1 = {"one","two"};
//     Song b2 = {"three","four"};
//     SpotifyPlaylist A;
//     A.addSong(b1);
//     EXPECT_EQ(A.playlistSize, A.songs.size());
//     A.swapSongs(0,1);
//     EXPECT_EQ(A.songs[0].songName, b2.songName);
//     EXPECT_EQ(A.songs[0].artist, b2.artist);
//     A.removeSong(1);
//     EXPECT_EQ(A.playlistSize, A.songs.size());
//     //EXPECT_EQ(A.send(1), 1);
// }

// TEST(createEmptyPlaylist, TestFunc) {
//     PlaylistManager<Playlist> PManager;
//     Playlist A = PManager.createEmptyPlaylist();
//     PlaylistManager<YoutubePlaylist> YPManager;
//     YoutubePlaylist B = YPManager.createEmptyPlaylist();
//     PlaylistManager<SpotifyPlaylist> SPManager;
//     SpotifyPlaylist C = SPManager.createEmptyPlaylist();
//     EXPECT_EQ(A.playlistSize, 0);
//     EXPECT_EQ(B.playlistSize, 0);
//     EXPECT_EQ(C.playlistSize, 0);
// }

// TEST(createExistingPlaylist, TestFunc) {
//     PlaylistManager<YoutubePlaylist> YPManager;
//     RefsForURL playlistRefs = {"","","",""};
//     string URL1 = GetPlaylistItemsURLYoutube(playlistRefs);
//     vector<string> headers1;
//     GetPlaylistItemsHeadersYoutube(headers1);
//     YoutubePlaylist B = YPManager.createExistingPlaylist(URL1, headers1);

//     PlaylistManager<SpotifyPlaylist> SPManager;
//     RefsForURL playlistRefs2 = {"","","",""};
//     string URL2 = GetPlaylistItemsURLSpotify(playlistRefs2);
//     vector<string> headers2;
//     GetPlaylistItemsHeadersSpotify(headers2, playlistRefs2.OAuthToken);
//     SpotifyPlaylist C = SPManager.createExistingPlaylist(URL2, headers2);
//     EXPECT_EQ(B.playlistSize, C.playlistSize);
//     if(B.playlistSize > 0 && C.playlistSize > 0){
//         EXPECT_EQ(B.songs[0].songName, C.songs[0].songName);
//         EXPECT_EQ(B.songs[0].artist, C.songs[0].artist);
//     }
// }

