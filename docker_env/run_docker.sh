#!/bin/bash

xhost +local:docker
docker build --tag desafio .
docker compose up