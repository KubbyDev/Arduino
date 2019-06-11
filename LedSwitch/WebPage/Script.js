let ledPin = [];
let adresse = "http://" + document.getElementById("ip").value + ":" + document.getElementById("port").value + "/";

document.addEventListener('DOMContentLoaded', setup, false);

function setup() {

    // fonction qui va lier les variables à leur conteneur HTML
    ledPin = document.getElementById("broche3");

    // La fonction concernant le bouton
    let bouton = document.getElementById("envoyer");
    bouton.addEventListener('click', executer, false);
}

function executer() {

    // Fonction qui va créer l'url avec les paramètres puis
    // envoyer la requête
    let requete = new XMLHttpRequest(); // créer un objet de requête
    let url = adresse;
    url += "?b=";

    if(ledPin.checked)
        url += "3,";

    // enlève la dernière virgule si elle existe
    if(url[url.length-1] === ',')
        url = url.substring(0, url.length-1);

    console.log(url); // Pour debugguer l'url formée

    requete.open("GET", url, true); // On construit la requête
    requete.send(null); // On envoie !
}