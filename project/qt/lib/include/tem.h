
#ifndef LIB_TEM_H
#define LIB_TEM_H

namespace mutualH {

    struct PlaylistPlatformsRefs {
        //std::string SpotifyRef;
        //std::string YoutubeRef;
        std::string Ref;
    };

    struct Message {
        uint64_t owner_id;
        uint64_t chat_id;
        std::string text;
        PlaylistPlatformsRefs playlists;
    };

    struct Song {
        std::string songName;
        std::string artist;
    };
}
#endif //LIB_TEM_H
