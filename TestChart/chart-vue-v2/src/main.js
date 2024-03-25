import { createApp } from "vue";
import App from "./App.vue";
import { Bar } from "vue-chartjs";
const app = createApp(App);
app.use(Bar);
app.mount("#app");
