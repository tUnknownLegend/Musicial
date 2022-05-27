#include <string>
#include <vector>
#include <functional>
//#include "../../../web/include/net_tools.h"
#include "../../../web/include/shared_lib.h"

#ifndef MUSICIAL_BUILD_H
#define MUSICIAL_BUILD_H

#define BOT_ID 0
#define USER_ID 1
#define FILE_PATH "data.bin"

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

    std::string getPlatform(const sharedLib::Platform &platform);

    class MessageGroup : public Group {
    public:
        std::vector<sharedLib::Message> Messages = {};

        explicit MessageGroup(const sharedLib::Message &_message);

        MessageGroup(const std::string &text, uint64_t ownerID, const sharedLib::Platform &platform,
                     const std::vector<sharedLib::Playlist> &playlists = {},
                     const std::vector<sharedLib::Song> &songs = {},
                     const std::vector<sharedLib::Platform> &toPlatform = {});

        explicit MessageGroup(std::vector<sharedLib::Message> &_messages);

        bool receiveNet(const sharedLib::Message &message);

        bool sendDB() override { return false; };

        bool sendNet() override;

        bool receive(const sharedLib::Message &message);

        bool send();

        bool send(const std::function<void(const std::vector<sharedLib::Message>::iterator &,
                                           const std::vector<sharedLib::Message>::iterator &)> &qtDraw);

    private:

        std::function<void(const std::vector<sharedLib::Message>::iterator &,
                           const std::vector<sharedLib::Message>::iterator &)> QtDraw;

        bool getDB() override { return false; };

        bool receiveMessage(const sharedLib::Message &message);
    };

    class LocalData {
    public:

        LocalData() = delete;

        explicit LocalData(const std::function<void(const std::vector<sharedLib::Message>::iterator &,
                                                    const std::vector<sharedLib::Message>::iterator &)> &qtDraw,
                           const std::function<void(const std::vector<sharedLib::Message>::iterator &,
                                                    const std::vector<sharedLib::Message>::iterator &)> &_saveData);

        ~LocalData() { fclose(file); };

        bool save();

    private:

        FILE *file;
        std::function<void(const std::vector<sharedLib::Message>::iterator &,
                           const std::vector<sharedLib::Message>::iterator &)> saveData;
    };
}
#endif //MUSICIAL_BUILD_H