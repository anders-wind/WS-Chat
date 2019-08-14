<template>
  <v-container fill-height>
    <v-layout align-space-around justify-end column fill-height>
      <v-flex v-if="!usernameChoosen">
        <v-text-field label="Enter Username" v-model="usernameField"></v-text-field>
        <v-btn color="info" @click="joinChat()" :disabled="usernameField.length < 1">Join Chat</v-btn>
      </v-flex>
      <v-flex v-if="usernameChoosen" scrollable>
        <h2>Chatting as: '{{username}}'</h2>
        <v-card>
          <v-card-title primary-title>Message Board</v-card-title>
          <v-card-text>
            <v-list three-line>
              <v-list-item v-for="item in chatMessages" :key="item.time.toLocaleString()">
                <v-list-item-content>
                  <v-list-item-title v-text="item.fromUser"></v-list-item-title>
                  <v-list-item-subtitle v-text="item.time.toLocaleString()"></v-list-item-subtitle>
                  <v-list-item-subtitle class="text--primary" v-text="item.message"></v-list-item-subtitle>
                </v-list-item-content>
              </v-list-item>
            </v-list>
          </v-card-text>
        </v-card>
      </v-flex>
      <v-card v-if="usernameChoosen">
        <v-card-text>
          <v-text-field label="Write to" v-model="targetUsernameField"></v-text-field>
          <v-text-field label="Message" v-model="messageField"></v-text-field>
          <v-btn color="info" @click="sendMessage()" :disabled="!canSendMessage">Send Message</v-btn>
        </v-card-text>
      </v-card>
    </v-layout>
  </v-container>
</template>

<script lang="ts">
import { Component, Vue } from 'vue-property-decorator';
import { ChatMessage } from '../models/ChatMessage';
import store from '../store';

@Component({
  components: {},
})
export default class DataPicker extends Vue {
  public usernameField: string = '';
  public targetUsernameField: string = '';
  public messageField: string = '';

  set username(value: string) {
    this.$store.commit('setUser', value);
  }
  get username(): string {
    return this.$store.state.user;
  }

  get usernameChoosen(): boolean {
    return !!this.username;
  }

  get chatMessages(): ChatMessage[] {
    return this.$store.state.chatMessages;
  }

  get canSendMessage(): boolean {
    return (
      !!this.targetUsernameField && this.usernameChoosen && !!this.messageField
    );
  }

  public async joinChat() {
    this.username = this.usernameField;
    await this.$store.dispatch('joinChat', this.username);
  }

  public async sendMessage() {
    if (!this.canSendMessage) {
      return;
    }
    const chatMessage: ChatMessage = {
      fromUser: this.username,
      toUser: this.targetUsernameField,
      message: this.messageField,
      time: new Date(),
    };
    await this.$store.dispatch('sendMessage', chatMessage);
    this.messageField = '';
  }
}
</script>

<style lang="scss" scoped>
</style>
