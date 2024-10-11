#!/bin/bash

# Check if the correct number of arguments are provided
if [ "$#" -ne 5 ]; then
    echo "Usage: $0 <AWS_ACCESS_KEY_ID> <AWS_SECRET_ACCESS_KEY> <AWS_DEFAULT_REGION> <POSTGRES_PASSWORD>"
    exit 1
fi

AWS_ACCESS_KEY_ID=$1
AWS_SECRET_ACCESS_KEY=$2
AWS_DEFAULT_REGION=$3
POSTGRES_PASSWORD=$4
VPS_IP=$5

echo 'Removing wt_starter container'
docker rm -f wt_starter || true
echo 'Running wt_starter container'
docker  run --rm -d  \
        --network vps-starter-containers_caddy \
        -p 9010:9010 \
        -e AWS_ACCESS_KEY_ID=$AWS_ACCESS_KEY_ID \
        -e AWS_SECRET_ACCESS_KEY=$AWS_SECRET_ACCESS_KEY \
        -e AWS_DEFAULT_REGION=$AWS_DEFAULT_REGION \
        -e POSTGRES_PASSWORD=$POSTGRES_PASSWORD \
        -e VPS_IP=$VPS_IP \
        --name wt_starter wt_starter:latest 