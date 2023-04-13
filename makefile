SHELL := /bin/bash
randomMake: 
	chmod +x board_interface/scripts/*.py
	source ../../devel/setup.bash
	sudo chmod a+rw /dev/ttyACM0