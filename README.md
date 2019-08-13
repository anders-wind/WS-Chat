# P2P-Chat
A simple websocket based chat system.

## How to Build/Run

Make sure to run: `git submodule init && git submodule update`

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
