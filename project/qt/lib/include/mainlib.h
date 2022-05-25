#include <string>
#include <vector>
#include "tem.h"
#include <functional>
#include "../../../web/project/server/include/net_tools.h" //fix

#ifndef MUSICIAL_BUILD_H
#define MUSICIAL_BUILD_H

#define BOT_ID 0
#define USER_ID 1
#define CHAT_ID

namespace client {
/*
    class RecieveMessageNet {
    public:
        std::vector<net_tools::Message> messages = {};


        void addToVec(const net_tools::Message &message) {messages.push_back(message);};
        friend void receiveMessage(const net_tools::Message &message) {
            //addToVec(message);
            //messages.push_back(message); };

    };

*/
    struct Size {
        unsigned short height;
        unsigned short width;
    };

    struct Color {
        std::string textColor;
        std::string backgroundColor;
    };

    struct Text {
        Color color;
        std::string text;
    };

    struct Instance {
        // struct Size;
        Color color;
        Text text;
    };

    struct TextField : public Instance {

    };

    struct Picture {
        std::string path;
        // struct Size;
    };

    class Button : public Instance {

    };

    class ButtonSendMessage : public Button {
    public:
        bool action(net_tools::Message &message) {
            // getData()
            // sendToServer()
            // sendToDB()
            return false;
        };
    };

    class ButtonAuth : public Button {
    public:
        // security?
        bool action(std::string &login, std::string &password);
    };

/*
    struct Post {
        // struct of channel post
    };

    class Channel : public Post {

    };
*/
    class Group {
    public:
        unsigned short amount;

        virtual bool getDB() = 0;

        //virtual bool receiveNet() = 0;

        virtual bool sendDB() = 0;

        virtual bool sendNet() = 0;
    };


    class SongGroup : public Group {
    public:
        std::vector<templib::Song> song = {};

        bool getDB() override { return false; };

        //bool receiveNet() override { return false; };

        bool sendDB() override { return false; };

        bool sendNet() override { return false; };
    };


    class MessageGroup : public Group {
    public:
        std::vector<net_tools::Message> Messages = {};

        explicit MessageGroup(const net_tools::Message &_message);

        MessageGroup(std::string text, uint64_t id, bool isUrl);

        explicit MessageGroup(std::vector<net_tools::Message> &_messages);

        bool receiveNet(const net_tools::Message &message);

        bool sendDB() override;

        bool sendNet() override;

        bool receive();

        bool send();

        bool send(std::function<void(const std::vector<net_tools::Message>::iterator &,
                                     const std::vector<net_tools::Message>::iterator &)> _QtDraw);

    private:

        std::function<void(const std::vector<net_tools::Message>::iterator &,
                           const std::vector<net_tools::Message>::iterator &)> QtDraw;

        bool getDB() override { return false; };

        bool sendText();

        bool sendPlaylist();

        bool receiveMessage(const net_tools::Message &message);
    };

    class ButtonCreatePlaylist : public Button {
    public:
        bool action(SongGroup &list) {
            // getDataWithAPI()
            // sendToServer()
            // sendToDB()
            return false;
        };
    };

    class ButtonGetDialog : public Button {
    public:
        std::vector<net_tools::Message> Messages;

        bool action();
    };
}

#endif //MUSICIAL_BUILD_H