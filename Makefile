# minimalist makefile
.SUFFIXES:
#
.SUFFIXES: .cpp .o .c .h
ifeq ($(DEBUG),1)
CFLAGS = -fPIC  -std=c99  -mavx2 -ggdb -Wall -Wextra -Wshadow -fsanitize=undefined  -fno-omit-frame-pointer -fsanitize=address
else
CFLAGS = -fPIC -std=c99 -O3 -mavx2 -Wall -Wextra -Wshadow
endif # debug
LDFLAGS = -shared
LIBNAME=libbiasedbitstream.so.0.0.1

all:  unit benchmark $(LIBNAME)

test: unit
	./unit

install: $(OBJECTS)
	cp $(LIBNAME) /usr/local/lib
	ln -s /usr/local/lib/$(LIBNAME) /usr/local/lib/libbiasedbitstream.so
	ldconfig
	cp $(HEADERS) /usr/local/include



HEADERS=./include/simdrandombitstream.h ./include/basicgeometricdist.h ./src/simdxorshift128plus.h ./src/util.h
uninstall:
	for h in $(HEADERS) ; do rm  /usr/local/$$h; done
	rm  /usr/local/lib/$(LIBNAME)
	rm /usr/local/lib/libbiasedbitstream.so
	ldconfig


OBJECTS= simdxorshift128plus.o simdrandombitstream.o basicgeometricdist.o

$(LIBNAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(LIBNAME) $(OBJECTS)  $(LDFLAGS)

basicgeometricdist.o: ./src/basicgeometricdist.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/basicgeometricdist.c -Isrc  -Isrc -Iinclude

simdxorshift128plus.o: ./src/simdxorshift128plus.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdxorshift128plus.c -Isrc


simdrandombitstream.o: ./src/simdrandombitstream.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdrandombitstream.c -Isrc -Iinclude


unit: ./tests/unit.c    $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) -o unit ./tests/unit.c -Iinclude -Isrc  $(OBJECTS) -lm

benchmark: ./bench/bench.c ./bench/benchmark.h   $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) -o benchmark ./bench/bench.c -Iinclude -Isrc -Ibench $(OBJECTS) -lm

clean:
	rm -f unit benchmark *.o $(OBJECTS) $(LIBNAME)
