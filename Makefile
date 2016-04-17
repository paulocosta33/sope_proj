rmdup: rmdup.c execlsdir lsdir
	cc rmdup.c -o rmdup
	mv rmdup bin
	mv execlsdir bin
	mv lsdir bin
execlsdir: execlsdir.c
	cc execlsdir.c -o execlsdir
lsdir: lsdir.c
	cc lsdir.c -o lsdir
