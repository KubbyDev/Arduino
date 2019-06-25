const express = require('express');
const app = express();
app.listen(3200, () => console.log("listening"));
app.use(express.static('Client'));  //Le serveur envoie le fichier Client/index.html

let latest = [];

//Reception des values des capteurs
app.get('/meteo', (request, response) => {

    console.log("received values");
    response.json({
        errors: 'None'
    });

    latest = [
        request.query.sound,
        request.query.humidity,
        request.query.pressure,
        request.query.altitude,
        request.query.smoke,
        request.query.luminosity,
        request.query.temperature,
        request.query.water
    ]
});

//Envoi des valeurs au client
app.get('/getValues', (request, response) => {

    console.log("sent values");
    response.json({
        values: latest
    });
});