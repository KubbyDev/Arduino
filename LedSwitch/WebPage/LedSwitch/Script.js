let ledPin = [];

ledPin = document.getElementById("broche3");
document.getElementById("envoyer").addEventListener('click', send, false);

function send() {

    let request = new XMLHttpRequest();
    let url = "http://" + document.getElementById("ip").value + ":" + document.getElementById("port").value + "/";
    url += "?b=";

    if(ledPin.checked)
        url += "3,";

    // enleve la derniere virgule si elle existe
    if(url[url.length-1] === ',')
        url = url.substring(0, url.length-1);

    console.log(url);

    request.open("GET", url, true);
    request.send(null);
}