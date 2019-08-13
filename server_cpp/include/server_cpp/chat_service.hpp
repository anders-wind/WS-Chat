#include "seasocks/Logger.h"
#include "seasocks/WebSocket.h"
#include "rapidjson/document.h"
#include <unordered_map>
#include <string>

struct ChatService : seasocks::WebSocket::Handler
{
private:
    const std::shared_ptr<seasocks::Logger> logger;
    std::unordered_map<seasocks::WebSocket *, std::string> connections;
    std::unordered_map<std::string, seasocks::WebSocket *> names;
    const std::string error = "{ \"type\":\"errorMessage\", \"message\":\"The user did not exist.\"}";

public:
    ChatService(const std::shared_ptr<seasocks::Logger> &logger) : logger(logger)
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
            joinChat(socket, message);
        }
        else if (std::string("sendMessage").compare(type) == 0)
        {
            sendMessage(socket, message, data);
        }
    }
    void onDisconnect(seasocks::WebSocket *socket) override
    {
        names.erase(connections.at(socket));
        connections.erase(socket);
    }

private:
    void joinChat(seasocks::WebSocket *socket, const rapidjson::Value &message)
    {
        auto username = message.GetString();
        names.insert({username, socket});
    }

    void sendMessage(seasocks::WebSocket *socket, const rapidjson::Value &message, const char *data)
    {
        auto toUser = message.GetObject()["toUser"].GetString();
        auto fromUser = message.GetObject()["fromUser"].GetString();

        if (names.find(toUser) != names.end())
        {
            if (std::string(toUser).compare(std::string(fromUser)) != 0)
            {
                // we will only send to "toUser" if it is not the same as the sender
                names[toUser]->send(data);
            }
            socket->send(data);
        }
        else
        {
            socket->send(error);
        }
    }
};