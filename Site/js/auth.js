function logOut(){
    console.log("logout triggered;")
    document.cookie = "userId=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
    document.cookie = "userType=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
    document.cookie = "userEmail=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
    $(location).attr('href','index.html');
 }

$(function(){
 //in een apparte js file want index.html mag de authorize functie
 //niet oproepen anders had ik infinite loop
 var userId = getCookie("userId");
 console.log("hmmm");
 console.log(userId);

//checks voor iederpagina appart anders loopte
//het wnr het op zijn eigen pagina was

//klant pagina

 if($('body').is('#klantPage')){
    if (document.cookie.indexOf('userId=')) {
        $(location).attr('href','index.html'); }
        else if (getCookie("userType") == "koerier"){
            $(location).attr('href','koerier.html');}
            if (getCookie("userType") == "admin"){
                $(location).attr('href','admin.html');}

 }
//admin pagina
 if($('body').is('#adminPage')){
    if (document.cookie.indexOf('userId=')) {
        $(location).attr('href','index.html'); }
        else if (getCookie("userType") == "koerier"){
            $(location).attr('href','koerier.html');}
            if (getCookie("userType") == "klant"){
                $(location).attr('href','klant.html');}

 }

 //koerierpagna
 if($('body').is('#koerierPage')){
    if (document.cookie.indexOf('userId=')) {
        $(location).attr('href','index.html'); }
        else if (getCookie("userType") == "klant"){
            $(location).attr('href','klant.html');}
            if (getCookie("userType") == "admin"){
                $(location).attr('href','admin.html');}

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

});
