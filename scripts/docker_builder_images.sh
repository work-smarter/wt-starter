#!/bin/bash

echo 'Building wt_starter_build image'
docker build -t wt_starter_build -f dockerfiles/Dockerfile_build .
docker build -t wt_starter -f dockerfiles/Dockerfile_deploy .