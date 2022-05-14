#include "mainlib.h"
#include "tem.h"
#include <string>
#include <stdlib.h>

bool client::MessageGroup::receive() {

    receiveNet();
    sendDB();
    return false;
}

bool client::MessageGroup::receiveNet() {

    for (auto &i: Messages) {
        i.text = "[server]: " + i.text;
        i.playlists.Ref = "[playlist]: " + i.playlists.Ref;
    }
    return false;
}

bool client::MessageGroup::send() {

    sendNet();
    sendDB();

    return false;
}

bool client::MessageGroup::sendNet() {

    receiveNet();

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

client::MessageGroup::MessageGroup(mutualH::Message _message) {
    Messages.push_back(_message);
}

client::MessageGroup::MessageGroup(std::string text, uint64_t id, bool isUrl) {
    mutualH::Message message;
    message.owner_id = id;
    if (isUrl)
        message.playlists.Ref = std::move(text);
    else
        message.text = std::move(text);

    Messages.push_back(message);
}

bool client::ButtonGetDialog::action() {
    // getData()
    //creating fake data
    std::vector<mutualH::Message> fakeMessages;
    int n = 35;
    fakeMessages.reserve(n);
    for (int i = 0; i < n; ++i) {
        fakeMessages.push_back({i % 2, 0, "MSG" + std::to_string(i), "PLAY" + std::to_string(i)});
    }


    Messages = std::move(fakeMessages);

    // sendDataToQT()
    return false;
};

bool client::ButtonAuth::action(std::string &login, std::string &password) {



    // getDataWithAPI()
    // sendToServer()
    // sendToDB()
    return false;
};

