(function () {
    var oSize = {
        height: function () {
            var B = document.body; var H = document.documentElement; var h;
            if (typeof document.height !== 'undefined') {
                h = document.height // For webkit browsers
            } else {
                h = Math.max(B.scrollHeight, B.offsetHeight, H.clientHeight, H.scrollHeight, H.offsetHeight);
            }
            return h;
        },
        width: document.documentElement.clientWidth
    };
    var getStyle = function (e, styleName) {
        var styleValue = "";
        if (document.defaultView && document.defaultView.getComputedStyle) {
            styleValue = document.defaultView.getComputedStyle(e, "").getPropertyValue(styleName);
        } else if (e.currentStyle) {
            styleName = styleName.replace(/\-(\w)/g, function (strMatch, p1) {
                return p1.toUpperCase();
            });
            styleValue = e.currentStyle[styleName];
        }
        return styleValue;
    }
    var m = parseInt((getStyle(document.getElementsByTagName('body')[0], 'margin')), 10);

    document.body.style.margin = '0px';
    document.body.style.padding = '0px';
    document.body.style.border = '0px';
    plugin = document.createElement('object');
    plugin.id = 'vrshopplugin';
    plugin.type = 'application/x-vrshopplugin';
    plugin.width = oSize.width;
    plugin.height = oSize.height() - (m/2);
    plugin.margin = '0px';
    plugin.padding = '0px';
    plugin.border = '0px';
    document.body.appendChild(plugin);

    var result = plugin.valid;
    plugin.runApplication(console.log("Plugin: " + result));
})();