const express = require("express");
var app = express();

app.get('/', (req, res) => {
    res.send('./index.html');
});

app.listen(3000, function() {
    console.log(`App listening at port 3000`);
});