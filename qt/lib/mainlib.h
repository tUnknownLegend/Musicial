#pragma once

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include "shared_lib.h"

#ifndef MUSICIAL_BUILD_H
#define MUSICIAL_BUILD_H

#define BOT_ID 0
#define USER_ID 1

namespace client {
class Group {
 public:
    unsigned short amount;

    virtual bool getDB() = 0;

    virtual bool sendDB() = 0;

    virtual bool sendNet() = 0;
};

std::string getPlatform(const sharedLib::Platform &platform);

class MessageGroup : public Group {
 public:
    std::vector<sharedLib::Message> Messages = {};

    explicit MessageGroup(const sharedLib::Message &_message);

    MessageGroup(const std::string &text, uint64_t ownerID, const sharedLib::Platform &platform,
                 const std::vector<sharedLib::Playlist> &playlists = {},
                 const std::vector<sharedLib::Song> &songs = {},
                 const std::vector<sharedLib::Platform> &toPlatform = {});

    explicit MessageGroup(const std::vector<sharedLib::Message> &_messages);

    bool receiveNet(const sharedLib::Message &message);

    bool sendDB() override { return true; };

    bool sendNet() override;

    bool receive(const sharedLib::Message &message);

    bool send();

    bool send(const std::function<void(const std::vector<sharedLib::Message>::iterator &,
                                       const std::vector<sharedLib::Message>::iterator &)> &qtDraw);

 private:
    std::function<void(const std::vector<sharedLib::Message>::iterator &,
                       const std::vector<sharedLib::Message>::iterator &)> QtDraw;

    bool getDB() override { return true; };

    bool receiveMessage(const sharedLib::Message &message);
};

//  template<class T>
//  bool checkURLs(typename std::vector<T>::iterator vecBegin, typename std::vector<T>::iterator vecEnd);

template<class T>
bool checkURLs(typename std::vector<T>::iterator vecBegin, typename std::vector<T>::iterator vecEnd) {
    if (std::is_same<T, typename sharedLib::Playlist>::value ||
    std::is_same<T, typename sharedLib::Song>::value) {
        if (std::find_if(vecBegin, vecEnd,
                         [](const T &i) {
                             return (i.ref.link.find("youtube.com") == std::string::npos &&
                                     i.ref.link.find("spotify.com") == std::string::npos) == true;
                         }) != vecEnd) {
            return false;
        }
        return true;
    } else {
        std::cout << "Wrong Type";
        return true;
    }
}

}  //  namespace client

#endif  // MUSICIAL_BUILD_H
