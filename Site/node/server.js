const express = require('express');
const mysql = require('mysql2');
const config = require('./config')
const path = require('path');
const app = express();
const port = 3000;

//Page to be redirecten wnr ge localhost:3000 intyped
//Basically index of homepage
app.get('/', (req, res) => {

    res.sendFile(path.join(__dirname + '/html/login.html'));

});

//Connection to database
const connection = mysql.createConnection({
    host: config.host,
    user: config.user,
    password: config.password,
    database: config.database
});

//GET get alle pakketten /soort van api
//Om alle data in json op te vangen
app.get('/getPakketten', (req, res) => {
    connection.query(
        'SELECT * FROM `L9_Pakket`',
        function(err, results, fields) {
            if(results){
                console.log(results);
                res.send(results);
            }
        }
    );
});


app.listen(port, () => console.log(
    `MY App listening on port ${port}!`));



