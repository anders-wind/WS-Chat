import express from 'express';
import http from 'http';
import path from 'path';
import socketio from 'socket.io';

import {ChatMessage} from './models/ChatMessage';

const port = process.env.PORT || 3000;

const app = express();
app.set('port', port);

const server = http.createServer(app);
// set up socket.io and bind it to our
// http server.
const io = socketio.listen(server);

const activeUsers: Map<string, socketio.Socket> =
    new Map<string, socketio.Socket>();

// whenever a user connects on port 8000 via
// a websocket, log that a user has connected
io.on('connection', (socket: socketio.Socket) => {
  let username: string|undefined;

  socket.on('joinChat', (name: string) => {
    activeUsers.set(name, socket);
    username = name;
  });
  socket.on('sendMessage', (chatMessage: ChatMessage) => {
    if (activeUsers.has(chatMessage.toUser)) {
      const otherSocket = activeUsers.get(chatMessage.toUser);
      otherSocket.emit('receiveMessage', chatMessage);
      if (chatMessage.fromUser !== chatMessage.toUser) {
        socket.emit('receiveMessage', chatMessage);
      }
    } else {
      socket.emit('errorMessage', 'The user did not exist');
    }
  });
  socket.on('disconnect', () => {
    if (username && activeUsers.has(username)) {
      activeUsers.delete(username);
    }
  });
});

server.listen(port, () => {
  // tslint:disable-next-line: no-console
  console.log('listening on *:' + port);
});
