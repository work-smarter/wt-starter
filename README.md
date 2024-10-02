# wt-starter


sudo docker build -t wt_starter_build -f dockerfiles/Dockerfile_build .

sudo docker build -t wt_starter -f dockerfiles/Dockerfile_deploy .

sudo docker run --rm -d --network VPS-starter-containers_caddy -p 9010:9010 --name wt_starter wt_starter:latest

docker  run --rm -it  \
        -p 9010:9010 \
        -e AWS_ACCESS_KEY_ID=AKIAZAGYIJ4ELRSHZ7GJ \
        -e AWS_SECRET_ACCESS_KEY=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 \
        -e AWS_DEFAULT_REGION=eu-north-1 \
        --name wt_starter wt_starter:latest 

### Commands to start the application
mkdir build 
cd build
cmake ..
make
make run


### Commands to start the tailwind watch process
cd tailwindn
npm install
npm run watch