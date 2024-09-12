# wt-starter


sudo docker build -t wt_starter_build -f dockerfiles/Dockerfile_build .

sudo docker build -t wt_starter -f dockerfiles/Dockerfile_deploy .

sudo docker run --rm -d --network VPS-starter-containers_caddy -p 9010:9010 --name wt_starter wt_starter:latest