#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "mainlib.h"
//#include "mainlib.cpp"

class mockMessageGroup {
public:
    MOCK_METHOD0(MockrmockMessageGroup, void());
    MOCK_METHOD0(MockreceiveNet, void());
    MOCK_METHOD0(MocksendNet, void());
    MOCK_METHOD0(Mocksend, void());

    mockMessageGroup() = delete;

    mockMessageGroup(const std::string &text, uint64_t ownerID,
                     const sharedLib::Platform &platform, const std::vector<sharedLib::Playlist> &playlists = {},
                     const std::vector<sharedLib::Song> &songs = {},
                     const std::vector<sharedLib::Platform> &toPlatform = {}) : Messages(text, ownerID, platform,
                                                                                         playlists, songs,
                                                                                         toPlatform) {
        // MessageGroup m(text, ownerID, platform, playlists, songs, toPlatform);
        MockrmockMessageGroup();
        std::cout << "mockMessageGroup init";
    };

    bool receiveNett(const sharedLib::Message &message) {
        bool f = Messages.receiveNet(message);
        MockreceiveNet();
        return f;
    };

    bool sendNet() {
        bool f = Messages.sendNet();
        MocksendNet();
        return f;
    };

    bool sendd(const std::function<void(const std::vector<sharedLib::Message>::iterator &,
                                        const std::vector<sharedLib::Message>::iterator &)> &qtDraw) {
        bool f = Messages.send(qtDraw);
        Mocksend();
        return f;
    };

    client::MessageGroup Messages;
};

TEST(mMessageGroup, MockmMessageGroup) {
    std::string text = "Message";
    uint64_t ownerID = 0;
    sharedLib::Platform platform = sharedLib::Spotify;
    std::vector<sharedLib::Playlist> playlists;
    playlists.emplace_back(sharedLib::URL("https://open.spotify.com/playlist/1hBbNxTjcitTZfu51dB7RB"), platform);
    std::vector<sharedLib::Song> songs;
    songs.emplace_back(sharedLib::URL("https://open.spotify.com/track/0ZLhqWBAhobSU4bTvKdM2K?si=e8a36ebb078f4dea"),
                       platform);
    std::vector<sharedLib::Platform> toPlatform;
    toPlatform.emplace_back(sharedLib::YouTube);
    mockMessageGroup messageGr(text, ownerID, platform, playlists, songs, toPlatform);
    EXPECT_CALL(messageGr, MockreceiveNet()).Times(1);
    EXPECT_CALL(messageGr, MocksendNet()).Times(1);
    EXPECT_CALL(messageGr, Mocksend()).Times(1);

    bool res = 0;

    res = messageGr.sendd([](const std::vector<sharedLib::Message>::iterator &a,
                             const std::vector<sharedLib::Message>::iterator &b) {
        std::cout << a->text;
    });
    EXPECT_EQ(res, true);
    res = messageGr.sendNet();
    EXPECT_EQ(res, true);
    res = messageGr.receiveNett(messageGr.Messages.Messages[0]);
    EXPECT_EQ(res, true);
}

TEST(getPlatform, getPlatform_int) {
    EXPECT_EQ(client::getPlatform(sharedLib::None), "None");
    EXPECT_EQ(client::getPlatform(sharedLib::YouTube), "Youtube");
    EXPECT_EQ(client::getPlatform(sharedLib::Spotify), "Spotify");
}

TEST(checkURLs, allRight) {
    std::vector<sharedLib::Playlist> playlists;
    playlists.emplace_back(sharedLib::URL("https://open.spotify.com/playlist/1hBbNxTjcitTZfu51dB7RB"),
                           sharedLib::Spotify);
    playlists.emplace_back(sharedLib::URL("https://www.youtube.com/playlist?list=PLcidtVPGDsUWcrT65QjefzB8syuGpgDoN"),
                           sharedLib::YouTube);
    std::vector<sharedLib::Song> songs;
    songs.emplace_back(sharedLib::URL("https://open.spotify.com/track/0ZLhqWBAhobSU4bTvKdM2K?si=e8a36ebb078f4dea"),
                       sharedLib::Spotify),
            songs.emplace_back(sharedLib::URL("https://www.youtube.com/watch?v=dcG8c_KxeJ4a"), sharedLib::YouTube);

    EXPECT_EQ(client::checkURLs<sharedLib::Playlist>(playlists.begin(), playlists.end()), true);
    EXPECT_EQ(client::checkURLs<sharedLib::Song>(songs.begin(), songs.end()), true);
}

TEST(checkURLs, allFalse) {
    std::vector<sharedLib::Playlist> playlists;
    playlists.emplace_back(sharedLib::URL("https://open.spoify.com/playlist/1hBbNxTjcitTZfu51dB7RB"),
                           sharedLib::Spotify);
    playlists.emplace_back(sharedLib::URL("https://www.youtub.com/playlist?list=PLcidtVPGDsUWcrT65QjefzB8syuGpgDoN"),
                           sharedLib::YouTube);
    std::vector<sharedLib::Song> songs;
    songs.emplace_back(sharedLib::URL("https://open.spoify.co/track/0ZLhqWBAhobSU4bTvKdM2K?si=e8a36ebb078f4dea"),
                       sharedLib::Spotify),
            songs.emplace_back(sharedLib::URL("youtubecom"), sharedLib::YouTube);

    EXPECT_EQ(client::checkURLs<sharedLib::Playlist>(playlists.begin(), playlists.end()), false);
    EXPECT_EQ(client::checkURLs<sharedLib::Song>(songs.begin(), songs.end()), false);
}

TEST(checkURLs, semiFalse) {
    std::vector<sharedLib::Playlist> playlists;
    playlists.emplace_back(sharedLib::URL("https://open.spotify.com/playlist/1hBbNxTjcitTZfu51dB7RB"),
                           sharedLib::Spotify);
    playlists.emplace_back(sharedLib::URL("https://www.youtuba.com/playlist?list=PLcidtVPGDsUWcrT65QjefzB8syuGpgDoN"),
                           sharedLib::YouTube);
    std::vector<sharedLib::Song> songs;
    songs.emplace_back(sharedLib::URL("https://open.spotify.com/track/0ZLhqWBAhobSU4bTvKdM2K?si=e8a36ebb078f4dea"),
                       sharedLib::Spotify),
            songs.emplace_back(sharedLib::URL("youtubecom"), sharedLib::YouTube);

    EXPECT_EQ(client::checkURLs<sharedLib::Playlist>(playlists.begin(), playlists.end()), false);
    EXPECT_EQ(client::checkURLs<sharedLib::Song>(songs.begin(), songs.end()), false);
}
