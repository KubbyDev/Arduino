
setInterval(async () => {
    const rawResponse = await fetch('/getValues');
    const response = await rawResponse.json();
    updateValues(response.values);
}, 2000);

function updateValues(values) {

    document.getElementById("sound").innerHTML = values[0];
    document.getElementById("humidity").innerHTML = values[1];
    document.getElementById("pressure").innerHTML = values[2];
    document.getElementById("altitude").innerHTML = values[3];
    document.getElementById("smoke").innerHTML = values[4];
    document.getElementById("luminosity").innerHTML = values[5];
    document.getElementById("temperature").innerHTML = values[6];
    document.getElementById("water").innerHTML = values[7];
}