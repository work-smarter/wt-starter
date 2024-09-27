#!/bin/bash
echo 'Removing wt_starter_build and wt_starter images'
docker rmi -f wt_starter_build wt_starter || true

echo 'Building wt_starter_build image'
docker build -t wt_starter_build -f dockerfiles/Dockerfile_build .
docker build -t wt_starter -f dockerfiles/Dockerfile_deploy .
