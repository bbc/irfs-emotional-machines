### Neue Radio Voice

This version sends a specific set of commands to the robot app.

Instalation notes in ths repo.


## Train

```curl -XPOST -H "Content-Type: application/x-yml" localhost:5005/train?project=emotional_robots --data-binary @src/assets/model.yml```

[assets/model.yml](src/assets/model.yml)

Returns JSON

```
{
    "info": "new model trained",
    "model": "model_20190508-203057"
}
```

## Query

```curl -XPOST localhost:5005/parse -d '{"q":"good robot", "project":"emotional_robots"}'```

Returns JSON

```
{
  "text": "good robot",
  "intent": {
    "name": "good_robot",
    "confidence": 0.9407419562339783
  },
  "project": "emotional_robots",
  "intent_ranking": [
    {
      "name": "good_robot",
      "confidence": 0.9407419562339783
    },
    {
      "name": "bad_robot",
      "confidence": 0.10839154571294785
    },
    {
      "name": "radio_six_music",
      "confidence": 0.05585484951734543
    },
    {
      "name": "radio_one",
      "confidence": 0.05322892963886261
    },
    {
      "name": "weather_today",
      "confidence": 0.019510649144649506
    },
    {
      "name": "news_today",
      "confidence": 0.000510193407535553
    },
    {
      "name": "radio_six_music_please",
      "confidence": 0.0
    },
    {
      "name": "radio_one_please",
      "confidence": 0.0
    },
    {
      "name": "beeb",
      "confidence": 0.0
    }
  ],
  "model": "model_20190522-121300",
  "entities": []
```

## Postman

Other useful API calls can be found [here](https://documenter.getpostman.com/view/924347/RWgozeGu)
