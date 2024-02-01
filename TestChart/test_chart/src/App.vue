<template>
  <div>
    <h1>Welcome to My Vue App</h1>
    <apexchart
      type="line"
      height="350"
      :options="chartOptions"
      :series="series"
    ></apexchart>
  </div>
</template>

<script>
export default {
  data() {
    return {
      chartOptions: {
        chart: {
          type: 'line',
        },
        series: [
          {
            name: 'sales',
            data: [30, 40, 35, 50, 49, 60, 70, 91, 125],
          },
        ],
        xaxis: {
          categories: [1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999],
        },
      },
    };
  },
};
</script>

<style>
h1 {
  color: blue;
}
</style>