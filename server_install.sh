#!/bin/bash
#start installation and copie server application to /usr/lib/'INoInvestigation Server'

sudo apt update
sudo apt install build-essential
sudo apt-get install manpages-dev
sudo apt-get install -y uuid-dev
cd server
cc -o connectionServer.c connectionServer -luuid -lpthread

sudo chmod 777 connectionServer
sudo chmod 777 install

mkdir /usr/lib/'INoHome Server'
sudo chmod 777 /usr/lib/'INoHome Server'
sudo cp -r server/* /usr/lib/'INoHome Server'/
sudo chmod 777 -R /usr/lib/'INoHome Server'/*


clear
echo "Server is starting..."
./usr/lib/'INoHome Server'/connectionServer