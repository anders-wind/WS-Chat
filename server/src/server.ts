import * as express from 'express';
import * as path from 'path';
import * as socketio from 'socket.io';

const app = express();
const port = process.env.PORT || 8000;
app.set('port', port);

let http = require('http').Server(app);
// set up socket.io and bind it to our
// http server.
let io = require('socket.io')(http);

app.get('/', (req: any, res: any) => {
  res.sendFile(path.resolve('./client/index.html'));
});

// whenever a user connects on port 8000 via
// a websocket, log that a user has connected
io.on('connection', function(socket: any) {
  console.log('a user connected');
});

const server = http.listen(port, function() {
  console.log('listening on *:port');
});