prolific: prolific.c
	gcc -o prolific prolific.c
generation: generation.c
	gcc -o generation generation.c
#exploration: exploration.c
#	gcc -o exploration exploration.c
slug: slug.c
	gcc -o slug slug.c
slugrace: slugrace.c
	gcc -o slugrace slugrace.c

all: prolific generation slug slugrace
#add exploration        ^

clean: 
	rm -f prolific
	rm -f generation
#	rm -f exploration
	rm -f slug
	rm -f slugrace
