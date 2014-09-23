var intervalID;

function start() {
  intervalID = window.setInterval(ajax, 1000);
}

function stop() {
  if (intervalID)
    window.clearInterval(intervalID);
}

function ajax() {
  $.ajax('/ajax', {
    type: 'GET',
    timeout: 500
  }).done(function(data, status, xhr) {
    var json = JSON.parse(data);
    var date = new Date(json.time);
    var time = date.getHours() + ':' + date.getMinutes() + ':' + date.getSeconds();
    $('div#time').html('<h1>' + time + '</h1>');
  }).fail(function(xhr, status, error) {
  }).always(function(arg1, status, arg2) {
  });
}
