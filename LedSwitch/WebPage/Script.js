var broches = []; // Tableau de broches
var etats = []; // Tableau d'etat des broches
var pwm;
var a0;
var millis;
var adresse = "http://192.168.0.136:4200/"; // L'url+port de votre shield

document.addEventListener('DOMContentLoaded', setup, false);

function setup() {
    // fonction qui va lier les variables à leur conteneur HTML
    broches[3] = document.getElementById("broche3");
    broches[4] = document.getElementById("broche4");
    broches[5] = document.getElementById("broche5");
    etats[3] = document.getElementById("etat3");
    etats[4] = document.getElementById("etat4");
    etats[5] = document.getElementById("etat5");
    pwm = document.getElementById("pwm");
    a0 = document.getElementById("a0");
    millis = document.getElementById("millis");

    // La fonction concernant le bouton
    var bouton = document.getElementById("envoyer");
    bouton.addEventListener('click', executer, false);
}

function executer() {
    // Fonction qui va créer l'url avec les paramètres puis
    // envoyer la requête
    var requete = new XMLHttpRequest(); // créer un objet de requête
    var url = adresse;
    url += "?b=";
    for( i=3; i <= 5; i++) { // Pour les broches 3 à 5 de notre tableau
        if(broches[i].checked) // si la case est cochée
            url += i + ",";
    }
    // enlève la dernière virgule si elle existe
    if(url[url.length-1] === ',')
        url = url.substring(0, url.length-1);
    // Puis on ajoute la pwm
    url += "&p=" + pwm.value;
    console.log(url); // Pour debugguer l'url formée
    requete.open("GET", url, true); // On construit la requête
    requete.send(null); // On envoie !
    requete.onreadystatechange = function() { // on attend le retour
        if (requete.readyState === 4) { // Revenu !
            if (requete.status === 200) {// Retour s'est bien passé !
                // fonction d'affichage (ci-dessous)
                afficher(requete.responseText);
            } else { // Retour s'est mal passé :(
                alert(requete.status, requete.statusText);
            }
        }
    };
}

function afficher(json) {
    // Affiche l'état des broches/pwm/millis revenu en json
    donnees = JSON.parse(json);
    console.log(donnees);

    for(i=3; i <= 5; i++) { // Pour les broches 3 à 5 de notre tableau
        etats[i].checked = donnees["broches"][i];
    }
    pwm.value = parseInt(donnees["pwm"]);
    a0.value = parseInt(donnees["A0"]);
    millis.textContent = donnees["uptime"];
}