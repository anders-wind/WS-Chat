#include "seasocks/util/Json.h"
#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/WebSocket.h"

#include <set>

namespace server_cpp
{

struct ChatHandler : seasocks::WebSocket::Handler
{
    std::set<seasocks::WebSocket *> connections;

    void onConnect(seasocks::WebSocket *socket) override
    {
        connections.insert(socket);
    }
    void onData(seasocks::WebSocket *, const char *data) override
    {
        for (auto c : connections)
            c->send(data);
    }
    void onDisconnect(seasocks::WebSocket *socket) override
    {
        connections.erase(socket);
    }
};

void chat()
{
    seasocks::Server server(std::make_shared<seasocks::PrintfLogger>());
    server.addWebSocketHandler("/chat", std::make_shared<ChatHandler>());
    server.serve("web", 3000);
}

} // namespace server_cpp

int main()
{
    server_cpp::chat();
}