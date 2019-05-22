const appName = "robot";
const websocket = createWebsocket();

const main = async () => {
  websocket.ready.then(() => {
    console.log('Websocket connected');

    websocket.publish({
      topic: `${appName}/event/ready`,
      payload: { msg: 'External app ready!' }
    });
  });

  // show all messages - for debugging
  websocket.subscribe(new RegExp(`.*`), ({ topic, payload }) => {
    console.log('Recieved message', topic, payload);
  });

  console.log('External app loaded');
};

main();
