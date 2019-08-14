export class WebSocketService {
  private socket: WebSocket;
  // tslint:disable-next-line: ban-types
  private onMessageMap: Map<string, Function> = new Map<string, Function>();

  constructor(host: string) {
    this.socket = new WebSocket(host);
    this.socket.onmessage = (message: MessageEvent) => {
      const json = JSON.parse(message.data);
      const func = this.onMessageMap.get(json.type);
      if (func) {
        func(json.message);
      }
      return;
    };
  }

  // tslint:disable-next-line: ban-types
  public on(type: string, func: Function) {
    if (this.onMessageMap.has(type)) {
      throw Error('Double websocket on listen');
    }
    this.onMessageMap.set(type, func);
  }

  public emit(type: string, message: any) {
    this.socket.send(JSON.stringify({type, message}));
  }
}
