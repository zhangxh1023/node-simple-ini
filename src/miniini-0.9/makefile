# Copyright (C) 2009-2010 Ferdinand Majerech
# This file is part of MiniINI
# For conditions of distribution and use, see copyright notice in LICENSE.txt

i_dir = miniini/include/
s_dir = miniini/src/
o_dir = obj
objects = log.o globals.o inisection.o inifile.o allocator.o

sources = $(s_dir)log.cpp $(s_dir)globals.cpp $(s_dir)inisection.cpp $(s_dir)inifile.cpp $(s_dir)allocator.cpp
headers = $(i_dir)log.h $(i_dir)globals.h $(i_dir)typedefs.h $(i_dir)linetoken.h $(i_dir)inisection.h $(i_dir) inisectionutil.h $(i_dir)inifile.h $(i_dir)inifileutil.h $(i_dir)allocator.h $(i_dir)util.h $(i_dir)parse.h $(i_dir)time.h $(i_dir)miniini_assert.h
bin_dir = bin/
lib = libminiini.a
libdbg = libminiini-dbg.a
flags_dbg = -g -Wall -Wextra -Weffc++ -Wold-style-cast -Wundef -Wcast-qual -Wcast-align -Wconversion -Wlogical-op -Wvla $(OPT) -D MINIINI_DEBUG 
flags_opt = -Os -funroll-loops $(OPT) -D NDEBUG

define compile
	rm -f $(bin_dir)$(lib)
	g++ $(CPPFLAGS) $(LDFLAGS) -c $(sources)
	mkdir -p $(bin_dir)
	ar -cvq $(bin_dir)$(lib) $(objects)
	ar -t $(bin_dir)$(lib)
	rm $(objects) 
endef

.PHONY: all no-stl benchmark-debug benchmark-debug-no-stl benchmark-optimized benchmark-optimized-no-stl debug debug-no-stl optimized optimized-no-stl tester tester-no-stl clean install uninstall

all:
	make debug
	make optimized
	make tester
	make benchmark-debug
	make benchmark-optimized

no-stl:
	make debug-no-stl
	make optimized-no-stl
	make tester-no-stl
	make benchmark-debug-no-stl
	make benchmark-optimized-no-stl

debug: CPPFLAGS =  -I $(i_dir) $(flags_dbg) 
debug: lib = $(libdbg)
debug: 
	$(compile)

debug-no-stl: CPPFLAGS =  -I $(i_dir) $(flags_dbg) -D MINIINI_NO_STL
debug-no-stl: lib = $(libdbg)
debug-no-stl: 
	$(compile)

optimized: CPPFLAGS =  -I $(i_dir) $(flags_opt)
optimized: 
	$(compile)

optimized-no-stl: CPPFLAGS =  -I $(i_dir) $(flags_opt) -D MINIINI_NO_STL
optimized-no-stl: 
	$(compile)

tester: CPPFLAGS =  -I $(i_dir) $(flags_dbg)
tester:
	g++ -o $(bin_dir)tester $(CPPFLAGS) $(LDFLAGS) $(s_dir)tester.cpp $(bin_dir)$(libdbg)

tester-no-stl: CPPFLAGS =  -I $(i_dir) $(flags_dbg) -D MINIINI_NO_STL
tester-no-stl:
	g++ -o $(bin_dir)tester $(CPPFLAGS) $(LDFLAGS) $(s_dir)tester.cpp $(bin_dir)$(libdbg)

benchmark-debug: CPPFLAGS =  -I $(i_dir) $(flags_dbg) 
benchmark-debug:
	g++ -o $(bin_dir)benchmark-dbg $(CPPFLAGS) $(LDFLAGS) $(s_dir)benchmark.cpp $(bin_dir)$(libdbg)

benchmark-debug-no-stl: CPPFLAGS =  -I $(i_dir) $(flags_dbg) -D MINIINI_NO_STL
benchmark-debug-no-stl:
	g++ -o $(bin_dir)benchmark-dbg $(CPPFLAGS) $(LDFLAGS) $(s_dir)benchmark.cpp $(bin_dir)$(libdbg)

benchmark-optimized: CPPFLAGS =  -I $(i_dir) $(flags_opt) 
benchmark-optimized:
	g++ -o $(bin_dir)benchmark $(CPPFLAGS) $(LDFLAGS) $(s_dir)benchmark.cpp $(bin_dir)$(lib)

benchmark-optimized-no-stl: CPPFLAGS =  -I $(i_dir) $(flags_opt) -D MINIINI_NO_STL
benchmark-optimized-no-stl:
	g++ -o $(bin_dir)benchmark $(CPPFLAGS) $(LDFLAGS) $(s_dir)benchmark.cpp $(bin_dir)$(lib)

clean:
	rm -f $(objects) 
	rm -r -f bin

install:
	mkdir -p $(DESTDIR)/usr/lib/
	mkdir -p $(DESTDIR)/usr/include/
	cp $(bin_dir)$(lib) $(DESTDIR)/usr/lib/$(lib)
	cp $(bin_dir)$(libdbg) $(DESTDIR)/usr/lib/$(libdbg)
	cp miniini.h $(DESTDIR)/usr/include
	cp -R miniini $(DESTDIR)/usr/include 

uninstall:
	rm -f /usr/lib/$(lib)
	rm -f /usr/lib/$(libdbg)
	rm -f /usr/include/miniini.h
	rm -r -f /usr/include/miniini  
