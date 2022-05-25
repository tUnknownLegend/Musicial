#ifndef PROJECT_WEB_INCLUDE_SHARED_LIB_H_
#define PROJECT_WEB_INCLUDE_SHARED_LIB_H_

#include <iostream>
#include <string>
#include <vector>

enum Platform {
    YouTube, Spotify
};

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
    uint64_t ownerID;
    uint64_t chatID;
    std::string text;
    std::vector<Playlist> playlists;
    uint64_t playlistNumber{};
    std::vector<Song> songs;
    uint64_t songsNumber{};
};


#endif  // PROJECT_WEB_INCLUDE_SHARED_LIB_H_
