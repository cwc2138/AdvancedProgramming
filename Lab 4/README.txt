Zuokun Yu
zy2170
Lab 4
Lab implemented as specified in the lab

Implementation is pretty straightforward. The only non-standard thing is
the access() function which checks if a file exists or not.

I added
{hizhiz} added {lolcat}
 
Valgrind below vv
==15909== Memcheck, a memory error detector
==15909== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==15909== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==15909== Command: ./mdb-lookup my-mdb
==15909== 
lookup: 1: {hiz} said {yayay}
2: {test1} said {test1}
3: {test2} said {test2}
4: {thisisrlylong} said {thisisrlylongtoo}

lookup: 1: {hiz} said {yayay}
2: {test1} said {test1}
3: {test2} said {test2}
4: {thisisrlylong} said {thisisrlylongtoo}

lookup: 
lookup: 
lookup: 
lookup: ==15909== 
==15909== HEAP SUMMARY:
==15909==     in use at exit: 0 bytes in 0 blocks
==15909==   total heap usage: 9 allocs, 9 frees, 792 bytes allocated
==15909== 
==15909== All heap blocks were freed -- no leaks are possible
==15909== 
==15909== For counts of detected and suppressed errors, rerun with: -v
==15909== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
