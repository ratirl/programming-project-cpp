const express = require('express');
const mysql = require('mysql2');
const config = require('./config')
const path = require('path');
const bodyParser = require('body-parser');
const session = require('express-session');
const app = express();
const bcrypt = require('bcrypt');
const port = 3000;
const saltRounds = 10;
const googleMapsClient = require('@google/maps').createClient({
    key: 'AIzaSyCVU3VPTDXfpx_zHGoB5ol6m92PzTW7gFQ'
  });
//Connection to database
const connection = mysql.createConnection({
    host: config.host,
    user: config.user,
    password: config.password,
    database: config.database
});
//Middleware
  app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
});
//Bodyparser
app.use(bodyParser.urlencoded({
    extended: false
}));
app.use(bodyParser.json());

//Session initialiseren met een secret denk ik
app.use(session({
    secret: 'keyboardcat',
    resave: true,
    saveUninitialized: true,
    cookie: { secure: false }
  }))











//Page to be redirecten wnr ge localhost:3000 intyped
//Basically index of homepage
app.get('/', (req, res) => {
    console.log(session.id);
    console.log('checken of er al iemand is ingelogd in de session');
    if (req.session.useremail){
        console.log('SESSION CHECK TRIGGERED HAHAHAHAHAH!');
        console.log(req.session.useremail);
        res.redirect('logged');
    }
    

    res.sendFile(path.join(__dirname + '/html/help.html'));
    
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


//GET get alle voertuigen met bijhorende
//pakketten
app.get('/getVoertuigen', (req, res) => {
    connection.query(
        'SELECT * FROM `L9_Voertuig`',
        function(err, results, fields) {
            if(results){
               // console.log(results);
                res.send(results);
            }
        }
    );
});

//GET alle adressen vd paketten
//
app.get('/getAdressen', (req, res) => {
    connection.query(
        'SELECT `straat`,`huisnummer`, `gemeente` FROM `L9_Pakket` ',
        function(err, results, fields) {
            if(results){
                console.log(results);
                res.send(results);
            }
        }
    );
});

//GET get alle voertuigen met bijhorende
//pakketten
app.get('/getPakettenByVoertuigId/:idd', (req, res) => {
    const idVanUrl = req.params.idd;
    console.log(idVanUrl);
    console.log('manon')
    connection.query(
        'SELECT * FROM `L9_Pakket` WHERE `voertuigId` = ?', [idVanUrl],
        function(err, results, fields) {
            if(results){
                console.log(results);
                res.send(results);
            }
        }
    );
  
});


//POST KLANT OF KOERIER REGISTREREN
 app.post('/register', (req, res) => {
    console.log('register triggered!');
    console.log(req.body);
    //kijken of de email al in gebruik is of niet

    connection.query(
        'SELECT `*` FROM `L9_Login` WHERE `email` = ?', [req.body.email],
        function(err, results, fields) {
            if(results.length){
                console.log("wtf bestaat die al????");
                console.log(results);
                res.send("bestaatAl");
            }
            else   bcrypt.hash(req.body.password, saltRounds, function (err, hash) {
                connection.query(
                    'INSERT INTO `L9_Login` (email, password, type) VALUES (?, ?, ?)',
                    [req.body.email, hash, req.body.type],
                    function (err, results) {
                        console.log(results);
                        console.log(err);
                        //no problemos xp
                        res.send("OK");
                    }
                );
            });
        }
    );

}); 

//POST login checken en doorsturen indien true
app.post('/checklogin', (req, res) => {
    console.log('login check triggered!');

  
    connection.query(
        'SELECT `id`,`email`, `password`, `type` FROM `L9_Login` WHERE `email` = ?', [req.body.email],
        function (err, results, fields) {
            if (results.length > 0) { 
            bcrypt.compare(req.body.password, results[0].password, function (err, ress) {
                if (ress) {
                    console.log("juiste password");
                    //als we resultaat hebben dan sturen we de type terug om op basis daarvan
                    // naar de juiste inlog pagina te redirecten
                    req.session.userid = results[0].id;
                    req.session.useremail = results[0].email;
                    req.session.type = results[0].type;
                    console.log(req.session.userid);
                    console.log(req.session.type);
                    console.log(req.session.useremail);
                    let loginData = {
                        id: results[0].id,
                        type: results[0].type,
                        email: results[0].email,
                    };

                    res.send(loginData);
                } else {
                    console.log("verkeerde password");
                    res.send("fouteLogin");
                }
            });
        };
        } 
    );
});

//GET getPaketten
app.get('/getPaketten', (req, res) => {
    console.log('im treiggerd');
    const idd = req.params.idd;
    connection.query(
        'SELECT * FROM `L9_Pakket` WHERE `userId` = ?', [idd],
        function(err, results, fields) {
            if(results){
                 console.log(results);
                res.send(results);
            }
        }
    );
});

//GET paketten by id vd klant
app.get('/getPakettenById/:idd', (req, res) => {
    console.log("getPakettenById getriggered");
    const xd = req.params.idd;
    connection.query(
        'SELECT * FROM `L9_Pakket` WHERE `userId` = ?', [xd],
        function(err, results, fields) {
            if(results){
                console.log(results);
                res.send(results);
            }
        }
    );
  
});

//POST insertOpmerking
app.post('/insertOpmerking', (req, res) => {
    console.log('insert triggered!');
    console.log(req.body);

    connection.query(
        'UPDATE L9_Pakket SET status = ? ,opmerking = ? WHERE `id` = ?',
        [req.body.status, req.body.text, req.body.id],
        function(err, results){
            console.log(results);
            console.log(err);
        }
    );
    res.send('OK');

});

googleMapsClient.geocode({
    address: '1600 Amphitheatre Parkway, Mountain View, CA'
  }, function(err, response) {
    if (!err) {
      console.log(response.json.results);
    }
  });



app.listen(port, () => console.log(
    `MY App listening on port ${port}!`));



