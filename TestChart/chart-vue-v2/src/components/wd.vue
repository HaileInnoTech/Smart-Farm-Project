<template>
  <div style="width: 700px">
    <canvas id="myChart"></canvas>
  </div>
  <button @click="fetchData">Fetch Data</button>

  <table>
    <thead>
      <tr>
        <th></th>
        <th>Humidity Data</th>
        <th>Temperature Data</th>
        <th>Time Data</th>
      </tr>
    </thead>
    <tbody>
      <tr v-for="(value, key) in humidityData" :key="key">
        <td>{{ key }}</td>
        <td>{{ value }}</td>
        <td>{{ temperatureData[key] }}</td>
        <td>{{ timeData[key] }}</td>
      </tr>
    </tbody>
  </table>
</template>

<script>
import { initializeApp } from "firebase/app";
import { getDatabase, ref, onValue } from "firebase/database";

import Chart from "chart.js/auto";

const firebaseConfig = {
  apiKey: "AIzaSyAOmVngCIDg_WpMykay6NeKttHJPDu0pHc",
  authDomain: "smart-farming-system-f9435.firebaseapp.com",
  databaseURL:
    "https://smart-farming-system-f9435-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "smart-farming-system-f9435",
  storageBucket: "smart-farming-system-f9435.appspot.com",
  messagingSenderId: "733693187694",
  appId: "1:733693187694:web:704e1bb3467cdbcae3f87f",
  measurementId: "G-BBK4EYQ8BQ",
};
const firebaseApp = initializeApp(firebaseConfig);
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
            console.log(this.humidityData);
          }
          this.setupChart();
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
            console.log(this.temperatureData);
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
            console.log(this.timeData);
          }
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
            tension: 0.1,
          },
          {
            label: "Temperature",
            data: this.temperatureData,
            fill: false,
            borderColor: "rgb(255, 99, 132)",
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
