# Compile with different flags to compare performance

map="maps/mars.fdf"
folder="benchmark_output"
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

make build # For submodules
for OPT in 0 s 1 2 3 fast
do
	make clean # Force recompilation of all files
	for TRANSFORM in "" "-DSIMPLISTIC_TRANSFORM"
	do
		CPPFLAGS="$TRANSFORM -O$OPT" make build
		touch src/transform.c # force recompilation of the file affected by the define
		./fdf.exe --width=1200 --height=900 --benchmark=1024 --output=${folder}/${name}.bmp $map >> ${folder}/${name}-O${OPT}${TRANSFORM}.out
	done
done
