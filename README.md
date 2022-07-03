# scull-iot

IoT Scull

Program for control IoT Scull (my home decorate).

Implement REST API for control LED eyes.

Development for board ESP32.

## Getting status eyes of Scull

* Request:

``` http
GET http://host/eye
```

* Response:

``` json
{
    "left": "off",
    "right": "on"
}
```

## Setting eyes of Scull

* Request:

``` http
POST http://host/eye
Content-Type: application/json

{
    "left": "on",
    "right": "on"
}
```

* Response:

``` json
{
    "left": "on",
    "right": "on"
}
```
