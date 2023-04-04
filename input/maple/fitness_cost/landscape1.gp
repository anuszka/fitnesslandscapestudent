set term wxt
set multiplot layout 1,2

set pm3d #map

set ticslevel 0



# x = k_{mr}
# y = k_{r}

file1 = "landscape1.dat"
file2 = "landscape2.dat"

set title ""
set xlabel "Transcription rate, k_{mr}"
set ylabel "Translation rate, k_{r}"
set zlabel "Fitness"
 set view 10.,53.
#set view 46.,60.
# set ztics 500
splot [:][:][0:] file1 u 1:2:3 with pm3d title "Fitness"
splot [:][:][:] file2 u 1:2:3 with pm3d title "Fitness"
unset multiplot
unset output
set term wxt
reset
