const express = require('express');
const app = express();
app.listen(5000, () => console.log("listening"));
app.use(express.static('LedSwitch'));  //Le serveur envoie le fichier Client/index.html
app.use(express.json({}));