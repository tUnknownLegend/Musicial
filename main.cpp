//#include "api.h"
#//include "apiYoutube.h"
//#include "apiSpotify.h"
#include "apiConvertHandlers.h"

int main()
{
    Settings S;

      PlaylistManagerYoutube A(S.getApiKeyYoutube(), S.getOAuthTokenYoutube());
    // string st = "PL6AVWk5NUegUV-FWNYbCG_ykC13vevU_6";
    // Playlist B = A.createPlaylistFromExistingYoutubePlaylist(st);
    // for(int i = 0; i < B.songs.size(); i++){
    //     std::cout <<  B.songs[i].songName << "-" << B.songs[i].artist << std::endl;
    // }
    string plref1 = "https://youtube.com/playlist?list=PL6AVWk5NUegW4wPkPtFE5FXXvoeyBEZYI";
    string songref1 = "https://www.youtube.com/watch?v=bESGLojNYSo";
    vector<string> songs;
    vector<string> play;
    songs.push_back(songref1);
    play.push_back(plref1);
    //string st = createYoutubePlaylistFromPlatformRefsAndSongsLists(play.begin(), play.end(), songs.begin(), songs.end());
    //string st = createSpotifyPlaylistFromPlatformRefsAndSongsLists(play.begin(), play.end(), songs.begin(), songs.end(), S.getUserIdSpotify());
    //string ref = "https://www.youtube.com/watch?v=bESGLojNYSo";
    //string id = getIdFromURL(ref);
    //string ref = "PL6AVWk5NUegWPGovi-nUk_2bInxdrrhww";
    //std::cout << st << std::endl;
    Song D = {"Before I Forget", "Slipknot"};
    //bool t = A.addSongYoutube(D, ref);
    //https://www.youtube.com/watch?v=bESGLojNYSo;
    //Song s1 = A.getSongByIdYoutube(ref);
    //std::cout <<  s1.songName << "-" << s1.artist << std::endl;

    //string g = A.createEmptyPlaylistYoutube();
    //std::cout <<  g << std::endl;
    //PL6AVWk5NUegUwqGA_taYm1NlCFfi2wuh6
    vector<Song> E;
    //Song D = {"Before I Forget", "Slipknot"};
    Song F = {"Skyfall", "Adele"};
    E.push_back(D);
    E.push_back(F);
    //string ref = "PL6AVWk5NUegX3hnJ9ri9kJCBhx1NLNvm0";
    //string g = A.createYoutubePlaylistFromSonglist(E.begin(), E.end());
    //bool t = A.addSongYoutube(F, ref);
    //std::cout <<  g << std::endl;

    // RefsForURL playlistRefsSpotify = {"https://api.spotify.com/v1/playlists/",
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

    
    
    //B.songs.push_back(A);
    //string s = URLSpotifySearchSong(A);
    //string s = createEmptyPlaylistSpotify(userIdSpotify,OAuthTokenSpotify);
    //std::cout <<  s << std::endl;

    // string playlistId = "3OIW9zDn6coCdVGMpBa6vC";
    // if(addSongSpotify(A, playlistId)){
    //     std::cout << "added" << std::endl;
    // }
    //string st = getIdFromURL(str);
    //Song s = B.getSongByIdSpotify(st);
    //std::cout << S.getOAuthTokenSpotify() << ' ' << S.getUserIdSpotify() << std::endl;

    // PlaylistManagerSpotify B(S.getOAuthTokenSpotify(), S.getUserIdSpotify());
    // string song1 = "https://open.spotify.com/track/11dFghVXANMlKmJXsNCbNl";
    // vector<string> playlistRefs;
    // vector<string> songRefs;
    // songRefs.push_back("https://open.spotify.com/track/11dFghVXANMlKmJXsNCbNl");
    // playlistRefs.push_back("https://open.spotify.com/playlist/6mQNMb22J9Rp5QPALHUeFr");
    // playlistRefs.push_back("https://open.spotify.com/playlist/1hBbNxTjcitTZfu51dB7RB");
    // string ref = B.createSpotifyPlaylistFromPlatformRefsAndSongsLists(playlistRefs.begin(), playlistRefs.end(), songRefs.begin(), songRefs.end(), S.getUserIdSpotify());
    // std::cout << ref << std::endl;
    //3OIW9zDn6coCdVGMpBa6vC
    return 0;
}