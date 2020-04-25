#!/bin/bash

#
gnuplot --version >> "/dev/null"

if [ $? -ne 0 ]
then
    echo "Error: Cannot invoke GNUPLOT"
    exit 1
fi

#
echo -e "[BEGIN]\n"

#cache levels
for cache in "L3" "RAM"
do
	#
		echo "Running for cache: "$cache

	#
	dir="Phase2_data_"$cache
	mkdir -p $dir $dir"/logs"

	#
	cp "plot_all.gp" $dir

	#Compiler optimizations
	for comp in "gcc" "icc"
	do
		#
		echo -e "\tRunning with compiler: "$comp

		#
		mkdir -p $dir"/"$comp
		mkdir -p $dir"/"$comp"/data"

		#
		cp "plot.gp" $dir"/"$comp
		echo -n "plot " >> $dir"/"$comp"/plot.gp"

		#
		echo -e "\n\nset title \""$comp" compiler\"" >> $dir"/plot_all.gp"
		echo -n "plot " >> $dir"/plot_all.gp"

		#Going through invert code variants
		for variant in vect_hoist_interchange_mem vect_hoist_interchange_mem vect_hoist_interchange vect baseline 
		do
			#
			echo -e "\t\tVariant: "$variant
      def=` echo $variant | tr '[:lower:]' '[:upper:]' `
			#Compile variant
			make $cache"-"$variant CC=$comp CACHE=$cache DEFINE=$def >> $dir"/logs/compile.log" 2>> $dir"/logs/compile_err.log"

			#Run & select run number & cycles
			./prog  | cut -d';' -f1,4 > $dir"/"$comp"/data/"$variant
#
			#Run with maqao
			maqao oneview -R1 binary="prog" run_command="<binary>" lprof_params="--use-OS-timers" --xp=$dir"/maqao_"$cache"_"$comp"_"$variant >> $dir"/logs/maqao_reports.log"

			#setting individual plots
			echo -n "\"data/"$variant"\" w lp, " >> $dir"/"$comp"/plot.gp"

			#setting general plot
			echo -n "\""$comp"/data/"$variant"\" w lp t \""$variant"\", " >> $dir"/plot_all.gp"

			make mrproper >> $dir"/logs/compile.log" 2>> $dir"/logs/compile_err.log"

		done

		#
		cd $dir"/"$comp

		#Generate the plot
		gnuplot -c "plot.gp" > "plot_"$cache"_"$comp".png"

		cd ../..

		echo
	done

	#
	cd $dir

	#Generate the plot
	echo -e "\n\nunset multiplot" >> "plot_all.gp"
	gnuplot -c "plot_all.gp" > "plot_all_"$cache".png"

	cd ..

	#
	make clean

done

#
echo -e "\n[DONE]"
