//int main() { return 0; };


#include <fstream>

#include "../include/api.h"


// struct RefsForURL{
//     std::string ApiUrl;
//     std::string ApiKey;
//     std::string playlistID;
//     std::string OAuthToken;
// };

int maisn()
{
    PlaylistManager<YoutubePlaylist> YPManager;
    RefsForURL playlistRefs = {"https://www.googleapis.com/youtube/v3/playlistItems",
                "AIzaSyC3-MWvfyHVPjEVn8XYZd-HMVpc_mlxNHE",
                "PL6AVWk5NUegUV-FWNYbCG_ykC13vevU_6", ""};
    string URL1 = GetPlaylistItemsURLYoutube(playlistRefs);
    vector<string> headers1;
    GetPlaylistItemsHeadersYoutube(headers1);
    YoutubePlaylist B = YPManager.createExistingPlaylist(URL1, headers1);
    for(int i = 0; i < B.songs.size(); i++){
        std::cout <<  B.songs[i].songName << "-" << B.songs[i].artist << std::endl;
    }

    PlaylistManager<SpotifyPlaylist> SPManager;
    RefsForURL playlistRefs2 = {"https://api.spotify.com/v1/playlists/",
                "",
                "6DlkmnKtGkaGy0hCKaqi15",
                "BQC0e8ZzorvXJ8q5RDEVy8Mmdg3Wz1v8UF0oxYrTzYBd7xfTDbmBmRjiuMhZU7amVeE1PJ355lp4Na89xZUt5U8YfIXzNsPcJDUUqFCXJZRTrl2EflP8qJiJVKwAcy6gbiHdV_0XlV_d4PXU8KyujKJ6rOxnw5o"};
    string URL2 = GetPlaylistItemsURLSpotify(playlistRefs2);
    vector<string> headers2;
    GetPlaylistItemsHeadersSpotify(headers2, playlistRefs2.OAuthToken);
    SpotifyPlaylist C = SPManager.createExistingPlaylist(URL2, headers2);
    for(int i = 0; i< C.songs.size(); i++){
        std::cout <<  C.songs[i].songName << "-" << C.songs[i].artist << std::endl;
    }
    //std::vector<std::string> playlist;
    //FILE* file = fopen("../playlists.txt", "w");
    //     if (file)
    //     {
    //         ofstream out("../playlists.txt");
    //         for(int i = 0; i < playlist.size(); i++){
    //             out << playlist[i] << endl;
    //             //out << data << endl;
    //             //fprintf(file, "%d\n", 1);
    //         }
    //     }
    //     else
    //         cout << "Нет доступа к файлу!" << endl;
    //     fclose(file);
    
    return 0;
}