#ifndef TEAMMATES_CLASSES_H
#define TEAMMATES_CLASSES_H

struct PlaylistPlatformsRefs {
std::string SpotifyRef;
std::string YoutubeRef;
};

class Message {
public:
	bool sendDB() { return false; };

	bool sendNet() { return false; };

private:
	uint64_t owner_id;
	uint64_t chat_id;
	std::string text;
	PlaylistPlatformsRefs playlists;
};



struct Song {
	std::string songName;
	std::string artist;
};

#endif