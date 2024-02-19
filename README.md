# EthernetDisplay
Communication system with Granpa that not wanto to use Smartphone!
You can send message from smartphone that he can receive on the display and then when he reply with a push button you can receive a push notification with preconfigured from 9 reply possible.

[![Demo and Implementation](https://img.youtube.com/vi/JNbMhhQWgLE/0.jpg)](https://www.youtube.com/watch?v=JNbMhhQWgLE)

Here is the schematic:
![schematic](https://github.com/studiociodo/EthernetDisplay/assets/150088592/4cc76312-eb57-44a3-a78f-957f05f240ba)

You need to register with a public mqtt service, like [Mqtt.one](https://mqtt.one/signup.html).
For sending message you can use [IoT MQTT Panel](https://play.google.com/store/apps/details?id=snr.lab.iotmqttpanel.prod&pcampaignid=web_share).
After you enter a profile for your account on your dashboard create an Edit Panel like this:
![write setting](https://github.com/studiociodo/EthernetDisplay/assets/150088592/74c17905-9abe-4ece-882a-8fb2b0be2f58)
For receiving notification you can use or the same in app (on Pro version) or free app [MQTT Push Client](https://play.google.com/store/apps/details?id=de.radioshuttle.mqttpushclient&pcampaignid=web_share).
After you install it you can set your server address with relativly account:
![setting notification](https://github.com/studiociodo/EthernetDisplay/assets/150088592/9ee38a1b-edd2-434a-877b-5a599dc968f9)
and set activate topic to receive notifications:
![setting notification 2](https://github.com/studiociodo/EthernetDisplay/assets/150088592/1b23ef97-f528-4bc8-a2a5-8f3532c7fa1d)
