var plugin = function plugin0() {
    return document.getElementById('plugin0');
}
//plugin = plugin0;

function addEvent(obj, name, func) {
    if (obj.attachEvent) {
        obj.attachEvent("on" + name, func);
    } else {
        obj.addEventListener(name, func, false);
    }
}

function load() {
    addEvent(plugin(), 'test', function () {
        alert("Received a test event from the plugin.")
    });
}
function pluginLoaded() {
    alert("Plugin loaded!");
}

function addTestEvent() {
    addEvent(plugin(), 'echo', function (txt, count) {
        alert(txt + count);
    });
}

function testEvent() {
    plugin().testEvent();
}

function pluginValid() {
    if (plugin().valid) {
        alert(plugin().echo("This plugin seems to be working!"));
    } else {
        alert("Plugin is not working :(");
    }
}

function printToFile() {
    plugin().printToFile();
}

