# Compile with different flags to compare performance

map="maps/mars.fdf"
if test -n "$1"
then
	map=$1
fi
name=$(basename ${map%.*})

make # For submodules
for OPT in 0 s 1 2 3 fast
do
	for TRANSFORM in "" "-DSIMPLISTIC_TRANSFORM"
	do
		CPPFLAGS="$TRANSFORM -O$OPT" make re
		./fdf.exe $map >> benchmark/${name}-O${OPT}${TRANSFORM}.out
	done
done
