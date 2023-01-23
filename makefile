all: prolific generation exploration slug slugrace

prolific: prolific.c
	gcc -o prolific prolific.c
generation: generation.c
	gcc -o generation generation.c
exploration: explorer.c
	gcc -o explorer explorer.c
slug: slug.c
	gcc -o slug slug.c
slugrace: slugrace.c
	gcc -o slugrace slugrace.c


clean: 
	rm -f prolific
	rm -f generation
	rm -f explorer
	rm -f slug
	rm -f slugrace
