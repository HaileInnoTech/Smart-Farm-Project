<template>
  <div>
    <canvas id="myChart"></canvas>
  </div>
</template>

<script>
import{ Chart} from "chart.js/auto";

export default {
  props: {
    humidityData: {
      type: Array,
      required: true,
    },
    temperatureData: {
      type: Array,
      required: true,
    },
    timeData: {
      type: Array,
      required: true,
    },
  },
  mounted() {
    const data = {
      labels: this.timeData,
      datasets: [
        {
          label: "Humidity",
          data: this.humidityData,
          fill: false,
          borderColor: "rgb(75, 192, 192)",
          tension: 0.1,
        },
      ],
    };
    const config = {
      type: "line",
      data: data,
      options: {
        scales: {
          y: {
            beginAtZero: true,
          },
        },
      },
    };
    const myChart = new Chart(document.getElementById("myChart"), config);
  },
};
</script>

<style>
/* Add your styles if needed */
</style>
