function start() {
  ajax();
}

function ajax() {
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (xhr.readyState == 4) {
      if (xhr.status == 200) {
        var response = document.getElementById('response');
        response.innerHTML = '<h1>' + xhr.responseText + '</h1>';
      }
    }
  };
  xhr.open('GET', '/ajax', true);
  xhr.send(null);
}
