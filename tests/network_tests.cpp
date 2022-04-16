#include <gtest/gtest.h>

#include "Network.h"


TEST(getMessageFromDB, IncorrectData) {
    Server server = {};
    Message defaultMessage;
    Message getting_result = server.getMessageFromDB();

    EXPECT_EQ(getting_result, defaultMessage);
}

TEST(getPlaylistFromDB, IncorrectData) {
    Server server = {};
    Playlist defaultPlaylist;
    Playlist getting_result = server.getPlaylistFromDB();

    EXPECT_EQ(getting_result, defaultPlaylist);
}

TEST(getUserFromDB, IncorrectData) {
    Server server = {};
    User defaultUser;
    User getting_result = server.getUserFromDB();

    EXPECT_EQ(getting_result, defaultUser);
}

TEST(getMessageGroupFromDB, IncorrectData) {
    Server server = {};
    MessageGroup defaultGroup;
    MessageGroup getting_result = server.getMessageGroupFromDB();

    EXPECT_EQ(getting_result, defaultGroup);
}
