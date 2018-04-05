#!/bin/bash
DIRC=$HOME/.initdev

mkdir $DIRC

cp -r bin $DIRC
cp -r gitignores $DIRC
cp -r licenses $DIRC
cp -r makefiles $DIRC
cp -r sources $DIRC


echo export PATH="$PATH:${DIRC}/bin" >> $HOME/.profile
