#include <string>
#include <utility>
#include "../include/mainlib.h"
#include "../../../web/include/client.h"

template<class T>
bool client::checkURLs(typename std::vector<T>::iterator vecBegin, typename std::vector<T>::iterator vecEnd) {
    if (std::is_same<T, typename sharedLib::Playlist>::value || std::is_same<T, typename sharedLib::Song>::value) {
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

bool client::MessageGroup::receive(const sharedLib::Message &message) {

    receiveNet(message);
    sendDB();
    return false;
}

bool client::MessageGroup::receiveMessage(const sharedLib::Message &message) {
    Messages.push_back(message);
    //receiveNet();

    return false;
}

bool client::MessageGroup::receiveNet(const sharedLib::Message &message) {
    Messages.clear();
    Messages.push_back(message);
    QtDraw(Messages.begin(), Messages.end());

    return false;
}

bool client::MessageGroup::send() {
    sendNet();
    sendDB();

    return false;
}

bool client::MessageGroup::send(const std::function<void(const std::vector<sharedLib::Message>::iterator &,
                                                         const std::vector<sharedLib::Message>::iterator &)> &qtDraw) {
    QtDraw = qtDraw;
    sendNet();
    sendDB();

    return false;
}

bool client::MessageGroup::sendNet() {
    QtDraw(Messages.begin(), Messages.end());

    // * handlers *
    //  echo
    //  test
    //  convert_playlist
    for (auto &i: Messages) {
        i.ownerID = BOT_ID;

        if (i.playlistNumber != 0 || i.songsNumber != 0)
            webClient::sendMessage("0.0.0.0", "8000", "convert_playlist", i,
                                   [this](const sharedLib::Message &Message) { receiveNet(Message); });
        else
            webClient::sendMessage("0.0.0.0", "8000", "echo", i,
                                   [this](const sharedLib::Message &Message) { receiveNet(Message); });
    }
    return false;
}

client::MessageGroup::MessageGroup(const sharedLib::Message &_message) {
    Messages.push_back(_message);
}

client::MessageGroup::MessageGroup(std::vector<sharedLib::Message> &_messages) {
    Messages = std::move(_messages);
}

client::MessageGroup::MessageGroup(const std::string &text, uint64_t ownerID, const sharedLib::Platform &platform,
                                   const std::vector<sharedLib::Playlist> &playlists,
                                   const std::vector<sharedLib::Song> &songs,
                                   const std::vector<sharedLib::Platform> &toPlatform) {
    sharedLib::Message message;
    message.ownerID = ownerID;
    message.text = text;

    if (platform != sharedLib::None) {
        message.playlists = playlists;
        message.playlistNumber = message.playlists.size();
        message.songs = songs;
        message.songsNumber = message.songs.size();
        message.toPlatform = toPlatform;
        message.toPlatformNumber = message.toPlatform.size();
    }

    Messages.push_back(message);
}

std::string client::getPlatform(const sharedLib::Platform &platform) {
    switch (platform) {
        case sharedLib::YouTube:
            return "Youtube";
            break;
        case sharedLib::Spotify:
            return "Spotify";
            break;
        default:
            return "None";
    }
}

