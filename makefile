test: test.c
	gcc -g -o test test.c -I
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