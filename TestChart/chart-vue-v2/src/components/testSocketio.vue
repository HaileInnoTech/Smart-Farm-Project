<template>
  <div>
    <h1>Hello World</h1>
    <p>{{ message }}</p>
    <div v-for="key in data" :key="key">
      <p>{{ key }}</p>
    </div>
    <div>
      <Line :data="chartData" :options="chartOptions" :style="chartStyles" />
    </div>
  </div>
</template>

<script>
import { Line } from "vue-chartjs";
import io from "socket.io-client";
import * as Utils from "../../Utils.js";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

export default {
  components: {
    Line,
  },

  data() {
    return {
      message: "Hello World",
      data: [],
      humidityData: [],
      temperatureData: [],
      timeData: [],
    };
  },
  created() {
    // Connect to Socket.IO server
    const socket = io("http://localhost:3000");
    socket.on("connect", () => {
      console.log("Connected to server");
    });

    // Event listener for receiving data from server
    socket.on("updateData", (data) => {
      this.updateChartData(data);
    });

    socket.on("initData", (data) => {
      this.updateChartData(data);
    });
  },
  methods: {
    updateChartData(data) {
      this.humidityData = [];
      this.temperatureData = [];
      this.timeData = [];
      this.data = data;

      data.forEach((item) => {
        this.humidityData.push(item.humidity);
        this.temperatureData.push(item.temperature);
        this.timeData.push(item.timestamp.replace("T", " ").slice(0, 19));
      });
    },
  },
  computed: {
    chartData() {
      return {
        labels: this.timeData,
        datasets: [
          {
            label: "Humidity",
            data: this.humidityData,
            fill: false,
            borderColor: Utils.CHART_COLORS.red,
            backgroundColor: Utils.transparentize(Utils.CHART_COLORS.red, 0.5),
            tension: 0.4,
          },
          {
            label: "Temperature",
            data: this.temperatureData,
            fill: false,
            borderColor: Utils.CHART_COLORS.blue,
            backgroundColor: Utils.transparentize(Utils.CHART_COLORS.blue, 0.5),
            tension: 0.2,
          },
        ],
      };
    },
    chartOptions() {
      return {
        responsive: true,
        interaction: {
          intersect: false,
        },
        plugins: {
          title: {
            display: true,
            text: "Humidity and Temperature Data",
          },
          legend: {
            position: "bottom",
          },
        },

        maintainAspectRatio: false,
        scales: {
          y: {
            beginAtZero: true,
          },
        },
      };
    },
    chartStyles() {
      return {
        height: "600px",
        width: "800px",
      };
    },
  },
};
</script>

<style></style>
