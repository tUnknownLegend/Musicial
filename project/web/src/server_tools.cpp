#include "server_tools.h"

//#include "../../api/include/api.h"
#include "../../api/include/apiSpotify.h"
#include "../../api/include/apiYoutube.h"

namespace server_tools {
    int startServer() {
        std::cout << "Info: 'hostname -I' to get local ip" << std::endl;
        try {
            std::string ip, port;
            std::cout << "Enter IP: ";
            std::cin >> ip;

            std::cout << "Enter port: ";
            std::cin >> port;

            auto num_threads = (std::size_t) sysconf(_SC_NPROCESSORS_ONLN);
            http::server3::server s(ip, port, num_threads);

            // Run the server until stopped.
            s.run();
        }


        catch (std::exception &e) {
            std::cerr << "exception: " << e.what() << "\n";
        }

        return 0;
    }
}  // namespace server_tools

Response HandlerConvertPlaylist(const Request &request) {
    //sharedLib::Message ans = net_tools::getAnswer(request.body);
    Response response;

    Settings S;
    PlaylistManagerSpotify B(S.getOAuthTokenSpotify(), S.getUserIdSpotify());

    // remove
    //std::string ref = "https://open.spotify.com/playlist/1hBbNxTjcitTZfu51dB7RB?si=4eb76190d17d479c";
    //playlists.push_back(ref);
    //playlists.push_back(sharedLib::URL(ref), sharedLib::Platform::Spotify);
    response.body.text = "Playlist:";

    /*
    std::vector<std::string> playlists;
    for (const auto& i : request.body.playlists) {
        playlists.push_back(i.ref.link);
    }

    std::vector<std::string> songs;
    for (const auto& i : request.body.songs) {
        songs.push_back(i.ref.link);
    }
*/

    std::vector<std::string> playlists;
    std::vector<std::string> songs;
    playlists.emplace_back("https://open.spotify.com/playlist/6mQNMb22J9Rp5QPALHUeFr");
    playlists.emplace_back("https://open.spotify.com/playlist/1hBbNxTjcitTZfu51dB7RB");
    songs.emplace_back("https://open.spotify.com/track/11dFghVXANMlKmJXsNCbNl");

    sharedLib::URL convertedPlaylist;
    sharedLib::Platform platform;
    vector<sharedLib::Platform> temp;
    temp.push_back(sharedLib::YouTube);
    temp.push_back(sharedLib::Spotify);
    //request.body.toPlatform;
    for (auto& i : temp) {
        switch(i) {
            case sharedLib::YouTube:
                // convertedPlaylist.link = метод для YT
                convertedPlaylist.link = "https://www.youtube.com/playlist?list=PLcidtVPGDsUWcrT65QjefzB8syuGpgDoN";
                platform = sharedLib::YouTube;
                response.body.playlists.emplace_back(convertedPlaylist, platform);
                break;
            case sharedLib::Spotify:
                convertedPlaylist.link = B.createSpotifyPlaylistFromPlatformRefsAndSongsLists(playlists.begin(), playlists.end(), songs.begin(), songs.end(), S.getUserIdSpotify());
                //"https://open.spotify.com/playlist/1hBbNxTjcitTZfu51dB7RB";
                // convertedPlaylist.link = метод для Spotify
                platform = sharedLib::Spotify;
                response.body.playlists.emplace_back(convertedPlaylist, platform);
                break;
            default:
                break;
        }
    }

    //response.body.playlists.emplace_back(convertedPlaylist, platform); // correct
    response.body.playlistNumber = response.body.playlists.size();
    response.body.songsNumber = 0;
    response.body.toPlatformNumber = 0;
    response.status_code = 200;
    response.status_message = "OK";
    response.http_version = "HTTP/1.1";

    return response;
}

Response HandlerEcho(const Request &request) {
    Response response;


    response.status_code = 200;
    response.status_message = "OK";
    response.http_version = "HTTP/1.1";

    response.body = request.body;

    return response;
}

Response HandlerTest(const Request &request) {
    Response response;

    response.status_code = 200;
    response.status_message = "OK";
    response.http_version = "HTTP/1.1";

    response.body = net_tools::getMessage();

    return response;
}


namespace http {
    namespace server3 {
        server::server(const std::string &address, const std::string &port,
                       std::size_t thread_pool_size)
                : thread_pool_size_(thread_pool_size),
                  signals_(io_context_),
                  acceptor_(io_context_),
                  new_connection_() {
            // Register to handle the signals that indicate when the server should exit.
            signals_.add(SIGINT);   // остановка процесса с терминала
            signals_.add(SIGTERM);  // сигнал от kill
            signals_.async_wait(boost::bind(&server::handle_stop, this));

            request_router.addHandler("convert_playlist", HandlerConvertPlaylist);
            request_router.addHandler("echo", HandlerEcho);
            request_router.addHandler("test", HandlerTest);

            // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
            boost::asio::ip::tcp::resolver resolver(io_context_);
            boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
            acceptor_.open(endpoint.protocol());
            acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            acceptor_.bind(endpoint);
            acceptor_.listen();

            start_accept();
        }

        void server::run() {
            std::cout << "Server is running with " << thread_pool_size_ << " threads" << std::endl;
            // Create a pool of threads to run all of the io_contexts.
            std::vector<boost::shared_ptr<std::thread> > threads;

            for (std::size_t i = 0; i < thread_pool_size_; ++i) {
                boost::shared_ptr<std::thread> thread(new std::thread(
                        [ObjectPtr = &io_context_] { ObjectPtr->run(); }));
                threads.push_back(thread);
            }

            // Wait for all threads in the pool to exit.
            for (auto &thread: threads)
                thread->join();
        }

        void server::start_accept() {
            new_connection_.reset(new Connection(io_context_, request_router));
            acceptor_.async_accept(new_connection_->socket(),
                                   boost::bind(&server::handle_accept, this,
                                               boost::asio::placeholders::error));
        }

        void server::handle_accept(const boost::system::error_code &e) {
            if (!e) {
                new_connection_->start();
            }

            start_accept();
        }

        void server::handle_stop() {
            io_context_.stop();
        }

    }  // namespace server3
}  // namespace http

struct Token {
    explicit Token(std::string t) :
            token(std::move(t)) {
    }

    std::string token;
};

class platformAccess {
public:
    bool addToken(sharedLib::Platform p, const Token &t) {
        auto res = tokens.insert({p, t});
        return !res.second;
    }

    bool updateToken(sharedLib::Platform p, const Token &t) {
        if (tokens.contains(p)) {
            tokens.at(p) = t;
            return true;
        } else {
            return false;
        }
    }

    Token getPlatformToken(sharedLib::Platform p) {
        if (tokens.contains(p)) {
            return tokens.at(p);
        } else {
            return Token("");
        }
    }

private:
    std::map<sharedLib::Platform, Token> tokens;
};
