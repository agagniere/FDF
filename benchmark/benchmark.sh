# Compile with different flags to compare performance

map="maps/mars.fdf"
if test -n "$1"
then
	map=$1
fi

make # For submodules
for OPT in 0 2
do
	for TRANSFORM in "-DSIMPLISTIC_TRANSFORM" ""
	do
		CPPFLAGS="$TRANSFORM -O$OPT" make re
		./fdf.exe $map >> $(basename ${map%.*})-O${OPT}${TRANSFORM}.out
	done
done
