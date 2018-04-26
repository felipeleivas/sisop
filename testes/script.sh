for i in *.c
do
	name=$(echo $i | cut -f 1 -d '.')
	# make $name > /dev/null
	rm -rf build
	mkdir build
	gcc -c ../src/cthread.c
	gcc -o build/$name ../bin/support.o cthread.o $i -Wall
	for file in build/*
	do
		name=$(echo $file | cut -f 1 -d '.')
		name=$(echo $name | cut -f 2 -d '/')
		echo =================================================================================================
		echo running $name 
		echo
		./$file 
		echo =================================================================================================
	done;
done;