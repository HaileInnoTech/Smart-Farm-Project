<template>
  <Bar id="my-chart-id" :options="chartOptions" :data="chartData" />

  <div><button @click="getData">Fetch Data</button></div>
</template>

<script>
import { Bar } from 'vue-chartjs'
import { Chart as ChartJS, Title, Tooltip, Legend, BarElement, CategoryScale, LinearScale } from 'chart.js'

ChartJS.register(Title, Tooltip, Legend, BarElement, CategoryScale, LinearScale)

export default {
  name: 'BarChart',
  components: { Bar },
  data() {
    return {
      chartData: {
        labels: ['January', 'February', 'March'],
        datasets: [{ data: [40, 20, 12] }]
      },
      chartOptions: {
        responsive: true
      }
    }
  },
  methods: {
    async getData() {
      const url = 'https://api.blockchain.info/pools?timespan=5days';
      try {
        const response = await fetch(url);
        const data = await response.json();
        console.log(data);

        const randomColors = Array.from({ length: Object.keys(data).length }, () => {
          const r = Math.floor(Math.random() * 256);
          const g = Math.floor(Math.random() * 256);
          const b = Math.floor(Math.random() * 256);
          return `rgba(${r}, ${g}, ${b}, 0.7)`;
        });

        const name = Object.keys(data); // get the name
        console.log(name);
        const chartData = {
          labels: name,
          datasets: [{
            label: 'Coin Dirty',
            backgroundColor: randomColors,
            data: name.map(value => data[value]),
            borderColor: 'rgba(75, 192, 192, 1)',
            borderWidth: 1
          }
          ],


        };
        this.chartData = chartData;
      }
      catch (error) {
        console.log(error);
      }


    }
  },
  mounted() {
    // You can optionally call getData here if you want to fetch data when the component is mounted
  },
  created() {
    this.getData(); // Fetch data when the component is created
  },
}
</script>
