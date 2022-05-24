#ifndef PROJECT_SERVER_INCLUDE_NET_TOOLS_H_
#define PROJECT_SERVER_INCLUDE_NET_TOOLS_H_

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum Platform {YouTube, Spotify};

namespace net_tools {
struct Database {
};

struct URL {
    std::string link;
};

struct Playlist {
    URL ref;
    Platform platform;
};

struct Song {
    URL ref;
    Platform platform;
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


struct Message {
    Message() {
        ownerID = 0;
        chatID = 0;
        text = "test";
    };

    uint64_t ownerID;
    uint64_t chatID;
    std::string text;
    std::vector<Playlist> playlists;
    uint64_t playlistNumber;
    std::vector<Song> songs;
    uint64_t songsNumber;
};


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
