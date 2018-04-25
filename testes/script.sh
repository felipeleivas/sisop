for i in *.c
do
	name=$(echo $i | cut -f 1 -d '.')
	make $name > /dev/null
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