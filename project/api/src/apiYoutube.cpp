 #include "apiYoutube.h"
 #include <string.h>

string URLsSetterYoutube::URLYoutubeGetPlaylistItems(string &playlistId){
    string ApiUrl = "https://www.googleapis.com/youtube/v3/playlistItems";
    return ApiUrl + "?part=snippet&playlistId=" + playlistId;
}

string URLsSetterYoutube::URLYoutubeSearchSong(Song &song){
    string ApiUrl = "https://www.googleapis.com/youtube/v3/search";
    string maxResults = "maxResults=1";
    string filter = "";
    char *helpString = new char[song.songName.size() + 1];
    strcpy(helpString, song.songName.c_str());
    char *p = strtok(helpString, " ");
    while(p != NULL){
        filter += string(p);
        p = strtok(NULL, " ");
        if(p != NULL)
            filter += "%20";
    }
    delete [] helpString;
    filter += "%20";
    char *helpString2 = new char[song.artist.size() + 1];
    strcpy(helpString2, song.artist.c_str());
    p = strtok(helpString2, " ");
    while(p != NULL){
        filter += string(p);
        p = strtok(NULL, " ");
        if(p != NULL)
            filter += "%20";
    }
    delete [] helpString2;
    return ApiUrl + "?part=snippet&maxResults=1&q=" + filter + "&type=video";
}

string URLsSetterYoutube::URLYoutubeCreateEmptyPlaylist(){
    string ApiUrl = "https://www.googleapis.com/youtube/v3/playlists";
    return ApiUrl + "?part=snippet&part=status";
}

string URLsSetterYoutube::URLYoutubeCreatePlaylistFromSonglist(string &playlistId){
    string ApiUrl = "https://www.googleapis.com/youtube/v3/playlists";
    return ApiUrl + "?part=snippet";
}

string URLsSetterYoutube::URLYoutubeAddSong(){
    string ApiUrl = "https://www.googleapis.com/youtube/v3/playlistItems";
    return ApiUrl + "?part=snippet";
}

string URLsSetterYoutube::URLYoutubeGetSongById(string &songId){
    string ApiUrl = "https://www.googleapis.com/youtube/v3/videos";
    return ApiUrl + "?part=snippet&id=" + songId;
}

void PlaylistManagerYoutube::SetHeadersYoutube(vector<string> &headers){
    
    headers.push_back("Authorization: Bearer " + OAuthTokenYoutube);
    headers.push_back("Accept: application/json");
    headers.push_back("Content-type: application/json");
}

void ResponseParserYoutube::ParseResponseYoutubeGetPlaylistItems(string &readBuffer, Playlist &playlist){
    //std::cout << readBuffer << std::endl;
    try{
        json responseJson = json::parse(readBuffer);
        json responseJsonItems = responseJson["items"];
        for (auto songItem : responseJsonItems) {
            const char separator = '-';
            std::string str = songItem["snippet"]["title"];
            Song song;
            song.songName = str.substr(0, str.find(separator));
            if (song.songName.size() != str.size()) {
                str.erase(0, str.find(separator) + 1);
                song.artist = str;
            }
            playlist.songs.push_back(song);
        }
        return;
    } catch(...){
        std::cout << "Parsing error ParseResponseYoutubeGetPlaylistItems" << std::endl;
        return;
    }
}

string ResponseParserYoutube::ParseResponseYoutubeGetSongId(string &readBuffer){
    //std::cout << readBuffer << std::endl;
    try{
        json responseJson = json::parse(readBuffer);
        string songId = responseJson["items"][0]["id"]["videoId"];
        //string href = responseJson["tracks"]["items"][0]["href"];
        return songId;
    } catch(...){
        std::cout << "Parsing error ParseResponseYoutubeGetSongId" << std::endl;
        return "-1";
    }
}

string ResponseParserYoutube::ParseResponseYoutubeCreateEmptyPlaylist(string &readBuffer){
    //std::cout << readBuffer << std::endl;
    try{
        json responseJson = json::parse(readBuffer);
        string playlistId = responseJson["id"];
        return playlistId;
    } catch(...){
        std::cout << "Parsing error ParseResponseYoutubeCreateEmptyPlaylist" << std::endl;
        return "";
    }
}

Song ResponseParserYoutube::ParseResponseYoutubeGetSongById(string &readBuffer){
    //std::cout << readBuffer << std::endl;
    Song song = {"",""};
    try{
        json responseJson = json::parse(readBuffer);
        string title = responseJson["items"][0]["snippet"]["title"];
        const char separator = '-';
        Song song;
        song.songName = title.substr(0, title.find(separator));
        if (song.songName.size() != title.size()) {
            title.erase(0, title.find(separator) + 1);
            song.artist = title;
        }
        return song;
    } catch(...){
        std::cout << "Parsing error ParseResponseYoutubeGetSongById" << std::endl;
        return song;
    }
    return song;
}

Playlist PlaylistManagerYoutube::createPlaylistFromExistingYoutubePlaylist(string &playlistId) {
    Playlist ans;
    string readBuffer;
    string URL = URLsSetter.URLYoutubeGetPlaylistItems(playlistId);
    vector<string> headers;
    SetHeadersYoutube(headers);
    int res = APIrequest(URL, headers, readBuffer);
    if (res == -1){
        std::cout << "error createPlaylistFromExistingYoutubePlaylist" << std::endl;
        return ans;
    }
    ParseResponseYoutubeGetPlaylistItems(readBuffer, ans);
    return ans;
}

string PlaylistManagerYoutube::searchSongYoutube(Song &song) {
    string URL = URLsSetter.URLYoutubeSearchSong(song);
    //std::cout << URL << std::endl;
    string readBuffer;
    vector<string> headers;
    SetHeadersYoutube(headers);
    int res = APIrequest(URL, headers, readBuffer);
    if (res == -1){
        std::cout << "error searchSongYoutube" << std::endl;
        return "-1";
    }
    string songId = ParseResponseYoutubeGetSongId(readBuffer);
    return songId;
}

Song PlaylistManagerYoutube::getSongByIdYoutube(string &songId) {
    string URL = URLsSetter.URLYoutubeGetSongById(songId);
    string readBuffer;
    vector<string> headers;
    SetHeadersYoutube(headers);
    Song song ={"",""};
    int res = APIrequest(URL, headers, readBuffer);
    if (res == -1){
        std::cout << "error getSongByIdYoutube" << std::endl;
        return song;
    }
    song = ParseResponseYoutubeGetSongById(readBuffer);
    return song;
}

string PlaylistManagerYoutube::createEmptyPlaylistYoutube() {
    string URL = URLsSetter.URLYoutubeCreateEmptyPlaylist();
    string readBuffer;
    vector<string> headers;
    SetHeadersYoutube(headers);
    json postParametersJson;
    postParametersJson["snippet"]["title"] = "New Playlist";
    postParametersJson["status"]["privacyStatus"] = "public";
    string postParameters = postParametersJson.dump();
    int res = APIrequest(URL, headers, readBuffer, "post", postParameters);
    if (res == -1){
        std::cout << "error createEmptyPlaylistYoutube" << std::endl;
        return "-1";
    }
    string playlistId = ParseResponseYoutubeCreateEmptyPlaylist(readBuffer);
    return playlistId;
}

bool PlaylistManagerYoutube::addSongYoutube(Song &song, string &playlistId) {
    string URL = URLsSetter.URLYoutubeAddSong();
    string readBuffer;
    vector<string> headers;
    SetHeadersYoutube(headers);
    string songId = searchSongYoutube(song);
    json postParametersJson;
    postParametersJson["snippet"]["playlistId"] = playlistId;
    postParametersJson["snippet"]["resourceId"]["videoId"] = songId;
    postParametersJson["snippet"]["resourceId"]["kind"]="youtube#video";
    string postParameters = postParametersJson.dump();
    int res = APIrequest(URL, headers, readBuffer, "post", postParameters);
    //std::cout << readBuffer << std::endl;
    if (res == -1){
        std::cout << "error addSongYoutube" << std::endl;
        return false;
    } 
    return true;
}
