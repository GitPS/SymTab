/*
 * Phillip Sime
 *
 * CS 442
 *
 * 2-17-2014
 *
 */

#include "SymTab.h"

/* DEBUG BEGIN */
int main(int argc, char * argv[]){
    struct SymTab* test = createSymTab(10);
    printf("Size of Symbol Table = %d\n", test->size);

    struct SymEntry* entry1 = (struct SymEntry*)malloc(sizeof(struct SymEntry));
    struct SymEntry* entry2 = (struct SymEntry*)malloc(sizeof(struct SymEntry));
    struct SymEntry* entry3 = (struct SymEntry*)malloc(sizeof(struct SymEntry));
    struct SymEntry* entry4 = (struct SymEntry*)malloc(sizeof(struct SymEntry));
    if(enterName(test, "Test1", &entry1)){
    	printf("Name was entered!\n");
    }

    if(enterName(test, "Test2", &entry2)){
    	printf("Name was entered!\n");
    }

    if(enterName(test, "Test3", &entry3)){
    	printf("Name was entered!\n");
    }

    if(enterName(test, "Test4", &entry4)){
    	printf("Name was entered!\n");
    }
    
    if(findName(test, "Test1") != NULL){
    	printf("Found entry in symbol table.\n");
    }

    if(findName(test, "Test2") != NULL){
    	printf("Found entry in symbol table.\n");
    }

    if(findName(test, "Test3") != NULL){
    	printf("Found entry in symbol table.\n");
    }

    if(findName(test, "Test4") != NULL){
    	printf("Found entry in symbol table.\n");
    }

    printf("Name of entry: %s\n", getName(entry1));
    printf("Name of entry: %s\n", getName(entry2));
    printf("Name of entry: %s\n", getName(entry3));
    printf("Name of entry: %s\n", getName(entry4));

    struct SymEntry* entry = firstEntry(test);
    while(entry != NULL){
    	printf("Entry name = %s\n", entry->name);
    	entry = nextEntry(test, entry);
    }
    
    destroySymTab(test);
}
/* DEBUG END */

struct SymTab* createSymTab(int size){
	int i;
	/* Create reference to symbol table */
	struct SymTab* sTable = (struct SymTab*)malloc(sizeof(struct SymTab));
	if(sTable == NULL){
		fprintf(stderr, "Error: Failed to allocate memory!  Failure on %d!", __LINE__);
		exit(-1);
	}

	sTable->size = size;
	
	/* Create 'size' many symbol table entries and set them to NULL*/
	struct SymEntry** entries = (struct SymEntry**)malloc(sizeof(struct SymEntry) * size);
	if(entries == NULL){
		fprintf(stderr, "Error: Failed to allocate memory!  Failure on %d!", __LINE__);
		exit(-1);
	}

	for(i = 0; i < size; i++){
		entries[i] = NULL;
	}

	/* Set contents of symbol table */
	sTable->contents = entries;

	return sTable;
}

void destroySymTab(struct SymTab *aTable){
	int i;
	int tableSize = aTable->size;
	struct SymEntry** entries = aTable->contents;
	struct SymEntry* entry = NULL;
	struct SymEntry* tempEntry = NULL;

	/* Check each entry in the symbol table.  If NULL skip, otherwise free each entry */
	for(i = 0; i < tableSize; i++){
		/* If there are entries, free their data */
		if(entries[i] != NULL){
			/* Iterate over each entry in the linked list and free it */
			entry = entries[i];
			while(entry != NULL){
				tempEntry = entry;
				entry = entry->next;

				tempEntry->attributes = NULL;
				tempEntry->next = NULL;
				
				if(tempEntry->name != NULL){
					free(tempEntry->name);
					tempEntry->name = NULL;
				}
				
				free(tempEntry);
				tempEntry = NULL;
			}
		}
	}

	/* Free the actual symbol table as the last step */
	aTable->size = 0;
	aTable->contents = NULL;
	
	free(aTable);
	aTable = NULL;
}

bool enterName(struct SymTab *aTable, const char *name, struct SymEntry **anEntry){
	int next;
	char *actualName;
	struct SymEntry **entries;
	int hashcode = 0;
	int i = 0;

	/* Check that the name doesn't already exist in the symobl table */
	if(findName(aTable, name) != NULL){
		return false; 
	}

	/* Duplicate the name (allocate new memory) so we have a new reference to it */
	actualName = strdup(name);

	/* Set the reference to the name of the entry */
	(*anEntry)->name = actualName;

	/* Ensure the next entry is NULL */
	(*anEntry)->next = NULL;

	/* Generate haschode */
	next = name[0];
	while(next != '\0'){
		hashcode += next;
		next = name[i];
		i++;
	}
	hashcode = hashcode % aTable->size;

	entries = aTable->contents;

	/* Check if location in symbol table contians an entry already */
	if(entries[hashcode] == NULL){
		entries[hashcode] = *anEntry;
	}
	else{
		struct SymEntry *temp = entries[hashcode];
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = *anEntry;
	}

	return true;
}

struct SymEntry* findName(struct SymTab *aTable, const char *name){
	int i;
	int found = 0;
	int tableSize = aTable->size;
	struct SymEntry** entries = aTable->contents;
	struct SymEntry* entry = NULL;

	for(i = 0; i < tableSize; i++){
		/* If there are entries, check for the name */
		if(entries[i] != NULL){
			/* Check each entry in the linked list for the provided name */
			entry = entries[i];
			while(entry != NULL && found != 1){
				if(strncmp(entry->name, name, strlen(name)) == 0 && strncmp(entry->name, name, strlen(entry->name)) == 0){
					/* Increment 'i' so we can break the loop */
					i = tableSize;
					found = 1;
				}
				/* Get the next entry if name wasn't found */
				else{
					entry = entry->next;
				}
			}
		}
	}

	/* If we did not find the name we set 'entry' back to NULL */
	if(found == 0){
		entry = NULL;
	}

	return entry;
}

void settAttr(struct SymEntry *anEntry, void *attributes){
	anEntry->attributes = attributes;
}

void* getAttr(struct SymEntry *anEntry){
	return anEntry->attributes;
}

const char* getName(struct SymEntry *anEntry){
	return anEntry->name;
}

struct SymEntry* firstEntry(struct SymTab *aTable){
	int i;
	int tableSize = aTable->size;
	struct SymEntry** entries = aTable->contents;
	struct SymEntry* entry = NULL;

	for(i = 0; i < tableSize; i++){
		/* Set first entry found to 'entry' */
		if(entries[i] != NULL){
			entry = entries[i];
			i = tableSize;
		}
	}

	return entry;
}

struct SymEntry* nextEntry(struct SymTab *aTable, struct SymEntry *anEntry){
	int hashcode, next, i;
	char* name;
	int tableSize;
	struct SymEntry** entries;

	if(anEntry->next != NULL){
		return anEntry->next;
	}

	name = anEntry->name;

	/* Determine hashcode to allow us to know where to start searching 
	 * for the next entry in the symbol table 
	 */
	tableSize = aTable->size;
	entries = aTable->contents;
	i = 0;
	hashcode = 0;
	next = name[0];
	while(next != '\0'){
		hashcode += next;
		next = name[i];
		i++;
	}
	hashcode = hashcode % aTable->size;
	/* Increment hashcode in order to skip the current section we already searched */
	hashcode++;

	for(i = hashcode; i < tableSize; i++){
		/* Find first non-NULL entry if there is one*/
		if(entries[i] != NULL){
			return entries[i];
		}
	}

	return NULL;
}
