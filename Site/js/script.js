$(function(){
    console.log('linked');
    //default setup
    $('form').hide();
    $('#listOfBooks').show();


    //Eventlisteners voor buttons
    $('#list').click(function(){
        $('form').hide();
        $('#listOfBooks').show();
    });
    $('#form').click(function(){
        $('form').show();
        $('#listOfBooks').hide();
    });




});
