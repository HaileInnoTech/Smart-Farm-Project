<script setup>
import wd from "./components/wd.vue";
</script>

<template>
  <!-- <div>
  <HelloWorld/>

</div> -->
  <!-- <div style="width: 550px">
    <Bar_chartjs />
  </div> -->

  <!-- <div style="width: 550px">
    <test />
  </div> -->
  <div>
    <wd />
  </div>
</template>
<script>
export default {
  name: "App",
  components: {
    wd,
  },
};
</script>
