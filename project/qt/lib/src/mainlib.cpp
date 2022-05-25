#include "../include/mainlib.h"
//#include "../include/tem.h"
#include <string>
#include <utility>
//#include <stdlib.h>
//#include "../../../web/project/server/include/client.h"
#include "../../../web/project/server/include/net_tools.h"
#include "../../../web/project/server/include/client.h"
//#include ""
#include "../../../api/include/api.h"

bool client::MessageGroup::receive() {

    //receiveNet();
    sendDB();
    return false;
}

void pushMessage(const net_tools::Message &message, const net_tools::Message &vectEnd) {
    //client::MessageGroup::receiveMessage(message);
}

bool client::MessageGroup::receiveMessage(const net_tools::Message &message) {
    Messages.push_back(message);
    //receiveNet();

    return false;
}

bool client::MessageGroup::receiveNet(const net_tools::Message &message) {

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

bool client::MessageGroup::send(std::function<void(const std::vector<net_tools::Message>::iterator &,
                                                   const std::vector<net_tools::Message>::iterator &)> _QtDraw) {
    QtDraw = std::move(_QtDraw);

    sendNet();
    sendDB();

    return false;
}

bool client::MessageGroup::sendNet() {

    QtDraw(Messages.begin(), Messages.end());

    //call function to send

    //clear vector

    //


    for (auto &i: Messages) {
        // fix struct Message
        i.ownerID = 1; // fix
        //i.text = "[server]: " + i.text;
        //i.playlists.ytRef = "[playlist]: " + i.playlists.ytRef;

        webClient::sendMessage("0.0.0.0", "8000", "/test", i,
                               [this](const net_tools::Message &Message) { receiveNet(Message); }); // fix!
    }

    //testing
    //receiveNet(Messages[0]);
    //webClient::sendMessage("0.0.0.0", "8000", "/test", );
    //Messages.clear();

    return false;
}

bool client::MessageGroup::sendDB() {


    return false;
}

bool client::MessageGroup::sendText() {

    return false;
}

bool client::MessageGroup::sendPlaylist() {


    return false;
}

client::MessageGroup::MessageGroup(const net_tools::Message &_message) {
    Messages.push_back(_message);
}

client::MessageGroup::MessageGroup(std::vector<net_tools::Message> &_messages) {
    Messages = std::move(_messages);
}

client::MessageGroup::MessageGroup(std::string text, uint64_t id, bool isUrl) {
    net_tools::Message message;
    message.ownerID = id;
    if (isUrl)
        message.playlists.ytRef = std::move(text);
    else
        message.text = std::move(text);

    Messages.push_back(message);
}

bool client::ButtonGetDialog::action() {
    // getData()
    //creating fake data
    std::vector<net_tools::Message> fakeMessages;
    int n = 35;
    fakeMessages.reserve(n);
    for (int i = 0; i < n; ++i) {
        //fakeMessages.push_back({i % 2, 0, "MSG" + std::to_string(i), "PLAY" + std::to_string(i)});
    }


    Messages = std::move(fakeMessages);  // move fix?

    // sendDataToQT()
    return false;
};

bool client::ButtonAuth::action(std::string &login, std::string &password) {



    // getDataWithAPI()
    // sendToServer()
    // sendToDB()
    return false;
};

