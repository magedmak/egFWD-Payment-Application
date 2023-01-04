# Makefile
A makefile is a script used to build executables from source code. It specifies how the executables should be built, and can be used to build multiple executables at once.

This makefile has the following structure:

- **'CC'**: This variable specifies the compiler to be used (in this case, **'gcc'**).

- **'Cfiles'**: This variable lists all the source files that should be included in the build process. In this case, the files are listed in separate lines preceded by **'+='**. This means that the list of files will be appended to, rather than overwritten.

- **'.PHONY'**: This specifies that the **'compile'** and **'clean'** targets are not associated with any file names. This is useful because it allows you to use these targets even if you have files with these names in your project.

- **'compile'**: This target specifies that the executable should be built by compiling all the source files listed in **'Cfiles'** using the compiler specified in **'CC'**, and linking them into an executable called "main.exe". It also includes an **'echo'** command that will print a message to the console when the target is run.

- **'clean'**: This target removes the executable file "main.exe" and prints a message to the console. The **'-rm'** command is used to delete the file, and the **'-f'** flag specifies that the command should run without prompting for confirmation even if the file does not exist. The **'@'** symbol at the beginning of the command tells **'make'** to not print the command itself before running it.

To use this makefile, you will need to have the **'make'** utility installed on your system. You can then run make at the command prompt to build the payment application, or **'make clean'** to clean up any files created by the build process.
