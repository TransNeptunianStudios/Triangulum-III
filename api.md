# Client-Server Communication API
Documents the json msgs being used for communication between the server and clients.

#### Client Login Request
Sent one time when login in.
```sh
{"type" : "login", "name" : <USERNAME>, "color" : <HEX-COLOR>}
```

#### Server Login Response
Response from login attempt, status can be "success" or "failure", id is a handle to the player object.
```sh
{"type" : "login_resp", "status" : <SUCCESS/FAILURE>, "id" : <PLAYER-ID>}
```

#### Client Input Msg
Send boolean input to the server as an 8 bit inputmask,
Order: {thurst, reverse, strafe Left, strafe right, turn left, turn right, fire weapon, not used}. example when thrusting and firing: 10000010 binary = 130 decimal. Sending 130.
```sh
{"type" : "control", "input_mask" : <INPUT MASK>}
```

#### Server Update Msg
Send list of all relevant objects current state.
```sh
{"type" : "update",
 "objects" : [{"id": <ID>, "sprite" : "<SPRITE>, "color" : <HEX-COLOR> , "x": <X-POS>, "y": <Y-POS>, 
"vx": <X-VELOCITY>, "vy": <Y-VELOCITY>, "r":<ROTATION>, "vr" : <ROTATION VELOCITY},
               {"id": <PLAYER-ID>, color : <HEX-COLOR> , "x": <X-POS>, "y": <Y-POS>, 
"vx": <X-VELOCITY>, "vy": <Y-VELOCITY>, "r":<ROTATION>, "vr" : <ROTATION VELOCITY, "score" : <SCORE}}],
               }
```
