<template>
  <div style="width: 700px">
    <canvas id="myChart"></canvas>
  </div>
</template>

<script>
import firebaseApp from "../firebase";
import { getDatabase, ref, onValue } from "firebase/database";
import { Chart } from "chart.js/auto";

const database = getDatabase(firebaseApp);
const humidityRef = ref(database, "/Temp-Humid/humidity");
const temperatureRef = ref(database, "/Temp-Humid/temperature");
const timeRef = ref(database, "/Temp-Humid/timestamp");

export default {
  data() {
    return {
      humidityData: [],
      temperatureData: [],
      timeData: [],
    };
  },
  created() {
    this.humidityData = null;
    this.temperatureData = null;
    this.timeData = null;
    this.fetchData();
    this.UpdateData();
  },
  mounted() {},
  methods: {
    async fetchData() {
      try {
        const url =
          "https://us-central1-smart-farming-system-f9435.cloudfunctions.net/app/data";
        const response = await fetch(url);
        const data = await response.json();

        const humidityArray = Object.values(data.humidity);
        this.humidityData = humidityArray.reverse().slice(0, 10);
        this.humidityData = this.humidityData.reverse();

        const temperatureArray = Object.values(data.temperature);
        this.temperatureData = temperatureArray.reverse().slice(0, 10);
        this.temperatureData = this.temperatureData.reverse();

        const timeArray = Object.values(data.timestamp);
        this.timeData = timeArray.reverse().slice(0, 10);
        this.timeeData = this.timeData.reverse();
        this.setupChart();
      } catch (error) {
        console.error("Error fetching data:", error);
      }
    },

    UpdateData() {
      onValue(humidityRef, (snapshot) => {
        try {
          const newObject = snapshot.val();
          this.humidityData = Object.values(newObject);
          if (this.humidityData.length > 10) {
            this.humidityData = this.humidityData.reverse().slice(0, 10);
            this.humidityData = this.humidityData.reverse();
          }
        } catch (error) {
          console.error("Error in humidity callback:", error);
        }
      });

      onValue(temperatureRef, (snapshot) => {
        try {
          const newObject = snapshot.val();
          this.temperatureData = Object.values(newObject);
          if (this.temperatureData.length > 10) {
            this.temperatureData = this.temperatureData.reverse().slice(0, 10);
            this.temperatureData = this.temperatureData.reverse();
          }
        } catch (error) {
          console.error("Error in temperature callback:", error);
        }
      });

      onValue(timeRef, (snapshot) => {
        try {
          const newObject = snapshot.val();
          this.timeData = Object.values(newObject);
          if (this.timeData.length > 10) {
            this.timeData = this.timeData.reverse().slice(0, 10);
            this.timeData = this.timeData.reverse();
          }
          this.setupChart();
        } catch (error) {
          console.error("Error in time callback:", error);
        }
      });
    },
    setupChart() {
      if (this.myChart) {
        this.myChart.destroy();
      }

      const grapharea = document.getElementById("myChart").getContext("2d");
      const data = {
        labels: this.timeData,
        datasets: [
          {
            label: "Humidity",
            data: this.humidityData,
            fill: false,
            borderColor: "rgb(75, 192, 192)",
            backgroundColor: "rgb(75, 192, 192, 0.5)",
            tension: 0.2,
          },
          {
            label: "Temperature",
            data: this.temperatureData,
            fill: false,
            borderColor: "rgb(255, 99, 132)",
            backgroundColor: "rgb(255, 99, 132, 0.5)",
            tension: 0.2,
          },
        ],
      };
      const config = {
        type: "line",
        data: data,
        options: {
          interaction: {
            intersect: false,
          },
          plugins: {
            legend: {
              position: "top",
            },
            title: {
              display: true,
              text: "Humidity and Temperature Chart",
            },
          },

          scales: {
            y: {
              beginAtZero: true,
            },
          },
        },
      };
      // Create a new chart
      this.myChart = new Chart(grapharea, config);
    },
  },
};
</script>

<style>
/* Add your styles here */
button {
  margin-bottom: 10px;
}

table {
  width: 100%;
  border-collapse: collapse;
  margin-top: 10px;
}

th,
td {
  border: 1px solid #ddd;
  padding: 8px;
  text-align: left;
}

th {
  background-color: #f2f2f2;
}
</style>
