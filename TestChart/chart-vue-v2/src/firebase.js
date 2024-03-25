import { initializeApp } from "firebase/app";
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
    export default firebaseApp;