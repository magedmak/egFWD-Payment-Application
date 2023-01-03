# Makefile
A makefile is a script used to build executables from source code. It specifies how the executables should be built, and can be used to build multiple executables at once.

This makefile has the following structure:

- **'CC'**: This variable specifies the compiler to be used (in this case, gcc).

- **'Cfiles'**: This variable lists all the source files that should be included in the build process. In this case, the files are listed in separate lines preceded by +=. This means that the list of files will be appended to, rather than overwritten.

- **'.PHONY'**: This specifies that the all and clean targets are not associated with any file names. This is useful because it allows you to use these targets even if you have files with these names in your project.

- **'all'**: This target specifies that the executable should be built by compiling all the source files listed in Cfiles using the compiler specified in CC, and linking them into an executable called "main.exe".

- **'clean'**: This target removes any object files and the executable created by the makefile.

- To use this makefile, you will need to have the make utility installed on your system. You can then run make at the command prompt to build the payment application, or make clean to clean up any files created by the build process.
