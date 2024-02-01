<template>
    <div>
      <canvas id="myChart"></canvas>
    </div>
  </template>
  
  <script>
  import Chart from "chart.js/auto";
  
  export default {
    mounted() {
      const labels = this.generateMonthLabels({ count: 7 });
      const data = {
        labels: labels,
        datasets: [
          {
            label: "My First Dataset",
            data: [65, 59, 80, 81, 56, 55, 40],
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
    methods: {
      generateMonthLabels({ count }) {
        const currentDate = new Date();
        const monthFormatter = new Intl.DateTimeFormat('en', { month: 'long' });
  
        return Array.from({ length: count }, (_, i) => {
          const date = new Date(currentDate);
          date.setMonth(date.getMonth() - i);
          return monthFormatter.format(date);
        }).reverse();
      },
    },
  };
  </script>
  
  <style>
  /* Add your styles if needed */
  </style>
  