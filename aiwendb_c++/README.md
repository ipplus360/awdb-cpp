To install this code, run the following commands:
1.this is a wrap of c library, first of all ,enter the libaiwendb_c dictory follow the README step,compile the c library


2.compile and install 
	$ sudo cmake .
    $ sudo make 
	$ sudo make install 

	
3. run the demo
	$ cd src-main
	$ ./geolite2pp




4. problems. if you got compile error,you need update your gcc version
	1.download gcc 5.4.0
	$ wget https://ftp.gnu.org/gnu/gcc/gcc-5.4.0/gcc-5.4.0.tar.bz2
	$ tar -jxvf gcc-5.4.0.tar.bz2
	$ cd gcc-5.4.0
	$ ./contrib/download_prerequisites
	$ mkdir gcc-build-5.4.0
	$ cd gcc-build-5.4.0
	$ ../configure --enable-checking=release --enable-languages=c,c++ --disable-multilib
	$ make -j4
	$ make install
	$ cd /usr/bin/
	$ mv gcc gcc_back
	$ mv g++ g++_back
	$ ln -s /usr/local/bin/gcc gcc
	$ ln -s /usr/local/bin/g++ g++
	
	
	2. if got error: ‘__int128’ is not supported on this target ,you machine is x86,change machine to x86_64
    
	