#include "net_tools.h"


namespace net_tools {
    std::ostream &operator<<(std::ostream &os, const sharedLib::URL &url) {
        os << url.link;
        return os;
    }

    std::istream &operator>>(std::istream &is, sharedLib::URL &url) {
        is >> url.link;
        return is;
    }

    bool operator==(const sharedLib::URL &lURL, const sharedLib::URL &rURL) {
        if (lURL.link == rURL.link) {
            return true;
        }
        return false;
    }


    sharedLib::Message getMessage() {
        sharedLib::Message message;
        std::cout << "Owner ID: ";
        std::cin >> message.ownerID;

        std::cout << "Chat ID: ";
        std::cin >> message.chatID;

        std::cout << "Text: ";
        std::cin >> message.text;

        std::cout << "Number of playlists: ";
        std::cin >> message.playlistNumber;

        for (uint64_t i = 0; i < message.playlistNumber; ++i) {
            sharedLib::URL ref;
            std::cout << "Ref to playlist: ";
            std::cin >> ref.link;
            std::string str;
            std::cout << "Platform (0 - YT, 1 - Spotify): ";
            std::cin >> str;
            auto p = static_cast<sharedLib::Platform>(std::stoi(str));

            message.playlists.emplace_back(ref, p);
        }

        std::cout << "Number of songs: ";
        std::cin >> message.songsNumber;

        for (uint64_t i = 0; i < message.songsNumber; ++i) {
            sharedLib::URL ref;
            std::cout << "Ref to song: ";
            std::cin >> ref.link;
            std::string str;
            std::cout << "Platform (0 - YT, 1 - Spotify): ";
            std::cin >> str;
            auto p = static_cast<sharedLib::Platform>(std::stoi(str));

            message.songs.emplace_back(ref, p);
        }

        return message;
    }

    sharedLib::Message getAnswer(const sharedLib::Message &mes) {
        sharedLib::Message ans_message;

        ans_message = getMessage();

        return ans_message;
    }

    std::string Message2String(const sharedLib::Message &message) {
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

        result += std::to_string(message.toPlatformNumber);
        result += "\r\n";
        for (auto &i: message.toPlatform) {
            result += std::to_string(i);
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

    sharedLib::Message String2Message(const std::string &str) {
        sharedLib::Message result;

        std::vector<std::string> blocks = parseMessage(str, '\n');

        result.ownerID = (uint64_t) std::stoi(blocks[0]);
        result.chatID = (uint64_t) std::stoi(blocks[1]);
        result.text = blocks[2];

        result.playlistNumber = (uint64_t) std::stoi(blocks[3]);
        for (uint64_t i = 0; i < result.playlistNumber * 2; ++i) {
            if (!(i % 2)) {
                auto p = static_cast<sharedLib::Platform>(std::stoi(blocks[i + 1 + 4]));
                sharedLib::Playlist playlist = sharedLib::Playlist(sharedLib::URL(blocks[i + 4]), p);
                result.playlists.push_back(playlist);
            }
        }

        result.songsNumber = (uint64_t) std::stoi(blocks[4 + result.playlistNumber * 2]);
        for (uint64_t i = 0; i < result.songsNumber * 2; ++i) {
            if (!(i % 2)) {
                auto p = static_cast<sharedLib::Platform>(std::stoi(blocks[i + 1 + 5 + result.playlistNumber * 2]));
                sharedLib::Song s = sharedLib::Song(sharedLib::URL(blocks[i + 5 + result.playlistNumber * 2]), p);
                result.songs.push_back(s);
            }
        }

        result.toPlatformNumber = (uint64_t) std::stoi(blocks[4 + result.playlistNumber * 2 + result.songsNumber * 2]);
        for (uint64_t i = 0; i < result.toPlatformNumber; ++i) {
            auto p = static_cast<sharedLib::Platform>(std::stoi(blocks[i + 5 + result.playlistNumber * 2 + result.songsNumber * 2]));
            result.toPlatform.push_back(p);

        }

        std::cout << "To Platfrom: ";
        for (auto &i : result.toPlatform) {
            std::cout << i << " ";
        }
        return result;
    }

}  // namespace net_tools

std::ostream &operator<<(std::ostream &os, const sharedLib::Message &message) {
    os << "Owner ID: " << message.ownerID << std::endl;
    os << "Chat ID: " << message.chatID << std::endl;
    os << "Text: " << message.text << std::endl;

    int counter = 1;
    os << "Playlist Number: " << message.playlistNumber << std::endl;
    for (const auto &i: message.playlists) {
        os << " " << counter << "\n";
        os << " Playlist link: " << i.ref.link << std::endl;
        os << " Playlist platform: " << i.platform << std::endl;
        ++counter;
    }

    counter = 1;
    os << "Songs Number: " << message.songsNumber << std::endl;
    for (const auto &i: message.songs) {
        os << " " << counter << "\n";
        os << " Song link: " << i.ref.link << std::endl;
        os << " Song platform: " << i.platform << std::endl;
        ++counter;
    }

    os << "enum: ";
    for (auto& i : message.toPlatform) {
        os << i << " ";
    }

    return os;
}
