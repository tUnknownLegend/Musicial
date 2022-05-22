#include "server_tools.h"
#include "client.h"

#include "nlohmann/json.hpp"
#include "../../../../api/include/api.h"



int main() {
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

    server_tools::startServer();
    net_tools::Message message = net_tools::getMessage();
    client::sendMessage("0.0.0.0", "5000", "/test", message);

    return 0;
}

