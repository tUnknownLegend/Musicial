#ifndef PROJECT_SERVER_INCLUDE_NET_TOOLS_H_
#define PROJECT_SERVER_INCLUDE_NET_TOOLS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


namespace net_tools {
struct Database {
};

struct URL {
    std::string link;
};

struct playlistPlatformsRefs {
    URL ytRef;
    URL spRef;
};

struct User {
    uint64_t id;
    std::string email;
    std::string nickname;
    std::string firstName;
    std::string secondName;
    std::string phoneNumber;
    std::string avatarRef;
};

struct Playlist {
    int someData;
};

struct Message {
    Message(uint64_t ownerID_, uint64_t chatID_, std::string &text_, URL &spRef_, URL &ytRef_) :
    ownerID(ownerID_),
    chatID(chatID_),
    text(text_),
    playlists({ytRef_, spRef_})
    {}

    Message() {
        ownerID = 0;
        chatID = 0;
        text = "test";
        playlists = {"", ""};
    };




    uint64_t ownerID;
    uint64_t chatID;
    std::string text;
    playlistPlatformsRefs playlists;
};

/*
class Server {
public:
    Message getMessageFromDB() {}

    Playlist getPlaylistFromDB() {}

    User getUserFromDB() {}

    bool updateFromServer() {}

    MessageGroup getMessageGroupFromDB(uint64_t ownerID) {}

private:
    Database DB;
};
*/
std::ostream &operator<<(std::ostream &os, const net_tools::Message &message);

bool operator==(const net_tools::Message &lMessage, const net_tools::Message &rMessage);

std::ostream &operator<<(std::ostream &os, const net_tools::playlistPlatformsRefs &refs);

bool operator==(const net_tools::playlistPlatformsRefs &lRefs, const net_tools::playlistPlatformsRefs &rRefs);

bool isMessageEmpty(const Message &message);

bool isRefEmpty(const playlistPlatformsRefs &refs);

Message getAnswer(const Message &mes);

Message getMessage();

std::string Message2String(const Message &message);

std::vector<std::string> parseMessage(const std::string &s, char delim);

Message String2Message(const std::string &str);

}  // namespace net_tools

#endif  // PROJECT_SERVER_INCLUDE_NET_TOOLS_H_
