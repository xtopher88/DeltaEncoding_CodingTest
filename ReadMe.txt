compiled it and run on ubuntu linux using gcc version 5.4.0

Input files
$ cat test_files/original_file 
a b  c
$ cat test_files/new_file 
abcd
$ cat test_files/foo 
polaod
$ cat test_files/bar 
abcd


Testing results
$ ./simple_delta test_files/original_file test_files/new_file
d
$ ./simple_delta test_files/foo test_files/bar 
omixod



