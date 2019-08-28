$(function(){
    //https://www.w3schools.com/js/js_cookies.asp
    function setCookie(cname, cvalue) {
        var d = new Date();
        var exdays = 7;
        d.setTime(d.getTime() + (exdays*24*60*60*1000));
        var expires = "expires="+ d.toUTCString();
        document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
      }
      function getCookie(cname) {
        var name = cname + "=";
        var decodedCookie = decodeURIComponent(document.cookie);
        var ca = decodedCookie.split(';');
        for(var i = 0; i <ca.length; i++) {
          var c = ca[i];
          while (c.charAt(0) == ' ') {
            c = c.substring(1);
          }
          if (c.indexOf(name) == 0) {
            return c.substring(name.length, c.length);
          }
        }
        return "";
      }
    console.log('linked');
    //login ajax call

    $('#form_register').click(function(){
       check_pw();
    });



    $('#form_login').submit(function (e) {
        //standard behaviour block
        e.preventDefault();

        //data terug krijgen vd form met jquery
        let loginObject = {
            email: $('#emailinput').val(),
            password: $('#passwordinput').val(),
        };

        //Call to server
        $.ajax({
            url: 'http://127.0.0.1:3000/checklogin',
            method: 'POST',
            data: loginObject

        }).done(function (data) {
            console.log('de teruggestuurde login data is ::');
        
            console.log(data);
            if (data.type == 'admin'){
                setCookie("userId", data.id);
                window.location.href = "admin.html";
                
            } else if (data.type == 'koerier'){
                setCookie("userId", data.id);
                window.location.href = "koerier.html";
                
            } else if (data.type == 'klant') {
                setCookie("userId", data.id);
                window.location.href = "klant.html";
                setCookie("userId", data.id);
            } else if (data == 'fouteLogin'){
                $('#errorMsg').css("visibility", "visible");
            }
          //  Cookies.set('login_xd', login_id);
           // Cookies.set('login_voornaam', data[0].voornaam);
            console.log('set id to cookie value werkte')


        }).fail(function (er1, er2) {
            console.log(er1);
            console.log(er2);
        });
    });

    //Register ajax call naar server
    $('#form_register').submit(function (e) {
        console.log('register triggered')
        //standard behaviour block
        e.preventDefault();

        //data terug krijgen vd form met jquery
        let registerObject = {
            email: $('#emailinput').val(),
            password: $('#passwordinput').val(),
            type: $("input[name='type']:checked").val()
        };
        console.log(registerObject);
        //Call to server
        $.ajax({
            url: 'http://127.0.0.1:3000/register',
            method: 'POST',
            data: registerObject

        }).done(function (data) {
         if (data == 'OK')
            { $('#succesMsg').html("User succesvol aangemaakt!");
            $('#succesMsg').css("color", "green");
                $('#succesMsg').css("visibility", "visible");

            }
            else { $('#succesMsg').html("Gebruiker bestaat al!");
            $('#succesMsg').css("visibility", "visible");
            $('#succesMsg').css("color", "red");
        }
          //  Cookies.set('login_xd', login_id);
           // Cookies.set('login_voornaam', data[0].voornaam);
            console.log('set id to cookie value werkte')


        }).fail(function (er1, er2) {
            console.log(er1);
            console.log(er2);
        });
    });


    //Status wijzigen en of opmerking toevoegen aan een pakket
    $(document).on("submit", '.form_Opm', function (e) {
        e.preventDefault();
        let opmerkingObject = {
            id: this.id,
            status: $('#boxStatus').val(),
            text: $('#opmerkingTxt').val()
        };
        console.log(opmerkingObject);

        //Call to server
        $.ajax({
            url: 'http://127.0.0.1:3000/insertOpmerking',
            method: 'POST',
            data: opmerkingObject

        }).done(function(data){
            console.log('opmerking en status inserted!');


        }).fail(function(er1, er2){
            console.log(er1);
            console.log(er2);
        });
    });



   


    //GET ALLE VOERTUIGEN
    $.ajax({
        url: 'http://127.0.0.1:3000/getVoertuigen',
        method: 'GET',
        dataType: 'json'
    }).done(function(data){
        console.log('DONE');
        for(let b of data){
            $('#listVoertuigen').append(`<li id="voertuig${b.id}"><strong>VoertuigId: ${b.id} - Naam: ${b.naam} - Status: ${b.status} - Capaciteit: ${b.totaalCapaciteit}m2 </strong><button type="button" class="btn btn-dark showPaketten" id="${b.id}">Toon alle paketten </button> </li><br>`);
        }
    }).fail(function(er1, er2){
        console.log(er1);
        console.log(er2);
    });

    // TOON ALLE PAKETTNE PER VOERTUIG
    $(document).on("click", '.showPaketten', function () {
        console.log(this.id);
        var str = '#voertuig'+this.id;
        $.ajax({
            url: 'http://127.0.0.1:3000/getPakettenByVoertuigId/' + this.id,
            method: 'GET',
            dataType: 'json',

        }).done(function(data){
            console.log('DONE???');
            for(let b of data){
                
                $(str).append(`
                <form id="${b.id}"; class="form_Opm"><ul>
                <li id="${b.id}"><strong>PakketId: ${b.id} - Status: ${b.status} - Opmerking: ${b.opmerking}  </strong> 
                <br>Status<br>
                <select id="boxStatus";>
                    <option value="in magazijn">In magazijn</option>
                    <option value="in verwerking">In verwerking</option>
                    <option value="onderwerg">Onderweg</option>
                    <option value="bezorgt">Bezorgt</option>
                </select>
                <br>
                Opmerking:<br>
                <input id="opmerkingTxt"; type="text" name="opmerking">
                <br><br>
                <button type="submit" class="btn btn-dark">Submit</button>
                 </li></ul></form><br>
                
                
                `);
                
            }
        }).fail(function(er1, er2){
            console.log(er1);
            console.log(er2);
        });
    })

//Retrieves list of books from database using AJAX call
$.ajax({
    url: 'http://127.0.0.1:3000/getPakettenById/' + getCookie("userId"),
    method: 'GET',
    dataType: 'json'
}).done(function(data){
    console.log('getPakettenById getriggered op by return van server');
    //clean up previous data
    $('#listOfPaketten').empty();
    for(let b of data){
        $('#listOfPaketten').append(`
        <ol>
            <strong><li id="listItem">Pakket id: ${b.id}</li></strong>
            <ul>
                <li><strong style="color:black;">Status:</strong> <strong>${b.status}</strong></li>
                <li><strong style="color:black;">Capaciteit: </strong> <strong>${b.capaciteit}m2</strong></li>
                <li><strong style="color:black;">Naam: </strong> <strong>${b.voornaam} ${b.achternaam}</strong></li>
                <li><strong style="color:black;">Adres: </strong> <strong>${b.straat} ${b.huisnummer} : ${b.gemeente}</strong></li>
            </ul>
        
        </ol>
        <hr>
        
        `);
    }
}).fail(function(er1, er2){
    console.log(er1);
    console.log(er2);
});

    
    //get alle paket adressen vd server
    $.ajax({
        url: 'http://127.0.0.1:3000/getAdressen',
        method: 'GET',
        dataType: 'json'
    }).done(function(data){
        console.log('DONE');
        for(let b of data){
            $('#alleAdressen').append(`
            <p><strong>${b.straat} - ${b.huisnummer} - ${b.gemeente}</p>
            `);
        }
    }).fail(function(er1, er2){
        console.log(er1);
        console.log(er2);
    });


    function check_pw() {
        if (passwordinput.value != passwordcontroleinput.value) {
            passwordcontroleinput.setCustomValidity("Wachtwoorden komen niet overeen");
        } else {
            passwordcontroleinput.setCustomValidity('');
        }
    }


});
