# Triangulum-III

1. Clone from github
```sh
$ git clone https://github.com/TransNeptunianStudios/Triangulum-III  
$ npm install -d
$ git submodule update --init  
```
2. Prepare the client
```sh
$ cd Triangulum-III/client  
$ npm install   
$ npm run deploy   
```

3. Build and run server
```sh
$ export TRIANGULUM_HOME=/path/to/Triangulum-III  
$ cd Triangulum-III/server  
$ ./build_dbg.sh && cd build  
$ ./triangulum-server
```
