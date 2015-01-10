(function () {
    document.body.style.margin = '0px';
    plugin = document.createElement('object');
    plugin.id = 'vrshopplugin';
    plugin.type = 'application/x-vrshopplugin';
    var w = window.innerWidth; var h = window.innerHeight;
    plugin.width = w;
    plugin.height = h;
    //                plugin.style.visibility = "hidden";
    //                plugin.style.display = "inline";
    //                plugin.style.float = "right";
    document.body.appendChild(plugin);

    var result = plugin.valid;
    plugin.runApplication(console.log("Plugin: " + result));
})();