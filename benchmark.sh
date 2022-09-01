# Compile with different flags to compare performance

map="maps/mars.fdf"
folder="/tmp/fdf_benchmark"
result="benchmark_graph.png"
if test -n "$1"
then
	map=$1
fi
if test -n "$2"
then
	folder=$2
fi
if test -n "$3"
then
	result=$3
fi
if test ! -d "$folder"
then
	mkdir -p $folder
fi

name=$(basename ${map%.*})
gnuplot_script="$folder/render.gnuplot"
declare -a Targets=()

echo set terminal png size 2560,1440 > $gnuplot_script
echo "set output '${result}'" >> $gnuplot_script
cat <<-'EOF' >> $gnuplot_script
	set title 'Comparing transform algorithms and optimization flags'
	set xlabel 'Iteration'
	set ylabel 'Average delay to transform 1 point (ns)'
	set ytics 20
	set mytics 4
EOF

make build # Build submodules with default flags
for FLAGS in -O0 -O2 -Ofast_-march=native
do
	make clean # Force recompilation of all files
	for TRANSFORM in "" "-DSIMPLISTIC_TRANSFORM"
	do
        CPPFLAGS="$(tr '_' ' ' <<<$FLAGS) $TRANSFORM" make build
		./fdf.exe --width=256 --height=256 --benchmark=1024 --output=/dev/null $map >> ${folder}/${name}${FLAGS}${TRANSFORM}.out
		touch src/transform.c # force recompilation of the file affected by the define
		Targets=("${Targets[@]}" "\"${folder}/${name}${FLAGS}${TRANSFORM}.out\" using (column(2)/column(1)) with lines title '$(tr '_' ' ' <<<${FLAGS}_${TRANSFORM})'")
	done
done

IFS=,
echo -n "plot [5:1020][0:120] " >> $gnuplot_script
echo "${Targets[*]}" >> $gnuplot_script
gnuplot "$gnuplot_script"
