// import io from 'socket.io-client';
import Vue from 'vue';
import Vuex, {ActionContext} from 'vuex';
import {ActionTree, GetterTree, MutationTree} from 'vuex';
import {ChatMessage} from './models/ChatMessage';

Vue.use(Vuex);


const host =
    `ws://${process.env.VUE_APP_SERVER}:${process.env.VUE_APP_SERVERPORT}/`;
const debug = process.env.environment !== 'production';

// export const socket = io.connect(host, {transports: ['websocket',
// 'polling']});
export const socket = new WebSocket(host);

// Store specifics
export class State {
  public user: string = '';
  public chatMessages: ChatMessage[] = [];
  public errorMessage: string = '';
  public hasError: boolean = false;
}

const getterTree: GetterTree<State, any> = {};

const mutationTree: MutationTree<State> = {
  setUser(state: State, newName: string) {
    state.user = newName;
  },
  addMessage(state: State, newMessage: ChatMessage) {
    state.chatMessages.push(newMessage);
  },
  setError(state: State, errorMessage: string) {
    state.errorMessage = errorMessage;
    state.hasError = true;
  },
  clearError(state: State) {
    state.errorMessage = '';
    state.hasError = false;
  },
};

const actionTree: ActionTree<State, any> = {
  async joinChat({commit}, userName: string) {
    commit('setUser', userName);
    socket.onmessage = (ev: MessageEvent) => {
      const msg = JSON.parse(ev.data);
      if (msg.type === 'sendMessage') {
        commit('addMessage', msg.message);
      } else if (msg.type === 'errorMessage') {
        commit('setError', msg.message);
      }
    };
    socket.send(JSON.stringify({type: 'joinChat', message: userName}));
  },
  async sendMessage({}: ActionContext<State, any>, message: ChatMessage) {
    socket.send(JSON.stringify({type: 'sendMessage', message}));
  },
};

export default new Vuex.Store({
  state: new State(),
  getters: getterTree,
  mutations: mutationTree,
  actions: actionTree,
  strict: debug,
});
