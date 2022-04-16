#include <stdio.h>
#include <iostream>
#include <stdint.h>

struct playlistPlatformsRefs {
    int someData;
};
struct User {

};
struct Playlist {
    int someData;
};
struct MessageGroup {
    int someData;
};

class Message {
public:
    void sendDB() {};

    void send() {};

private:
    uint64_t owner_id;
    uint64_t chat_id;
    std::string text;
    playlistPlatformsRefs playlists;
};

class Server {
public:
    Message getMessageFromDB() {}
    Playlist getPlaylistFromDB() {}
    User getUserFromDB() {}
    bool updateFromServer() {}
    MessageGroup getMessageGroupFromDB(uint64_t owner_id) {}
private:
    std::string BD;
};

