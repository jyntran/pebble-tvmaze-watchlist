var Clay = require('pebble-clay');
var clayConfig = require('./config.json');
var clay = new Clay(clayConfig, null, {autoHandleEvents: false});
var messageKeys = require('message_keys');

var Base64 = require('./Base64');

var user = "";
var apiKey = "";

var xhrRequest = function (url, type, headerType, header, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.setRequestHeader(headerType, header);
  xhr.send();
};

function getFollowedShows() {
  // Construct URL
  var url = 'https://api.tvmaze.com/v1/user/follows/shows?embed=show';

  // Send request to TVmaze
  xhrRequest(url, 'GET',
  	"Authorization", "Basic" + Base64.encode(user + ":" + apiKey),
    function(responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);

      var showid = json[0].show_id;
      console.log('Show_id is ' + showid);

      var showname = json[0]._embedded.show.name;      
      console.log('Show name is ' + showname);

		// Assemble dictionary using our keys
		var dictionary = {
		  'SHOWID': showid,
		  'SHOWNAME': showname
		};

		// Send to Pebble
		Pebble.sendAppMessage(dictionary,
		  function(e) {
		    console.log('Show info sent to Pebble successfully!');
		  },
		  function(e) {
		    console.log('Error sending show info to Pebble!');
		  }
		);
    }      
  );

}


Pebble.addEventListener('showConfiguration', function(e) {
  Pebble.openURL(clay.generateUrl());
});

Pebble.addEventListener('webviewclosed', function(e) {
  var dict = clay.getSettings(e.response);

  apiKey = dict[messageKeys.ApiKey];
  user = dict[messageKeys.User];

  Pebble.sendAppMessage(dict, function() {
    console.log('Message sent successfully: ' + JSON.stringify(dict));
  }, function(e) {
    console.log('Message failed: ' + JSON.stringify(e));
  });
});


// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
    getFollowedShows();
  }                     
);

