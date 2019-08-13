#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include <memory>
#include "server_cpp/chat_service.hpp"

namespace server_cpp
{

void run_chat_service()
{
    auto logger = std::make_shared<seasocks::PrintfLogger>();
    seasocks::Server server(logger);
    server.addWebSocketHandler("/", std::make_shared<ChatService>(logger));
    server.serve("ws", 3000);
}

} // namespace server_cpp

int main()
{
    server_cpp::run_chat_service();
}