#include <string>
#include <utility>
#include "../include/mainlib.h"
#include "../../../web/include/client.h"
//#include "../../../api/include/api.h"
/*
template<class T>
bool client::checkURLs(typename std::vector<T>::iterator vecBegin, typename std::vector<T>::iterator vecEnd) {
    bool isValid = true;
    if ((typeid(vecBegin).name() == typeid(std::vector<sharedLib::Platform>::iterator).name()) ||
        (typeid(vecBegin).name() == typeid(std::vector<sharedLib::Song>::iterator).name())) {
        std::for_each(vecBegin, vecEnd, [isValid](T *i) mutable {
            if (i->ref.link.find("spotify") || i->ref.link.find("youtube")) {
                isValid = false;
                return;
            }
        });
        return isValid;
    } else {
        std::cout << "Wrong Type";
        return false;
    }
}
*/
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

    //message.text = "[Server]: " + message.text;
    Messages.clear();
    Messages.push_back(message);
    QtDraw(Messages.begin(), Messages.end());

    /*
    for (auto &i: Messages) {
        i.text = "[server]: " + i.text;
        i.playlists.ytRef = "[playlist]: " + i.playlists.ytRef;
    }
     */
/*
    PlaylistManager<YoutubePlaylist> YPManager;
    RefsForURL playlistRefs = {"https://www.googleapis.com/youtube/v3/playlistItems",
                               "AIzaSyC3-MWvfyHVPjEVn8XYZd-HMVpc_mlxNHE",
                               "PL6AVWk5NUegUV-FWNYbCG_ykC13vevU_6", ""};
    string URL1 = GetPlaylistItemsURLYoutube(playlistRefs);
    vector<string> headers1;
    GetPlaylistItemsHeadersYoutube(headers1);
    YoutubePlaylist B = YPManager.createExistingPlaylist(URL1, headers1);

    for(int i = 0; i < B.songs.size(); i++){
        std::cout <<  B.songs[i].songName << "-" << B.songs[i].artist << std::endl;
    }
*/

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
    //echo
    //test
    //convert_playlist
    for (auto &i: Messages) {
        i.ownerID = BOT_ID; // fix

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

client::LocalData::LocalData(const std::function<void(const std::vector<sharedLib::Message>::iterator &,
                                                      const std::vector<sharedLib::Message>::iterator &)> &qtDraw,
                             const std::function<void(const std::vector<sharedLib::Message>::iterator &,
                                                      const std::vector<sharedLib::Message>::iterator &)> &_saveData) {
    file = fopen(FILE_PATH, "rb");

    saveData = _saveData;
}

bool client::LocalData::save() {

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

/*
bool client::ButtonGetDialog::action() {
    // getData()
    //creating fake data
    std::vector<sharedLib::Message> fakeMessages;
    int n = 35;
    fakeMessages.reserve(n);
    for (int i = 0; i < n; ++i) {
        //fakeMessages.push_back({i % 2, 0, "MSG" + std::to_string(i), "PLAY" + std::to_string(i)});
    }


    Messages = std::move(fakeMessages);  // move fix?

    // sendDataToQT()
    return false;
};
*/
