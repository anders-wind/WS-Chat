<template>
  <v-snackbar v-model="hasError" color="error" multi-line :timeout="timeout">
    {{ errorMessage }}
    <v-btn dark @click="dismiss()">Close</v-btn>
  </v-snackbar>
</template>


<script lang="ts">
import { Prop, Component, Vue, Watch } from 'vue-property-decorator';
@Component({})
export default class Error extends Vue {
  private timeout: number = 0;
  get hasError() {
    return this.$store.state.hasError;
  }
  public dismiss() {
    this.$store.commit('clearError');
  }
  get errorMessage() {
    return this.$store.state.errorMessage;
  }
}
</script>

<style lang="scss" scoped>
</style>