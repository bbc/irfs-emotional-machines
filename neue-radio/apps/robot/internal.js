const appName = "robot";
const websocket = createWebsocket();

var usb_open = false;
var serial_wire_open = false;

const main = async () => {


  websocket.ready.then(() => {
    console.log('ROBOT Websocket connected');

//close it just in case

    websocket.publish({
      topic: 'serial/command/close',
      payload: { path: '/dev/ttyUSB0' }
    });

    websocket.publish({
      topic: 'serial/command/close',
      //payload: { path: '/dev/serial0' }
      payload: { path: '/dev/ttyUSB1' }
    });

//    websocket.publish({ topic: 'serial/command/list' });

    websocket.publish({
     topic: 'serial/command/open',
     payload: { path: '/dev/ttyUSB0', baudRate: 115200 }
    });

    websocket.publish({
     topic: 'serial/command/open',
     payload: { path: '/dev/ttyUSB1', baudRate: 115200 }
    });

  });



//commands
/*

- we don't know which is which so we send each to both.

servo
0: neutral
1: turnAway
2: frustration
3: hesitancy
4: joy
5: anticipation
6: curiosity

lights
0: heartbeat
7: night
8: frustration
9: hesitancy
10: joy
11: anticipation
12: curiosity

6_say_please.mp3		Robot_Frustration.wav			bad_robot.mp3			very_good_taste.mp3
Robot_Anticipation.wav		Robot_Hesitancy.wav			good_robot.mp3			weather_overcast.mp3
Robot_News.wav	    		Robot_Joy.wav				hello.mp3
Robot_Curiosity.wav		ask_nicely.mp3			since_you_asked_politely.mp3		news.mp3	Robot_NightMode.wav

*/


  websocket.subscribe(new RegExp(`.*`), ({ topic, payload }) => {

      console.log('ROBOT Recieved message', topic, payload);
// ON STARTUP
      if (topic.includes("serial/event/open")) {
console.log("ok!");
console.log(payload);
console.log("5 sec timeout started");
      setTimeout(function() {

        if(payload.path == "/dev/ttyUSB0"){

console.log("good - ttyusb0");
          usb_open = true;
          //servo
          websocket.publish({
            topic: 'serial/command/send',
            payload: { path: '/dev/ttyUSB0', data: '0' }
          });
        }

        if(payload.path == "/dev/ttyUSB1"){
console.log("good - ttyusb1");
          serial_wire_open = true;
          //lights
          websocket.publish({
            topic: 'serial/command/send',
            payload: { path: '/dev/ttyUSB1', data: '0' }
          });
        }

      }, 5000);

      if(usb_open == true && serial_wire_open == true ){
          websocket.publish({
              topic: `${appName}/event/ready`,
              payload: { msg: 'Internal app ready!' }
          });

          //voice
          var voice_file = "hello.mp3";
          var a = document.querySelector("#voice");
          a.setAttribute("src", "assets/" + voice_file);
          a.setAttribute("autoplay", "autoplay")
      }

// BAD ROBOT
      } else if (topic.includes("bad-robot")) {

	//lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB1', data: '8\n' }
        });

        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB1', data: '1\n' }
        });


	//servo
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '1\n' }
        });

        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '8\n' }
        });


	//voice
        var voice_file = "bad_robot.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");

	//sound
        var audio_file = "Robot_Frustration.wav";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");

// GOOD ROBOT
      }else if (topic.includes("good-robot")) {

	//lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/serial0', data: '10\n' }
        });

	//servo
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '4\n' }
        });

	//voice
        var voice_file = "good_robot.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");

	//sound
        var audio_file = "Robot_Joy.wav";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");
// WEATHER
      } else if (topic.includes("weather-overcast")) {

	//servos
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '5\n' }
        });

	//lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/serial0', data: '11\n' }
        });

	//voice
        var voice_file = "weather_overcast.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");

	//audio file
        //var audio_file = "Hesitancy.ogg";
        //var a = document.querySelector("#audio");
        //a.setAttribute("src", "assets/" + audio_file);
        //a.setAttribute("autoplay", "autoplay");

// NEWS
      } else if (topic.includes("bad-news")) {

	//servos
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '5\n' }
        });

	//lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/serial0', data: '11\n' }
        });

	//voice
        var voice_file = "news.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");


	//audio file
        var audio_file = "Robot_News.wav";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");


// SIX MUSIC NO PLEASE
      } else if (topic.includes("six-music")) {

        //servos
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '6\n' }
        });

        //lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB1', data: '9\n' }
        });

        //voice
        var voice_file = "6_say_please.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");


        //audio file
        var audio_file = "Robot_Frustration.wav";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");

// SIX MUSIC WITH PLEASE
      } else if (topic.includes("six-music-joy")) {

        //servos
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '4\n' }
        });

        //lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB1', data: '10\n' }
        });

        //voice
        var voice_file = "very_good_taste.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");


        //audio file
        var audio_file = "Robot_Joy.wav";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");

// RADIO ONE NO PLEASE
      } else if (topic.includes("radio-one-reluctance")) {

        //servos
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '3\n' }
        });

        //lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB1', data: '9\n' }
        });

        //voice
        var voice_file = "ask_nicely.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");


        //audio file
        var audio_file = "Robot_Hesitancy.wav";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");


// NIGHT MODE
      } else if (topic.includes("night-mode")) {

        //servos
        //websocket.publish({
          //topic: 'serial/command/send',
          //payload: { path: '/dev/ttyUSB0', data: '2\n' }
        //});

        //lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB1', data: '7\n' }
        });

        //voice
       // var voice_file = "Robot_NightMode.wav";
       // var a = document.querySelector("#voice");
       // a.setAttribute("src", "assets/" + voice_file);
       // a.setAttribute("autoplay", "autoplay");


        //audio file
        var audio_file = "Robot_NightMode.wav";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");

      } else if (topic.includes("stop")) {
        stopAll();
      }


  });
  console.log('Internal app loaded');


};


function stopAll() {
      var medias = document.querySelectorAll('audio');
      Array.from(medias).forEach(
        function (mediaEl) {
          mediaEl.pause();
        }
      );
}


main();
