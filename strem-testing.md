# Stream Testing

## Prerequisite

Following test cases assume users, ['a', 'b', 'c'], have been registered.

Please start `backend_server` and `service_layer_server` before perform
following tets.

Client inputs are covered by `service_layer_client_tests`

```bash
# all operattions are assumed to be performed in 499_anirkkau/src/chirp/cpp folder
# start store server
./backend_store_server
# start service layer server
./service_layer_server
# execute tests for `stream`
./service_layer_client_tests
```

## Test Cases

### Case 1: Single User, Single Sender, No matching chirp

```
# for user a
./command_line --user a --stream "#a"
# for user b
./command_line --user b --chirp "test"
```

a should not print any chirps

### Case 2: Single User, Single Sender, Matching chirp with one hashtag

```
# for user a
./command_line --user a --stream "#a"
# for user b
./command_line --user b --chirp "test #a"
```

a should print the matching chirp

```
Username: b
Text: test #a
```

### Case 3: Single User, Single Sender, Matching chirp with one hashtag with historical mathcing chirp

```
# for user b
./command_line --user b --chirp "test1 #a"
# for user a
./command_line --user a --stream "#a"
# for user b
./command_line --user b --chirp "test2 #a"
```

a should only print the matching chirp after `stream`

```
Username: b
Text: test2 #a
```

### Case 4: Single User, Single Sender, Matching chirp with multiple hashtag

```
# for user a
./command_line --user a --stream "#a"
# for user b
./command_line --user b --chirp "test #a #b #c"
```

a should print the matching chirp

```
Username: b
Text: test #a #b #c
```

### Case 5: Single User, Single Sender, Streming on different hashtag

```
# for user a
./command_line --user a --stream "#a"
./command_line --user a --stream "#c"

# for user b
./command_line --user b --chirp "test #a #b #c"
```

a stream(#a) should print the matching chirp

```
Username: b
Text: test #a #b #c
```

a stream(#c) should print the matching chirp

```
Username: b
Text: test #a #b #c
```

### Case 6: Multiple Users, Single Sender, Streaming Diffdernt hashtags

```
# for user a
./command_line --user a --stream "#a"
# for user c
./command_line --user c --stream "#c"

# for user b
./command_line --user b --chirp "test #a #b #c"
```

a should print the matching chirp

```
Username: b
Text: test #a #b #c
```

c should print the matching chirp

```
Username: b
Text: test #a #b #c
```

### Case 7: Multiple Users, Single Sender, Streaming Same hashtag

```
# for user a
./command_line --user a --stream "#a"
# for user c
./command_line --user c --stream "#a"

# for user b
./command_line --user b --chirp "test #a #b #c"
```

a should print the matching chirp

```
Username: b
Text: test #a #b #c
```

c should print the matching chirp

```
Username: b
Text: test #a #b #c
```
