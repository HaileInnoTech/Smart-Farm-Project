const express = require('express');
const cors = require("cors");
const functions = require('firebase-functions');
var admin = require("firebase-admin");
var serviceAccount = require("./key.json");
admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://smart-farming-system-f9435-default-rtdb.asia-southeast1.firebasedatabase.app"
});

const app = express();
app.use(cors({ origin: true }));

const database = admin.database();
app.get("/data", (req, res) => {
    const dataRef = database.ref("/Temp-Humid");
    dataRef.on("value", (snapshot) => {
      const data = snapshot.val();
      res.status(200).json(data);
    });
  });
  
exports.app = functions.https.onRequest(app);