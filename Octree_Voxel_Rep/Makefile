all:	octree
octree:	g++ lib/octree.o octree_main.o -o octree -lGLU -lGL -lglut
lib/octree: g++ -c lib/octree.cpp -lGLU -lGL -lglut
octree_main:	g++ -c octree_main.cpp -lGLU -lGL -lglut	
	
