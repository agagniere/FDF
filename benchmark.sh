# Compile with different flags to compare performance

make # For submodules
for OPT in 0 2
do
	for TRANSFORM in "-DSIMPLISTIC_TRANSFORM" ""
	do
		CPPFLAGS="$TRANSFORM -O$OPT" make re
		./fdf.exe maps/mars.fdf > mars${OPT}${TRANSFORM}.out
	done
done
