const appName = "robot";
const websocket = createWebsocket();

const main = async () => {
  websocket.ready.then(() => {
    console.log('ROBOT Websocket connected');

//close it just in case
// ttyUSB0 should be servos

    websocket.publish({
      topic: 'serial/command/close',
      payload: { path: '/dev/ttyUSB0' }
    });

//serial0 shoudl be lights
    websocket.publish({
      topic: 'serial/command/close',
      payload: { path: '/dev/serial0' }
    });

    websocket.publish({
      topic: `${appName}/event/ready`,
      payload: { msg: 'Internal app ready!' }
    });

// if needed
// websocket.publish({ topic: 'serial/command/list' });

    websocket.publish({
     topic: 'serial/command/open',
     payload: { path: '/dev/ttyUSB0', baudRate: 115200 }
    });

    websocket.publish({
     topic: 'serial/command/open',
     payload: { path: '/dev/serial0', baudRate: 115200 }
    });

  });



//commands
/*
1: curiosity
2: frustration
3: hesitancy
4: joy
5: anticipation

lights only:
6: cold
7: warm
0: heartbeat

6_say_please.mp3		Frustration.ogg			bad_robot.mp3			very_good_taste.mp3
Anticipation.ogg		Hesitancy.ogg			good_robot.mp3			weather_overcast.mp3
BreakingNews.mp3		Joy.ogg				hello.mp3
Curiosity.ogg			ask_nicely.mp3			since_you_asked_politely.mp3

*/


  websocket.subscribe(new RegExp(`.*`), ({ topic, payload }) => {

      console.log('ROBOT Recieved message', topic, payload);

      if (topic.includes("serial/event/open")) {

        //lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/serial0', data: '0\n' }
        });

        //voice
        var voice_file = "hello.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");

      } else if (topic.includes("bad-robot")) {

//lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/serial0', data: '3\n' }
        });

//servo
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '2\n' }
        });

//voice
        var voice_file = "bad_robot.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");

//sound
        var audio_file = "Frustration.ogg";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");

      }else if (topic.includes("good-robot")) {

//lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/serial0', data: '4\n' }
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
        var audio_file = "Joy.ogg";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");

      } else if (topic.includes("weather-overcast")) {

//servos
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '2\n' }
        });

//lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/serial0', data: '6\n' }
        });

//voice
        var voice_file = "weather_overcast.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");

//audio file
        var audio_file = "Hesitancy.ogg";
        var a = document.querySelector("#audio");
        a.setAttribute("src", "assets/" + audio_file);
        a.setAttribute("autoplay", "autoplay");

      } else if (topic.includes("bad-news")) {

//servos
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/ttyUSB0', data: '2\n' }
        });

//lights
        websocket.publish({
          topic: 'serial/command/send',
          payload: { path: '/dev/serial0', data: '6\n' }
        });

//voice
        var voice_file = "news.mp3";
        var a = document.querySelector("#voice");
        a.setAttribute("src", "assets/" + voice_file);
        a.setAttribute("autoplay", "autoplay");


//audio file
        var audio_file = "BreakingNews.mp3";
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
