#include <iostream>
#include <vector>
#include <string>

struct PlaylistPlatformsRefs{
    std::string SpotifyRef;
    std::string YoutubeRef;
};

struct Song{
    std::string songName;
    std::string artist;
};

class Playlist{
public:
    Playlist(){
        playlistId = 0;
        playlistCreatorId = 0;
        playlistSize = 0;
        Refs = {"",""};
        playlistCreator = "";

    }   
    int playlistId;
    int playlistCreatorId;
    std::string playlistCreator;
    int playlistSize;
    std::vector<Song> songs;
    PlaylistPlatformsRefs Refs;
    
    virtual bool addSong(Song &s) = 0;
    virtual bool removeSong(int number) = 0;
    virtual bool swapSongs(int number1, int number2) = 0;

    bool send(uint64_t chat_id);
    //void receive(int senderId, int platform);
};


class MusicialPlaylist:public Playlist{
public:
    bool addSong(Song &s) override;
    bool removeSong(int number) override;
    bool swapSongs(int number1, int number2) override;
};

class YoutubePlaylist:public Playlist{
public:
    bool addSong(Song &s) override;
    bool removeSong(int number) override;
    bool swapSongs(int number1, int number2) override;
};

class SpotifyPlaylist:public Playlist{
public:
    bool addSong(Song &s) override;
    bool removeSong(int number) override;
    bool swapSongs(int number1, int number2) override;
};

class PlaylistManager {
public:
    virtual Playlist *createEmptyPlaylist();
    virtual void deletePlaylist();
};

class YoutubePlaylistManager:public PlaylistManager {
public:
    Playlist *createEmptyPlaylist() override;
    void deletePlaylist() override;
    Playlist *createExistingPlaylist(std::string &playlistRef);
};

class SpotifyPlaylistManager:public PlaylistManager {
public:
    Playlist *createEmptyPlaylist() override;
    void deletePlaylist() override;
    Playlist *createExistingPlaylist(std::string &playlistRef);
};
