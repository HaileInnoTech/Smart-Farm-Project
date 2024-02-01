import { createApp } from 'vue'
import App from './App.vue'
import VueApexCharts from "vue3-apexcharts";
import { Bar } from 'vue-chartjs'
const app = createApp(App);
app.use(Bar);
app.use(VueApexCharts);
app.mount('#app')
