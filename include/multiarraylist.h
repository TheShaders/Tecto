#ifndef __MULTIARRAYLIST_H__
#define __MULTIARRAYLIST_H__

#include <types.h>

typedef struct MultiArrayListBlock_t {
    MultiArrayListBlock *next;
    u32 numElements;
} MultiArrayListBlock;

// Dynamically allocated structure consisting of chunks, each which hold an equal length array of each component
// in the provided archetype.
typedef struct MultiArrayList_t {
    MultiArrayListBlock *start;
    MultiArrayListBlock *end;
    archetype_t archetype;
    u16 totalElementSize;
    u16 elementCount;
} MultiArrayList;

int lowest_bit(size_t value);

// Initializes a new multiarraylist
void multiarraylist_init(MultiArrayList *arr, archetype_t archetype);

// Allocates count more members in the arraylist
void multiarraylist_alloccount(MultiArrayList *arr, size_t count);

// Returns the offset into the chunk for the start of the array for a given component
size_t multiarraylist_get_component_offset(MultiArrayList *arr, size_t componentIndex);

// Removes the specified entity from the array list and moves the last one's components into its place
// Returns the new length of the array list
void multiarraylist_delete(MultiArrayList *arr, size_t arrayIndex);


#endif
