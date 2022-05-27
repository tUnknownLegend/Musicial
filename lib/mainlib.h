#include <string>
#include <vector>
#include "tem.h"

#ifndef MUSICIAL_BUILD_H
#define MUSICIAL_BUILD_H

namespace client {

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
        bool action(mutualH::Message &message) {
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

    struct User {
        uint64_t id;
        std::string firstName;
        std::string secondName;
        std::string userName;
        std::string email;
        std::string phoneNumber;
        Picture avatar;
    };

    class Profile {
    public:
        User user;
        /* + analytics */
    };

    struct Post {
        // struct of channel post
    };

    class Channel : public Post {

    };

    class Group {
    public:
        unsigned short amount;

        virtual bool getDB() = 0;

        virtual bool receiveNet() = 0;

        virtual bool sendDB() = 0;

        virtual bool sendNet() = 0;
    };

    class SongGroup : public Group {
    public:
        std::vector<mutualH::Song> song;

        bool getDB() override { return false; };

        bool receiveNet() override { return false; };

        bool sendDB() override { return false; };

        bool sendNet() override { return false; };
    };


    class MessageGroup : public Group {
    public:
        std::vector<mutualH::Message> Messages;

        MessageGroup(mutualH::Message _message);

        MessageGroup(std::string text, uint64_t id, bool isUrl);
        //MessageGroup(vector<Message> Messages);

        bool getDB() override { return false; };

        bool receiveNet() override;

        bool sendDB() override;

        bool sendNet() override;

        bool receive();

        bool send();

    private:
        bool sendText();

        bool sendPlaylist();
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
        std::vector<mutualH::Message> Messages;

        bool action();
    };

    struct Chat {
        uint64_t id;
        std::vector<MessageGroup> myMessages;
        std::vector<MessageGroup> otherMessages; // ?
    };

    struct Dialog : public Instance {
        Picture dialogPic;
        TextField lastMessage;
    };

    class DialogGroup : public Group {
        std::vector<Dialog> Dialogs;

        bool getDB() override { return false; };

        bool receiveNet() override { return false; };

        bool sendDB() override { return false; };

        bool sendNet() override { return false; };
    };

}

#endif //MUSICIAL_BUILD_H