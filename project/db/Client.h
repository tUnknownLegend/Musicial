#include <string>
#include <vector>
#include "teammates_classes.h"

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
        bool action(Message &message) {
            // getData()
            // sendToServer()
            // sendToDB()
            return false;
        };
    };

    class ButtonAuth : public Button {
    public:
        // security?
        bool action(std::string &login, std::string &password) {
            // getDataWithAPI()
            // sendToServer()
            // sendToDB()
            return false;
        };
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
    };

    class SongGroup : public Group {
    public:
        std::vector<Song> song;
    };


    class MessageGroup : public Group {
    public:
        std::vector<Message> Messages;
    };



    struct Chat {
        uint64_t id;
        std::vector<MessageGroup> myMessages;
        std::vector<MessageGroup> otherMessages; // ?
    };


}

#endif //MUSICIAL_BUILD_H