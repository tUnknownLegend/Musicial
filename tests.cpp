#include <gtest/gtest.h>
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
    string plref1 = "https://open.spotify.com/playlist/44dZArICqiIPwmMqFsoood";
    string plref2 = "https://www.youtube.com/playlist?list=PLcidtVPGDsUVA5uiD4s4KijPe5ARDVPdb";
    string songref1 = "https://www.youtube.com/watch?v=RubBzkZzpUA";
    string songref2 = "https://open.spotify.com/track/5BwQjRasNcdRPuVWKcHto2";
    vector<string> songs;
    vector<string> play;
    songs.push_back(songref1);
    play.push_back(plref1);
    songs.push_back(songref2);
    play.push_back(plref2);
    string ref = createYoutubePlaylistFromPlatformRefsAndSongsLists(play.begin(), play.end(), songs.begin(), songs.end());
    EXPECT_EQ(ref == "", false);
}

TEST(createSpotifyPlaylistFromPlatformRefs, TestBasics) {
    Settings S;
    PlaylistManagerSpotify A(S.getOAuthTokenSpotify(), S.getUserIdSpotify());
    string plref1 = "https://open.spotify.com/playlist/44dZArICqiIPwmMqFsoood";
    string plref2 = "https://www.youtube.com/playlist?list=PLcidtVPGDsUVA5uiD4s4KijPe5ARDVPdb";
    string songref1 = "https://www.youtube.com/watch?v=RubBzkZzpUA";
    string songref2 = "https://open.spotify.com/track/5BwQjRasNcdRPuVWKcHto2";
    vector<string> songs;
    vector<string> play;
    songs.push_back(songref1);
    play.push_back(plref1);
    songs.push_back(songref2);
    play.push_back(plref2);
    string ref = createSpotifyPlaylistFromPlatformRefsAndSongsLists(play.begin(), play.end(), songs.begin(), songs.end(), S.getUserIdSpotify());
    EXPECT_EQ(ref == "", false);
}

TEST(findSongYoutube, TestFunc) {
    Settings S;
    PlaylistManagerYoutube A(S.getApiKeyYoutube(), S.getOAuthTokenYoutube());
    string ref = "https://www.youtube.com/watch?v=RubBzkZzpUA";
    Song s1 = A.getSongByIdYoutube(ref);
    EXPECT_EQ(s1.songName == "", false);
    EXPECT_EQ(s1.artist == "", false);
}

TEST(getPlaylistItemsYoutube, TestFunc) {
    Settings S;
    PlaylistManagerYoutube A(S.getApiKeyYoutube(), S.getOAuthTokenYoutube());
    string ref = "https://www.youtube.com/playlist?list=PLcidtVPGDsUVA5uiD4s4KijPe5ARDVPdb";
    string playlistId = getIdFromURL(ref);
    Playlist ans = A.createPlaylistFromExistingYoutubePlaylist(playlistId);
    EXPECT_EQ(ans.songs.size() == 0, false);
}

TEST(findSongSpotify, TestFunc) {
    Settings S;
    PlaylistManagerSpotify A(S.getOAuthTokenSpotify(), S.getUserIdSpotify());
    string ref = "https://open.spotify.com/track/5BwQjRasNcdRPuVWKcHto2";
    Song s1 = A.getSongByIdSpotify(ref);
    EXPECT_EQ(s1.songName == "", false);
    EXPECT_EQ(s1.artist == "", false);
}

TEST(getPlaylistItemsSpotify, TestFunc) {
    Settings S;
    PlaylistManagerSpotify A(S.getOAuthTokenSpotify(), S.getUserIdSpotify());
    string ref = "https://open.spotify.com/playlist/44dZArICqiIPwmMqFsoood";
    string playlistId = getIdFromURL(ref);
    Playlist ans = A.createPlaylistFromExistingSpotifyPlaylist(playlistId);
    EXPECT_EQ(ans.songs.size() != 0, true);
}

