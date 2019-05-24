const appName = "voice";
const websocket = createWebsocket();
const rasa = new Rasa();

const main = async () => {
  websocket.ready.then(() => {
    console.log('Websocket connected');

    websocket.publish({
      topic: `${appName}/event/ready`,
      payload: { msg: 'Internal app ready!' }
    });
  });

  websocket.subscribe(new RegExp(`${appName}/.*`), ({ topic, payload }) => {
    console.log('Recieved message', topic, payload);

    if (topic.includes("recognition")) {
      const type = payload.params.type;
      const transcript = payload.params.transcript;

      if (type === 'full') {
        rasa.getIntent(transcript, 'emotional_robots').then((intent) => {
          console.log('got intent', intent);
          if (intent === 'bad_robot') {
            try{
              websocket.publish({ topic: `robot/command/bad-robot` });
            }catch(f){
              console.log(f);
            }

          } else if (intent == 'good_robot'){
            websocket.publish({ topic: `robot/command/good-robot` });

          } else if (intent == 'weather_today'){
            websocket.publish({ topic: `robot/command/weather-overcast` });

          } else if (intent == 'radio_six_music'){
           // websocket.publish({ topic: `speech/command/speak`, payload: { utterance: 'i will play bbc radio six music when you learn to say please' } });
            websocket.publish({ topic: `robot/command/six-music` });

          } else if (intent == 'radio_six_music_please'){
           // websocket.publish({ topic: `speech/command/speak`, payload: { utterance: 'my pleasure. you have very good taste' } });
            websocket.publish({ topic: `robot/command/six-music-joy` });

          } else if (intent == 'radio_one'){
           // websocket.publish({ topic: `speech/command/speak`, payload: { utterance: 'if you must listen to that you could at least ask nicely' } });
            websocket.publish({ topic: `robot/command/radio-one-reluctance` });


          } else if (intent == 'breaking_news'){
          websocket.publish({ topic: `robot/command/good-news` });

          } else if (intent == 'news_today'){
            websocket.publish({ topic: `robot/command/bad-news` });

          } else if (intent == 'night_mode'){
            websocket.publish({ topic: `robot/command/night-mode` });
          }

        }).catch((e) => {
          console.log('intent not found');
          console.log(e);
        });
      }
    }else{
       console.log("ARGH");
    }
  });

  console.log('Internal app loaded');
};

main();
