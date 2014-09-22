var express = require('express')
var app = express();

app.use(express.static(__dirname + '/public'));

app.get('/', function(req, res) {
  res.render('index');
});

app.get('/ajax', function(req, res) {
  var now = new Date();
  res.send('{"time": ' + now.getTime() + '}');
});

console.log('Server running at http://localhost:3000/');
app.listen(3000);
