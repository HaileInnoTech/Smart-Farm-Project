<template>
  <div>
    <canvas id="myChart" width="400" height="400"></canvas>
  </div>
</template>

<script>
import Chart from "chart.js";
import "chartjs-plugin-streaming";

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
    this.drawChart();
  },
  methods: {
    drawChart() {
      var ctx = document.getElementById("myChart").getContext("2d");
      var myChart = new Chart(ctx, {
        type: "line",
        data: {
          labels: [],
          datasets: [
            {
              label: "Temperature",
              data: [],
              backgroundColor: "rgba(255, 99, 132, 0.2)",
              borderColor: "rgba(255, 99, 132, 1)",
              borderWidth: 1,
              fill: false, // Set to false to make it a line chart for streaming
            },
          ],
        },
        options: {
          scales: {
            xAxes: [
              {
                type: "realtime",
                realtime: {
                  onRefresh: this.refreshChart,
                  delay: 1000,
                },
              },
            ],
            yAxes: [
              {
                ticks: {
                  beginAtZero: true,
                },
              },
            ],
          },
        },
      });
    },
    refreshChart: function (chart) {
      // Add new data here
      chart.data.labels.push(Date.now());
      chart.data.datasets[0].data.push(Math.random() * 50);

      // Limit the number of data points shown on the chart
      const maxDataPoints = 10;
      while (chart.data.labels.length > maxDataPoints) {
        chart.data.labels.shift();
        chart.data.datasets[0].data.shift();
      }
    },
  },
};
</script>
