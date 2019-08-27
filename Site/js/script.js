$(function(){
    console.log('linked');
    //login ajax call

    $('#form_register').click(function(){
       check_pw();
    });

    $('#listOfPaketten').hide();
    getList();


    
    //Retrieves list of books from database using AJAX call
    function getList(){

        $.ajax({
            url: 'http://127.0.0.1:3000/getPaketten',
            method: 'GET',
            dataType: 'json'
        }).done(function(data){
            console.log('DONE');
            //clean up previous data
            $('#listOfPaketten').empty();
            for(let b of data){
                $('#listOfPaketten').append(`<strong>Titel: </strong> <br>`);
                $('#x').css("color","red")
            }
        }).fail(function(er1, er2){
            console.log(er1);
            console.log(er2);
        });
    }


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
                window.location.href = "admin.html";
            } else if (data.type == 'koerier'){
                window.location.href = "koerier.html";
            } else if (data.type == 'klant') {
                window.location.href = "klant.html/id=" + data.id;
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
         if (data == 'OK'){
                $('#succesMsg').css("visibility", "visible");
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

    //$(document).on("click", '.form_statusEnOpmerking', function () {
    //    console.log(this.id);
     //   var str = '#voertuig'+this.id;
     //   console.log(str);
   // });



   


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
                
                $(str).append(`<ul><li id="${b.id}"><strong>PakketId: ${b.id} - Status: ${b.status} - Opmerking: ${b.opmerking}  </strong> <form class="form_statusEnOpmerking">
                Status<br>
                <select>
                    <option value="mag">In magazijn</option>
                    <option value="ver">In verwerking</option>
                    <option value="mond">Onderweg</option>
                    <option value="bez">Bezorgt</option>
                </select>
                <br>
                Opmerking:<br>
                <input type="text" name="opmerking">
                <br><br>
                <button type="submit" class="btn btn-primary">Submit</button>
            </form> </li></ul><br>
                
                
                `);
            }
        }).fail(function(er1, er2){
            console.log(er1);
            console.log(er2);
        });
    })



       //Form status en opmerking ajax call naar de server
       $('.form_statusEnOpmerking').submit(function (e) {
        console.log('rwaarom triggered dit niet')
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
         if (data == 'OK'){
                $('#succesMsg').css("visibility", "visible");
            }
          //  Cookies.set('login_xd', login_id);
           // Cookies.set('login_voornaam', data[0].voornaam);
            console.log('set id to cookie value werkte')


        }).fail(function (er1, er2) {
            console.log(er1);
            console.log(er2);
        });
    });



    function check_pw() {
        if (passwordinput.value != passwordcontroleinput.value) {
            passwordcontroleinput.setCustomValidity("Wachtwoorden komen niet overeen");
        } else {
            passwordcontroleinput.setCustomValidity('');
        }
    }


});
