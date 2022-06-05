//#include "api.h"
#include "apiYoutube.h"
#include "apiSpotify.h"

// struct RefsForURL{
//     std::string ApiUrl;
//     std::string ApiKey;
//     std::string playlistID;
//     std::string OAuthToken;
// };

int main()
{
    // RefsForURL playlistRefs = {"https://www.googleapis.com/youtube/v3/playlistItems",
    //             "AIzaSyC3-MWvfyHVPjEVn8XYZd-HMVpc_mlxNHE",
    //             "PL6AVWk5NUegUV-FWNYbCG_ykC13vevU_6", ""};
    // string URL1 = GetPlaylistItemsURLYoutube(playlistRefs);
    // vector<string> headers1;
    // SetPlaylistItemsHeadersYoutube(headers1);
    // YoutubePlaylist B = createPlaylistFromExistingYoutubePlaylist(URL1, headers1);
    // for(int i = 0; i < B.songs.size(); i++){
    //     std::cout <<  B.songs[i].songName << "-" << B.songs[i].artist << std::endl;
    // }

    //PlaylistManager<SpotifyPlaylist> SPManager;
    // RefsForURL playlistRefs2 = {"https://api.spotify.com/v1/playlists/",
    //             "",
    //             "6DlkmnKtGkaGy0hCKaqi15",
    //             "BQAkqqRkL8hskcLBGOCuazmqmPYMszSLziG8hfA_c2xctGN_IBmncQRA1rHD0D0r4pfMoBwfMBItZT1Alb-JpSXvBIN7rocu7DooVLvJ2PROUfWnyIjIOrhrkfnsDe2ftKFje10N0KLznH1OlPKfqG3LR9zC22af_4NgXv1WN12gSsiMJz2fFqiah1vR0LEC-tpd87ZT6oUEiTJlz77C31thjiUu2HI"};
    // string URL2 = URLSpotifyGetPlaylistItems(playlistRefs2);
    
    // SpotifyPlaylist C = createPlaylistFromExistingSpotifyPlaylist(URL2, headers2);
    // for(int i = 0; i< C.songs.size(); i++){
    //     std::cout <<  C.songs[i].songName << " - " << C.songs[i].artist << std::endl;
    // }
    // std::cout <<  123123 << std::endl;
    // string s = createYoutubePlaylistFromSonglist(C.songs.begin(), C.songs.end());

    Song A = {"Before I Forget", "Slipknot"};
    //B.songs.push_back(A);
    //string s = URLSpotifySearchSong(A);
    //string s = createEmptyPlaylistSpotify(usedIdSpotify,OAuthTokenSpotify);
    //std::cout <<  s << std::endl;
    //string ref = createSpotifyPlaylistFromSonglist(B.songs.begin(), B.songs.end(), usedIdSpotify);
    //std::cout <<  ref << std::endl;
    string playlistId = "3OIW9zDn6coCdVGMpBa6vC";
    if(addSongSpotify(A, playlistId)){
        std::cout << "added" << std::endl;
    }
    //3OIW9zDn6coCdVGMpBa6vC
    return 0;
}