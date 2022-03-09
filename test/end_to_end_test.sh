FDF=../fdf.exe
INPUT_FOLDER=../maps

total=0
success=0

function assert_error()
{
	cmd=$1
	expect=$2
	result=$(bash -c "$cmd" 2>&1)

	if [[ -z $(echo $result | grep "$expect") ]]
	then
		echo "Command '$cmd'"
		echo "Did not fail with the expected pattern '$expect'"
		echo $result
	else
		((success++))
	fi
	((total++))
}

# Wrong parameters
assert_error "$FDF" \
			 'Please provide an input file'
assert_error "$FDF -w1024 --height=1024 --title 'Failing'" \
			 'Please provide an input file'

assert_error "$FDF -w1024 --height=1024 --title" \
			 'Option "title" requires an argument'
assert_error "$FDF -w10 -h10 -h" \
			 'Option "h" requires an argument'

assert_error "$FDF -w10 -h10 -a 0 -- -" \
			 'Unknown option "a"'
assert_error "$FDF -w10 -h10 --no-such-option 0 -- -" \
			 'Unknown option "no-such-option"'

assert_error "$FDF -w10 -h10 -b -2048 -o toto $INPUT_FOLDER/42.fdf" \
			 'The number of iterations for benchmark must be positive, it cannot be -2048'
assert_error "$FDF -w10 -h10 -b2048 $INPUT_FOLDER/42.fdf" \
			 'The "benchmark" option has no effect when not in headless mode. It is to be used in conjunction with the "output" option'

assert_error "$FDF -w -1024 --height=1024 --title 'Failing' $INPUT_FOLDER/42.fdf"  \
			 'Image dimension must be positive, it cannot be (-1024, 1024)'
assert_error "$FDF -w 1024 --height 0 --title 'Failing' $INPUT_FOLDER/42.fdf"  \
			 'Image dimension must be positive, it cannot be (1024, 0)'


# Failing to open files
assert_error "$FDF inexistant" \
			 'Unable to open input file "inexistant" : No such file or directory'
assert_error "$FDF -w 1024 --height=1024 --title Failing -- inexistant" \
			 'Unable to open input file "inexistant" : No such file or directory'
assert_error "touch inaccessible ; chmod 0 inaccessible ; $FDF inaccessible ; rm -f inaccessible" \
			 'Unable to open input file "inaccessible" : Permission denied'

assert_error "$FDF -o inexistant/pic.bmp $INPUT_FOLDER/42.fdf" \
			 'Issue encountered with the output file "inexistant/pic.bmp" : No such file or directory'
assert_error "$FDF --output='..' -- $INPUT_FOLDER/42.fdf" \
			 'Issue encountered with the output file ".." : Is a directory'
assert_error "touch inaccessible ; chmod 0 inaccessible ; $FDF -o inaccessible $INPUT_FOLDER/42.fdf ; rm -f inaccessible" \
			 'Issue encountered with the output file "inaccessible" : Permission denied'


# Wrong format
assert_error "echo -e ' 0 1 2 3 \n 0 1 2 abc ' | $FDF  -" \
			 'File "<stdin>" is invalid : wrong format (line 2)'
assert_error "echo -e '-0\t1   +2  -3\n 0 1 2 +pi ' | $FDF  -" \
			 'File "<stdin>" is invalid : wrong format (line 2)'

assert_error "echo -e ' 0 1 2 3 \n 3\t2   1 0 \n 0 1 2 ' | $FDF  -" \
			 'Object described in file "<stdin>" is invalid : all lines are not the same length. (line 3)'

assert_error "echo -e '' | $FDF  -" \
			 'Object described in file "<stdin>" is invalid : (0, 0) is not a valid dimension, it should have at least 2 points'
assert_error "echo -e '0' | $FDF  -" \
			 'Object described in file "<stdin>" is invalid : (1, 1) is not a valid dimension, it should have at least 2 points'
assert_error "echo -e '\n\n\n0' | $FDF  -" \
			 'Object described in file "<stdin>" is invalid : (1, 1) is not a valid dimension, it should have at least 2 points'

echo "Passed $success / $total tests"

find $INPUT_FOLDER -type f | xargs -L1 $FDF -o /dev/null > /dev/null
