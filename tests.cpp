 #include <gtest/gtest.h>
// #include "api.h"
#include "apiConvertHandlers.h"

TEST(Playlist, TestBasics) {
    Song b1 = {"one","two"};
    Song b2 = {"three","four"};
    Playlist A;
    A.addSong(b1);
    A.addSong(b2);
    EXPECT_EQ(2, A.songs.size());
}

TEST(createYoutubePlaylistFromPlatformRefs, TestBasics) {
    Settings S;
    PlaylistManagerYoutube A(S.getApiKeyYoutube(), S.getOAuthTokenYoutube());
    string plref1 = "https://youtube.com/playlist?list=PL6AVWk5NUegW4wPkPtFE5FXXvoeyBEZYI";
    string songref1 = "https://www.youtube.com/watch?v=bESGLojNYSo";
    vector<string> songs;
    vector<string> play;
    songs.push_back(songref1);
    play.push_back(plref1);
    string ref = createYoutubePlaylistFromPlatformRefsAndSongsLists(play.begin(), play.end(), songs.begin(), songs.end());
    Playlist P = createPlaylistFromExistingYoutubePlaylist(ref);
    EXPECT_EQ(2, A.songs.size());
}

TEST(createYoutubePlaylistFromPlatformRefs, TestBasics) {
    Settings S;
    PlaylistManagerSpotify A(S.getApiKeyYoutube(), S.getOAuthTokenYoutube());
    string plref1 = "https://youtube.com/playlist?list=PL6AVWk5NUegW4wPkPtFE5FXXvoeyBEZYI";
    string songref1 = "https://www.youtube.com/watch?v=bESGLojNYSo";
    vector<string> songs;
    vector<string> play;
    songs.push_back(songref1);
    play.push_back(plref1);
    string ref = createSpotifyPlaylistFromPlatformRefsAndSongsLists(play.begin(), play.end(), songs.begin(), songs.end());
    Playlist P = createPlaylistFromExistingSpotifyPlaylist(ref);
    EXPECT_EQ(2, A.songs.size());
}

TEST(createEmptyPlaylist, TestFunc) {
    string ref = "https://www.youtube.com/watch?v=bESGLojNYSo";
    Song s1 = A.getSongByIdYoutube(ref);
}

