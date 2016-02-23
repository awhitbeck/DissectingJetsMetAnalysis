#!/bin/sh

export DelphesLib="./Delphes/Delphes-3.2.0/"
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$DelphesLib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DelphesLib