var simpleIni = require("./");

console.log(simpleIni.open("src/miniini-0.9/test/test.ini"));
console.log(simpleIni.read("a", "b", "c"));
console.log(simpleIni.read("a", "b", "d"));
console.log(simpleIni.read("SETTINGS", "sections"));
console.log(simpleIni.read("vals", "float"));
