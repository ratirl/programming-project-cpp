$(function(){
    console.log('linked');
    //login ajax call
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
            console.log('login gecheckt!');
            console.log(data);
            if (data == 'admin'){
                window.location.href = "adminhomepage.html";
            } else if (data == 'koerier'){
                window.location.href = "koerierhomepage.html";
            } else if (data == 'klant') {
                window.location.href = "klanthomepage.html";
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



   $('.form_statusEnOpmerking').submit(function(e){
    //standard behaviour block
    e.preventDefault();
    console.log('inser voor opm en status geriggered');

    
});


    //GET ALLE VOERTUIGEN
    $.ajax({
        url: 'http://127.0.0.1:3000/getVoertuigen',
        method: 'GET',
        dataType: 'json'
    }).done(function(data){
        console.log('DONE');
        for(let b of data){
            $('#listVoertuigen').append(`<li id="voertuig${b.id}"><strong>VoertuigId: ${b.id} - Naam: ${b.naam} - Capaciteit: ${b.totaalCapaciteit}m2 </strong><button type="button" class="btn btn-dark showVoertuigen" id="${b.id}">Toon alle paketten </button> </li><br>`);
        }
    }).fail(function(er1, er2){
        console.log(er1);
        console.log(er2);
    });

    // TOON ALLE PAKETTNE PER VOERTUIG
    $(document).on("click", '.showVoertuigen', function () {
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
                <button type="submit" class="btn btn-primary">Suefebmit</button>
            </form> </li></ul><br>
                
                
                `);
            }
        }).fail(function(er1, er2){
            console.log(er1);
            console.log(er2);
        });
    })


});
