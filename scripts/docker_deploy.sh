#!/bin/bash

echo 'Removing wt_starter container'
docker rm -f wt_starter || true
echo 'Running wt_starter container'
docker run --rm -d --network vps-starter-containers_caddy -p 9010:9010 --name wt_starter wt_starter:latest