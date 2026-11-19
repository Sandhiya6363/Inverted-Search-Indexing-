
# Target executable
a.out: main.o create_db.o display_db.o search_db.o update_db.o save_db.o free_db.o hash_index.o read_and_validate.o
	gcc -o a.out main.o create_db.o display_db.o search_db.o update_db.o save_db.o free_db.o hash_index.o read_and_validate.o

# Compile source files
main.o: main.c inverted_search.h
	gcc -c main.c

create_db.o: create_db.c inverted_search.h
	gcc -c create_db.c

display_db.o: display_db.c inverted_search.h
	gcc -c display_db.c

search_db.o: search_db.c inverted_search.h
	gcc -c search_db.c

update_db.o: update_db.c inverted_search.h
	gcc -c update_db.c

save_db.o: save_db.c inverted_search.h
	gcc -c save_db.c

free_db.o: free_db.c inverted_search.h
	gcc -c free_db.c

hash_index.o: hash_index.c inverted_search.h
	gcc -c hash_index.c

read_and_validate.o: read_and_validate.c inverted_search.h
	gcc -c read_and_validate.c

# Clean generated files
# clean:
# 	rm -f *.o a.out
