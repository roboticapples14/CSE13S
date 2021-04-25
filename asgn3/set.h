#ifndef __SET_H__
#define __SET_H__

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t Set;

#define SET_CAPACITY 32 // 32 bits means 32 items max.

// Returns an empty set.
Set set_empty(void);

// Returns true if x is in the set, false otherwise.
bool set_member(Set s, int x);

// Returns set s after inserting x.
Set set_insert(Set s, int x);

// Returns set s after removing x.
Set set_remove(Set s, int x);

// Returns the union of set s and set t.
Set set_union(Set s, Set t);

// Returns the intersect of set s and set t.
Set set_intersect(Set s, Set t);

// Returns the difference of set s and set t.
Set set_difference(Set s, Set t);

// Returns the complement of set s.
Set set_complement(Set s);

#endif
