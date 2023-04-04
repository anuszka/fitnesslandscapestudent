#!/bin/bash

### Preserves the buttons
### Usage: ./rungnuplot.sh <gnuplot script file>

gnuplot -e "load '$1'; pause mouse close; exit"