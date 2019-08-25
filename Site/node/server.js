const express = require('express');
const mysql = require('mysql2');
const config = require('./config')
const path = require('path');
const bcrypt = require('bcrypt');
const bodyParser = require('body-parser');
var session = require('express-session');
const router = express.Router();
const app = express();
const port = 3000;
const saltRounds = 10;
//Session initialiseren met een secret denk ik
app.use(session({
    secret: 'keyboard cat',
    resave: false,
    saveUninitialized: true,
    cookie: { secure: true }
  }))

  var sess;
//Page to be redirecten wnr ge localhost:3000 intyped
//Basically index of homepage
app.get('/', (req, res) => {

    res.sendFile(path.join(__dirname + '/html/help.html'));
    sess=req.session;
    /*
    * Here we have assign the 'session' to 'sess'.
    * Now we can create any number of session variable we want.
    * in PHP we do as $_SESSION['var name'].
    * Here we do like this.
    */
    sess.id; // equivalent to $_SESSION['email'] in PHP.
    sess.type; // equivalent to $_SESSION['username'] in PHP.

});




router.get('/xd',(req,res) => {
    sess = req.session;
    if(sess.id) {
        return res.redirect('/admin');
    }
    res.sendFile('index.html');
});

//Middleware
app.use(function (req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
});

//Bodyparser
app.use(bodyParser.urlencoded({
    extended: false
}));

app.use(bodyParser.json());

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

//POST KLANT REGISTREREN
 app.post('/registerKlant', (req, res) => {
    console.log('register triggered!');
    console.log(req.body);

    bcrypt.hash("admin", saltRounds, function (err, hash) {
        connection.query(
            'INSERT INTO `L9_Login` (email, password, type) VALUES (?, ?, ?)',
            [req.body.email, hash, "klant"],
            function (err, results) {
                console.log(results);
                console.log(err);
            }
        );
    });

    res.send('OK');
}); 

//POST KOERIER REGISTREREN
app.post('/registerKlant', (req, res) => {
    console.log('register triggered!');
    console.log(req.body);

    bcrypt.hash("admin", saltRounds, function (err, hash) {
        connection.query(
            'INSERT INTO `L9_Login` (email, password, type) VALUES (?, ?, ?)',
            [req.body.email, hash, "koerier"],
            function (err, results) {
                console.log(results);
                console.log(err);
            }
        );
    });

    res.send('OK');
}); 



//POST login checken en doorsturen indien true
app.post('/checklogin', (req, res) => {
    console.log('login check triggered!');



    connection.query(
        'SELECT `email`, `password`, `type` FROM `L9_Login` WHERE `email` = ?', [req.body.email],
        function (err, results, fields) {
            if (results.length > 0) { 
            bcrypt.compare(req.body.password, results[0].password, function (err, ress) {
                if (ress) {
                    console.log("juiste password");
                    //als we resultaat hebben dan sturen we de type terug om op basis daarvan
                    // naar de juiste inlog pagina te redirecten
                    res.send(results[0].type);
                } else {
                    console.log("verkeerde password");
                    res.send("fouteLogin");
                }
            });
        };
        } 
    );
});


app.listen(port, () => console.log(
    `MY App listening on port ${port}!`));



