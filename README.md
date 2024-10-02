# wt-starter


sudo docker build -t wt_starter_build -f dockerfiles/Dockerfile_build .

sudo docker build -t wt_starter -f dockerfiles/Dockerfile_deploy .

sudo docker run --rm -d --network VPS-starter-containers_caddy -p 9010:9010 --name wt_starter wt_starter:latest

docker  run --rm -it  \
        -p 9010:9010 \
        -e AWS_ACCESS_KEY_ID=AKIAZAGYIJ4EHIOHJLF4 \
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