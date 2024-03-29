# Arduino Client for MQTT

This library provides a client for doing simple publish/subscribe messaging with
a server that supports MQTT.

## Examples

The library comes with a number of example sketches. See File > Examples > PubSubClient
within the Arduino application.

Full API documentation is available here: http://pubsubclient.knolleary.net

## Limitations

 - It can subscribe at QoS 0 or 1.
 - It can publish at QoS 0, 1 or 2. WARNING! No retransmission is supported to
   keep the library as much memory friendly as possible. (Without retransmission
   support, the publish QoS is only meaningful when the broker sends your
   message to a subscriber, supposing that the subscriber subscribes with a QoS
   greater then or equal to the publish QoS; consider that MQTT runs over TCP,
   so retransmission isn't really required in most cases, especially when
   publishing to the broker)
 - The maximum message size, including header, is **128 bytes** by default. This
   is configurable via `MQTT_MAX_PACKET_SIZE` in `PubSubClient.h`.
 - The keepalive interval is set to 15 seconds by default. This is configurable
   via `MQTT_KEEPALIVE` in `PubSubClient.h`.
 - The client uses MQTT 3.1.1 by default. It can be changed to use MQTT 3.1 by
   changing value of `MQTT_VERSION` in `PubSubClient.h`.


## Compatible Hardware

The library uses the Arduino Ethernet Client api for interacting with the
underlying network hardware. This means it Just Works with a growing number of
boards and shields, including:

 - Arduino Ethernet
 - Arduino Ethernet Shield
 - Arduino YUN – use the included `YunClient` in place of `EthernetClient`, and
   be sure to do a `Bridge.begin()` first
 - Arduino WiFi Shield - if you want to send packets > 90 bytes with this shield,
   enable the `MQTT_MAX_TRANSFER_SIZE` define in `PubSubClient.h`.
 - Sparkfun WiFly Shield – [library](https://github.com/dpslwk/WiFly)
 - TI CC3000 WiFi - [library](https://github.com/sparkfun/SFE_CC3000_Library)
 - Intel Galileo/Edison
 - ESP8266

The library cannot currently be used with hardware based on the ENC28J60 chip –
such as the Nanode or the Nuelectronics Ethernet Shield. For those, there is an
[alternative library](https://github.com/njh/NanodeMQTT) available.

## License

This code is released under the MIT License.
