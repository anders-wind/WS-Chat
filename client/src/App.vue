<template>
  <v-app>
    <v-app-bar app>
      <v-toolbar-title class="headline text-uppercase">
        <span>WS</span>
        <span class="font-weight-light">Chat</span>
      </v-toolbar-title>
      <v-spacer></v-spacer>
      <v-btn text href="https://github.com/awia00/P2P-chat" target="_blank">
        <span class="mr-2">Github</span>
      </v-btn>
    </v-app-bar>

    <v-content>
      <ChatComponent />
      <Error />
    </v-content>
  </v-app>
</template>

<script lang="ts">
import Vue from 'vue';
import ChatComponent from './components/ChatComponent.vue';
import Error from './components/Error.vue';

export default Vue.extend({
  name: 'App',
  components: {
    ChatComponent,
    Error,
  },
  data: () => ({
    //
  }),
});
</script>
