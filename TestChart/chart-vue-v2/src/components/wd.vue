<template>
  <button @click="fetchData">Fetch Data</button>

  <div>
    <h1>Humidity Data</h1>
    <div v-for="(value, key) in humidityData" :key="key">
      {{ value }} 
    </div>
  </div>
</template>

<script>
import { initializeApp } from 'firebase/app';
import { getDatabase, ref, onValue } from 'firebase/database';

const firebaseConfig = {
  apiKey: "AIzaSyAOmVngCIDg_WpMykay6NeKttHJPDu0pHc",
  authDomain: "smart-farming-system-f9435.firebaseapp.com",
  databaseURL: "https://smart-farming-system-f9435-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "smart-farming-system-f9435",
  storageBucket: "smart-farming-system-f9435.appspot.com",
  messagingSenderId: "733693187694",
  appId: "1:733693187694:web:704e1bb3467cdbcae3f87f",
  measurementId: "G-BBK4EYQ8BQ"
};
const firebaseApp = initializeApp(firebaseConfig);
const database = getDatabase(firebaseApp);
const humidityRef = ref(database, '/Temp-Humid/humidity');
const temperatureRef = ref(database, '/Temp-Humid/temperature');
const timeRef = ref(database, '/Temp-Humid/timestamp');

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
    this.fetchData();
    this.UpdateData();
  },
  methods: {
    fetchData() {
      const url =
        "https://us-central1-smart-farming-system-f9435.cloudfunctions.net/app/data";
      fetch(url)
        .then((response) => response.json())
        
        .then((data) => {
          console.log(data);
          const humidityArray = Object.values(data.humidity);
          this.humidityData = humidityArray.reverse();
          this.humidityData = this.humidityData.reverse().slice(0,10);

         const temperatureArray= Object.values(data.temperature);
         this.temperatureData = temperatureArray.reverse();
         this.temperatureData = this.temperatureData.reverse().slice(0,10);

         const timeArray= Object.values(data.timestamp);
          this.timeData = timeArray.reverse();
          this.timeData = this.timeData.reverse().slice(0,10);

          console.log(this.humidityData);
          console.log(this.temperatureData);
          console.log(this.timeData);
        }
        )
        .catch((error) => {
          console.error('Error fetching data:', error);
    // Handle the error or provide appropriate feedback to the user
        });

    },

  UpdateData(){
    onValue(humidityRef, (snapshot) => {
      const newObject = snapshot.val();
      console.log('Humidity data changed:', newObject);
      this.humidityData = Object.values(newObject);
      if (this.humidityData.length>10){
        this.humidityData = this.humidityData.reverse().slice(0,10);
        this.humidityData = this.humidityData.reverse();
      }
    });
   
    onValue(temperatureRef, (snapshot) => {
      const newObject = snapshot.val();
      console.log('Temperature data changed:', newObject);
      this.temperatureData = Object.values(newObject);
      if (this.temperatureData.length>10){
        this.temperatureData = this.temperatureData.reverse().slice(0,10);
        this.temperatureData = this.temperatureData.reverse();
      }
    });
    onValue(timeRef, (snapshot) => {
      const newObject = snapshot.val();
      console.log('Time data changed:', newObject);
      this.timeData = Object.values(newObject);
      if (this.timeData.length>10){
        this.timeData = this.timeData.reverse().slice(0,10);
        this.timeData = this.timeData.reverse();
      }
    } );
  }
  },
};
</script>

<style>
  /* Add your styles here */
  button {
    margin-bottom: 10px;
  }

 
</style>
