# Compile with different flags to compare performance

map="maps/mars.fdf"
folder="/tmp/fdf_benchmark"

if test -n "$1"
then
	map=$1
fi
if test -n "$2"
then
	folder=$2
fi
name=$(basename ${map%.*})
if ! test -d "$folder"
then
	mkdir -p $folder
fi
gnuplot_script=$folder/"render.gnuplot"
echo -n > $gnuplot_script

make build # For submodules
for OPT in 0 s 2 fast
do
	make clean # Force recompilation of all files
	for TRANSFORM in "" "-DSIMPLISTIC_TRANSFORM"
	do
		CPPFLAGS="$TRANSFORM -O$OPT" make build
		touch src/transform.c # force recompilation of the file affected by the define
		./fdf.exe --width=512 --height=512 --benchmark=1024 --output=/dev/null $map >> ${folder}/${name}-O${OPT}${TRANSFORM}.out
		echo '"'${folder}/${name}-O${OPT}${TRANSFORM}.out'"' using "(column(2) / column(1))" with lines title "'-O${OPT} ${TRANSFORM}'" >> $gnuplot_script
	done
done
