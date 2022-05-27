
#include <string>
#include <utility>
#include "mainlib.h"

bool client::MessageGroup::receive(const sharedLib::Message &message) {
    if (receiveNet(message) && sendDB())
        return true;
    else
        return false;
}

bool client::MessageGroup::receiveMessage(const sharedLib::Message &message) {
    size_t size = Messages.size();
    Messages.push_back(message);
    return size + 1 == Messages.size();
}

bool client::MessageGroup::receiveNet(const sharedLib::Message &message) {
    Messages.clear();
    Messages.push_back(message);
    QtDraw(Messages.begin(), Messages.end());

    return Messages.size() == 1;
}

bool client::MessageGroup::send() {
    return sendNet() && sendDB();
}

bool client::MessageGroup::send(const std::function<void(const std::vector<sharedLib::Message>::iterator &,
        const std::vector<sharedLib::Message>::iterator &)> &qtDraw) {
    QtDraw = qtDraw;
    return sendNet() && sendDB();
}

bool client::MessageGroup::sendNet() {
    QtDraw(Messages.begin(), Messages.end());

    // * handlers *
    //  echo
    //  test
    //  convert_playlist
    for (auto &i : Messages) {
        i.ownerID = BOT_ID;

        if (i.playlistNumber != 0 || i.songsNumber != 0)
            webClient::sendMessage("0.0.0.0", "8000", "convert_playlist", i,
                                   [this](const sharedLib::Message &Message) { receiveNet(Message); });
        else
            webClient::sendMessage("0.0.0.0", "8000", "echo", i,
                                   [this](const sharedLib::Message &Message) { receiveNet(Message); });
    }
    return true;
}

client::MessageGroup::MessageGroup(const sharedLib::Message &_message) {
    Messages.push_back(_message);
}

client::MessageGroup::MessageGroup(std::vector<sharedLib::Message> &_messages) {
    Messages = std::move(_messages);
}

client::MessageGroup::MessageGroup(const std::string &text, uint64_t ownerID,
                                   const sharedLib::Platform &platform,
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

