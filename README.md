# Triangulum-III

1. Clone from github
> git clone https://github.com/TransNeptunianStudios/Triangulum-III  
> cd Triangulum-III  
> git submodule update --init  

2. Prepare the client
> cd Triangulum-III/client
> npm install
> npm run deploy   

3. Build and run server
> cd Triangulum-III/server  
> mkdir build && cd build  
> cmake .. && make  
> ./triangulum-server
