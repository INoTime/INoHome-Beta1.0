#!/bin/bash
#start installation and copie main application to /usr/lib/'INoInvestigation Garage'

sudo apt update
sudo apt install build-essential

cd desktopApp/config
cc `pkg-config gtk+-3.0 --cflags` mainConfig.c -o mainConfig `pkg-config gtk+-3.0 --libs`
sudo chmod 777 mainConfig

sudo ./mainConfig

sudo mkdir /usr/lib/INoHome
sudo chmod 777 /usr/lib/INoHome
sudo cp -r files/'INoInvestigation Garage'/* /usr/lib/INoHome/
sudo chmod 777 -R /usr/lib/INoHome
sudo cp -r files/crypt /usr/lib/INoHome/crypt
sudo cp -r files/tmp /usr/lib/INoHome/tmp
sudo chmod 777 -R /usr/lib/INoHome/*

cc `pkg-config gtk+-3.0 --cflags` /usr/lib/INoHome/main.c -o /usr/lib/INoHome/Garage `pkg-config gtk+-3.0 --libs`
sudo chmod 777 /usr/lib/INoHome/Garage

sudo cp ~/Desktop/garage/desktopApp/files/garage.desktop ~/.local/share/applications 