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
cp benchmark/header.gnuplot $gnuplot_script
declare -a Targets=()

make build # For submodules
for OPT in 0 s 2 fast
do
	make fclean # Force recompilation of all files
	for TRANSFORM in "" "-DSIMPLISTIC_TRANSFORM"
	do
		CPPFLAGS="$TRANSFORM -O$OPT" make build
		./fdf.exe --width=256 --height=256 --benchmark=1024 --output=/dev/null $map >> ${folder}/${name}-O${OPT}${TRANSFORM}.out
		touch src/transform.c # force recompilation of the file affected by the define
		Targets=("${Targets[@]}" "\"${folder}/${name}-O${OPT}${TRANSFORM}.out\" using (column(2) / column(1)) with lines title '-O${OPT} ${TRANSFORM}'")
	done
done

IFS=,
echo -n "plot [4:1004][0:100] " >> $gnuplot_script
echo "${Targets[*]}" >> $gnuplot_script
gnuplot "$gnuplot_script"
