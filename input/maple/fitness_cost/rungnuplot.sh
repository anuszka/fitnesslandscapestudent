#!/bin/bash

display_help() {
    # taken from https://stackoverflow.com/questions/55170843/gnuplot-buttons-greyed-out
    echo "Usage: `basename $0` gnuplot_script_file"
    echo
    echo "   Script location: ~/myscripts/"
    exit 1
}


### Preserves the buttons
### Usage: ./rungnuplot.sh <gnuplot script file>

gnuplot -e "load '$1'; pause mouse close; exit"