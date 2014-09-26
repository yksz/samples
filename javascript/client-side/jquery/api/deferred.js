function async(delay, error) {
  var deferred = new $.Deferred();
  setTimeout(function() {
    console.log('async: delay=' + delay);
    if (error) {
      deferred.reject();
    } else {
      deferred.resolve();
    }
  }, delay * 1000);
  return deferred.promise();
}

async(1).done(function() {
  console.log('done');
}).fail(function() {
  console.log('fail');
}).always(function() {
});

async(2, true).done(function() {
  console.log('done');
}).fail(function() {
  console.log('fail');
}).always(function() {
});

$.when(async(3), async(4), async(5))
.then(function() {
  console.log('complete');
});
