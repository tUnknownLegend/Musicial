#include "net_tools.h"

namespace net_tools {
    std::ostream &operator<<(std::ostream &os, const net_tools::playlistPlatformsRefs &refs) {
        os << "Spotify ref: " << refs.spRef << std::endl;
        os << "YouTube ref: " << refs.ytRef << std::endl;
        return os;
    }

    bool operator==(const net_tools::playlistPlatformsRefs &lRefs, const net_tools::playlistPlatformsRefs &rRefs) {
        if (lRefs.spRef == rRefs.spRef && lRefs.ytRef == rRefs.ytRef) {
            return true;
        }
        return false;
    }

    bool isRefEmpty(const playlistPlatformsRefs &refs) {
        if (refs.ytRef.empty() && refs.spRef.empty()) {
            return true;
        }
        return false;
    }

    std::ostream &operator<<(std::ostream &os, const net_tools::Message &message) {
        os << "Owner ID: " << message.ownerID << std::endl;
        os << "Chat ID: " << message.chatID << std::endl;
        os << "Text: " << message.text << std::endl;
        os << message.playlists;
        return os;
    }

    bool operator==(const net_tools::Message &lMessage, const net_tools::Message &rMessage) {
        if (lMessage.chatID == rMessage.chatID &&
            lMessage.ownerID == rMessage.ownerID &&
            lMessage.text == rMessage.text &&
            lMessage.playlists == rMessage.playlists) {
            return true;
        }
        return false;
    }


    bool isMessageEmpty(const Message &message) {
        if (message.text.empty() && isRefEmpty(message.playlists)) {
            return true;
        }
        return false;
    }

    Message getMessage() {
        Message message;
        std::cout << "Owner ID: ";
        std::cin >> message.ownerID;

        std::cout << "Chat ID: ";
        std::cin >> message.chatID;

        std::cout << "Text: ";
        std::cin >> message.text;

        std::cout << "YouTube Ref: ";
        std::cin >> message.playlists.ytRef;

        std::cout << "Spotify Ref: ";
        std::cin >> message.playlists.spRef;

        return message;
    }

    Message getAnswer(const Message &mes) {
        Message ans_message;

        ans_message = getMessage();

        return ans_message;
    }

    std::string Message2String(const Message &message) {
        std::string result = std::to_string(message.ownerID);
        result += "\r\n";

        result += std::to_string(message.chatID);
        result += "\r\n";

        result += message.text;
        result += "\r\n";

        result += message.playlists.ytRef;
        result += "\r\n";

        result += message.playlists.spRef;

        return result;
    }

    std::vector<std::string> parseMessage(const std::string &s, char delim) {
        std::stringstream ss(s);
        std::string item;
        std::vector<std::string> elems;

        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    Message String2Message(const std::string &str) {
        Message result;

        std::vector<std::string> blocks = parseMessage(str, '\n');

        result.ownerID = (uint64_t) std::stoi(blocks[0]);
        result.chatID = (uint64_t) std::stoi(blocks[1]);
        result.text = blocks[2];
        result.playlists.ytRef = blocks[3];
        result.playlists.spRef = blocks[4];


        return result;
    }

}  // namespace net_tools
