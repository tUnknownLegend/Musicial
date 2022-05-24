#include "net_tools.h"

namespace net_tools {

    std::ostream &operator<<(std::ostream &os, const net_tools::URL &url) {
        os << url.link;
        return os;
    }

    std::istream &operator>>(std::istream &is, net_tools::URL &url) {
        is >> url.link;
        return is;
    }

    bool operator==(const net_tools::URL &lURL, const net_tools::URL &rURL) {
        if (lURL.link == rURL.link) {
            return true;
        }
        return false;
    }

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
        if (refs.ytRef.link.empty() && refs.spRef.link.empty()) {
            return true;
        }
        return false;
    }

    std::ostream &operator<<(std::ostream &os, const net_tools::Message &message) {
        os << "Owner ID: " << message.ownerID << std::endl;
        os << "Chat ID: " << message.chatID << std::endl;
        os << "Text: " << message.text << std::endl;

        os << "Playlist Number: " << message.playlistNumber << std::endl;
        for (auto i : message.playlists) {
            os << "Playlist link: " << i.ref << std::endl;
            os << "Playlist platform: " << i.platform << std::endl;
        }

        os << "Songs Number: " << message.songsNumber << std::endl;
        for (auto i : message.songs) {
            os << "Song link: " << i.ref << std::endl;
            os << "Song platform: " << i.platform << std::endl;
        }

        return os;
    }



    Message getMessage() {
        Message message;
        std::cout << "Owner ID: ";
        std::cin >> message.ownerID;

        std::cout << "Chat ID: ";
        std::cin >> message.chatID;

        std::cout << "Text: ";
        std::cin >> message.text;

        std::cout << "Number of playlists: ";
        std::cin >> message.playlistNumber;

        for (int i = 0; i < message.playlistNumber; ++i) { // fix
            net_tools::URL ref;
            std::cout << "Ref to playlist: ";
            std::cin >> ref.link;
            std::string str;
            Platform p = YouTube; // fix
            std::cout << "Platform (0 - YT, 1 - Spotify): ";
            std::cin >> str;

            message.playlists.push_back({ref, p});

        }

        std::cout << "Number of songs: ";
        std::cin >> message.songsNumber;

        for (int i = 0; i < message.songsNumber; ++i) { // fix
            net_tools::URL ref;
            std::cout << "Ref to song: ";
            std::cin >> ref.link;
            std::string str;
            std::cout << "Platform (0 - YT, 1 - Spotify): ";
            Platform p = YouTube; // fix

            message.songs.push_back({ref, p});

        }

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

        result += std::to_string(message.playlistNumber);
        result += "\r\n";
        for (auto &i: message.playlists) {
            result += i.ref.link;
            result += "\r\n";
            result += std::to_string(i.platform);
            result += "\r\n";
        }

        result += std::to_string(message.songsNumber);
        result += "\r\n";
        for (auto &i: message.songs) {
            result += i.ref.link;
            result += "\r\n";
            result += std::to_string(i.platform);
            result += "\r\n";
        }

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

        result.playlistNumber = (uint64_t) std::stoi(blocks[3]);
        for (int i = 0; i < result.playlistNumber * 2; ++i) {
            if (!(i % 2)) {
                Platform p = static_cast<Platform>(std::stoi(blocks[i + 1 + 4]));
                Playlist playlist = {blocks[i + 4], p};
                result.playlists.push_back(playlist);
            }

        }

        result.songsNumber = (uint64_t) std::stoi(blocks[4 + result.playlistNumber * 2]);
        for (int i = 0; i < result.songsNumber * 2; ++i) {
            if (!(i % 2)) {
                Platform p = static_cast<Platform>(std::stoi(blocks[i + 1 + 5 + result.playlistNumber * 2]));
                Song s = {blocks[i + 5 + result.playlistNumber * 2], p};
                result.songs.push_back(s);
            }

        }

        return result;
    }

}  // namespace net_tools
