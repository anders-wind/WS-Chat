# WS-Chat
A simple websocket based chat system.

## Structure
The solution consists of two projects: a [VueJS](https://vuejs.org/) client project written in typescript using [Vuetify](https://vuetifyjs.com/en/) components, and a server written in C++ using the [seasocks](https://github.com/mattgodbolt/seasocks) and [rapidjson](http://rapidjson.org/) frameworks.

The core of the solution is the following files: 
- `client/src/store.ts`
- `client/src/components/ChatComponent.vue`
- `client/src/services/WebSocketService.ts`
- `server_cpp/include/server_cpp/chat_service.hpp`

The chat system works by enabling a user to write his/her name, joining the chat service. At this point the user can then write messages to other users by specifying a username and message. 
The system is ofcourse bare-bones and does not contain a lot of safety mechanisms that one would normally have in a chat system.

## How to Build/Run

Make sure to run: `git submodule init && git submodule update` after cloning the repository, and it is important that you do not have any services running on port `3000` or `8080`.

I have tested the system on Ubuntu 19.04.

Easiest way to run the solution is to run: `docker-compose up`. If you do not have docker or docker-compose installed follow the instructions below.


### Client
```
cd client
yarn install
yarn serve
```

### Server
```
mkdir -p server_cpp/build
cd server/build
cmake ..
cmake --build .
./server_cpp
```

### Demo

- Open two browser tabs at localhost:8080, 
- input usernames in each, press "Join Chat"
- input which user to write to and a message, press "Send Message"

