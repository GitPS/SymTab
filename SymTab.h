/*
 * Phillip Sime
 *
 * CS 442
 *
 * 2-10-2014
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Structure:
 *   Symbol table structure.
 */

struct SymTab {
    int size;
    struct SymEntry **contents;
};

/*
 * Structure:
 *   An entry in the symbol table used in a linked list.
 */
struct SymEntry {
    char *name;
    void *attributes;
    struct SymEntry *next;
};

/*
 * Creates a reference to a symbol table of a certian size.
 *
 * Parameters:
 *   size : Approximate number of entries
 *
 * Returns:
 *   Reference to a symbol table
 */
struct SymTab* createSymTab(int size);

/*
 * Destroy all storage associated with a Symbol Table which is under 
 * the table's control.  This does not include the attributes. 
 *
 * Parameters:
 *   aTable : Symbol table to destroy
 *
 * Returns:
 *   Void
 */
void destroySymTab(struct SymTab *aTable);

/*
 * Enters a name into a symbol table.
 *
 * Parameters:
 *   aTable : Symbol table to enter name into
 *   name : Name to enter into table
 *   anEntry : The sybmol table entry the name was entered into
 *
 * Returns:
 *   True if entered into table, false otherwise
 */
bool enterName(struct SymTab *aTable, const char *name, struct SymEntry **anEntry);

/*
 * Find a name in a symbol table.
 * 
 *  Parameters:
 *   aTable : Symbol table to find the name in
 *   name : Name to to find
 *
 * Returns:
 *   Reference to sybmol table entry if found, NULL otherwise
 */
struct SymEntry* findName(struct SymTab *aTable, const char *name);

/*
 * Set the attribute pointer associated with an entry
 *
 * Parameters:
 *   anEntry : Sybmol table entry to modify attribute in
 *   attributes : attribute pointer to modify entry to
 *
 * Returns:
 *   Void
 */
void settAttr(struct SymEntry *anEntry, void *attributes);

/*
 * Get the attribute pointer associated with an entry
 *
 * Parameters:
 *   anEntry : Sybmol table entry to get attribute in
 *
 * Returns:
 *   Pointer to the entry in the symbol table
 */
void* getAttr(struct SymEntry *anEntry);

/*
 * Get the name string associated with an entry
 *
 * Parameters:
 *   anEntry : Symbol table entry to get name tring from
 *
 * Returns:
 *   Name string associated with the provided entry
 */
const char* getName(struct SymEntry *anEntry);

/*
 * Gets the first entry in a symbol table.  There is no order at which values
 * are returned other than the order they appear in the table.
 *
 * Parameters:
 *   aTable : Symbol table to find the first entry in
 *
 * Returns:
 *   Sybmol table entry that is the first entry in the table
 */
struct SymEntry* firstEntry(struct SymTab *aTable);

/*
 * Gets the next sybmol table entry after the provided sybmol table entry
 *
 * Parameters:
 *   aTable : Symbol table to find the next entry in
 *   anEntry : Symbol table entry to find the next entry from
 *
 * Returns:
 *   Symbol table entry that is the next entry in the table
 */
struct SymEntry* nextEntry(struct SymTab *aTable, struct SymEntry *anEntry);




