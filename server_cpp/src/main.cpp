#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/WebSocket.h"
#include "rapidjson/document.h"
#include <unordered_map>
#include <string>

namespace server_cpp
{

struct ChatHandler : seasocks::WebSocket::Handler
{
private:
    const std::shared_ptr<seasocks::Logger> logger;
    std::unordered_map<seasocks::WebSocket *, std::string> connections;
    std::unordered_map<std::string, seasocks::WebSocket *> names;
    const std::string error = "{ \"type\":\"errorMessage\", \"message\":\"The user did not exist.\"}";

public:
    ChatHandler(const std::shared_ptr<seasocks::Logger> &logger) : logger(logger)
    {
    }

    void onConnect(seasocks::WebSocket *socket) override
    {
        connections.insert({socket, ""});
    }
    void onData(seasocks::WebSocket *socket, const char *data) override
    {
        logger->info(data);

        rapidjson::Document incoming_data;
        incoming_data.Parse(data);
        auto type = incoming_data["type"].GetString();
        auto &message = incoming_data["message"];

        if (std::string("joinChat").compare(type) == 0)
        {
            auto username = message.GetString();
            names.insert({username, socket});
        }
        else if (std::string("sendMessage").compare(type) == 0)
        {
            auto toUser = message.GetObject()["toUser"].GetString();
            auto fromUser = message.GetObject()["fromUser"].GetString();

            if (names.find(toUser) != names.end())
            {
                if (std::string(toUser).compare(std::string(fromUser)) != 0)
                {
                    // only send to other to and from are the same
                    names[toUser]->send(data);
                }
                socket->send(data);
            }
            else
            {
                socket->send(error);
            }
        }
    }
    void onDisconnect(seasocks::WebSocket *socket) override
    {
        names.erase(connections.at(socket));
        connections.erase(socket);
    }
};

void chat()
{
    auto logger = std::make_shared<seasocks::PrintfLogger>();
    seasocks::Server server(logger);
    server.addWebSocketHandler("/", std::make_shared<ChatHandler>(logger));
    server.serve("ws", 3000);
}

} // namespace server_cpp

int main()
{
    server_cpp::chat();
}