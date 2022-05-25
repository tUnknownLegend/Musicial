// #include "api.h"

// bool YoutubePlaylist::addSong(Song &s){
//     //T ans;
//     string readBuffer;
//     string URL = playlistRef.ApiUrl + "?part=snippet&playlistId=" + playlistRef.playlistID + "&key=" + playlistRef.ApiKey;
//     vector<string> headers;
//     headers.push_back("Accept: application/json");
//     int res = request(URL, headers, readBuffer);
//     if (res == -1)
//         return ans;
//     json responseJson = json::parse(readBuffer);
//     json responseJsonItems = responseJson["items"];
//     for (auto songItem : responseJsonItems)
//     {
//         const char separator = '-';
//         std::string str = songItem["snippet"]["title"];
//         Song song;
//         song.songName = str.substr(0, str.find(separator));
//         if (song.songName.size() != str.size())
//         {
//             str.erase(0, str.find(separator) + 1);
//             song.artist = str;
//         }
//         ans.songs.push_back(song);
//         //std::cout << h["snippet"]["title"] << std::endl;
//     }
//     ans.playlistSize = ans.songs.size();
//     ans.Refs.YoutubeRef = URL;
//     return ans;
// }