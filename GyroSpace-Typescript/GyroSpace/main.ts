//Inside scripts/main.js
require(["Gyrospace.js"], function (someModule) {
    var greeter = new someModule();
    greeter.Run();

});

require.config({
    baseUrl: "/",
    paths: {
        "some": "Gyrospace"
    },
    waitSeconds: 15,
    //locale: "fr-fr"
});

