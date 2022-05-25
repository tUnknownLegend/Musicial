#include <gtest/gtest.h>


#include "net_tools.h"

/*
TEST(parseMessage, CorrectData) {
    net_tools::Message message = {1, 2, "test 0", {"test 1", "test 2"}};
    std::string strMessage = net_tools::Message2String(message);

    EXPECT_TRUE(message == net_tools::String2Message(strMessage));
}

TEST(parseString, CorrectData) {
    net_tools::Message message = {1, 2, "test 0", {"test 1", "test 2"}};
    std::string stringMessage = "1\r\n2\r\ntest 0\r\ntest 1\r\ntest 2\r\n\r\n";

    EXPECT_EQ(stringMessage, net_tools::Message2String(message));
}
*/

/*
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
*/
