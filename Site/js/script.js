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
                window.location.href = "admin.html";
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

});
