#ifndef PROJECT_WEB_INCLUDE_SHARED_LIB_H_
#define PROJECT_WEB_INCLUDE_SHARED_LIB_H_

#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace sharedLib {

    enum Platform {
        None, YouTube, Spotify
    };

    struct Database {
    };

    struct URL {
        URL() = default;

        explicit URL(std::string _link) : link(std::move(_link)) {};
        std::string link = "-";
    };

    struct Playlist {
        Playlist() = default;

        Playlist(URL _url, Platform _platform) : ref(std::move(_url)), platform(_platform) {};
        URL ref = {};
        Platform platform = None;
    };

    struct Song {
        Song() = default;

        Song(URL _url, Platform _platform) : ref(std::move(_url)), platform(_platform) {};
        URL ref = {};
        Platform platform = None;
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
        uint64_t ownerID = 0;
        uint64_t chatID = 0;
        std::string text = "-";
        std::vector<Playlist> playlists = {};
        uint64_t playlistNumber = 0;
        std::vector<Song> songs = {};
        uint64_t songsNumber = 0;
        std::vector<Platform> toPlatform = {};
        uint64_t toPlatformNumber = 0;
    };

}
#endif  // PROJECT_WEB_INCLUDE_SHARED_LIB_H_
