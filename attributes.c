/**
 * Copyright (c) 2018, Tiny Mesh AS - https://tiny-mesh.com
 * All rights reserved.
 */


#include "attributes.h"
#include <stddef.h>
#include <string.h>

int tables[LAST_TABLE_ELEMENT][2] = {
  {0},
  {1},
  {2, 3},
  {4}
};


/**
 * Set attribute `attr` in `table`
 */
int attr_set(enum attr_tables table, int attr, uint8_t value) {
  if (table >= LAST_TABLE_ELEMENT) {
    return -1;
  }

//As per Readme, if two attributes supported for each table then it's value should be 0-1.
//here sizeof(tables[0]) = 8 bytes (depends on platform), which seems wrong check. Although
//C/C++ doesn't actually do any boundary checking with regards to arrays. It depends on the OS to ensure that you are accessing valid memory.
//  if (attr >= sizeof(tables[0])) {
//    return -2;
//  }

    if (attr >= 2) {
      return -2;
    }

    tables[table][attr] = value % 10;

  return 1;
}

/**
 * Get attribute `attr` in `table`
 */
int attr_get(enum attr_tables table, int attr) {
  if (table >= LAST_TABLE_ELEMENT) {
    return -1;
  }

  //As per Readme, if two attributes supported for each table then it's value should be 0-1.
  //here sizeof(tables[0]) = 8 bytes (depends on platform), which seems wrong check. Although
  //C/C++ doesn't actually do any boundary checking with regards to arrays. It depends on the OS to ensure that you are accessing valid memory.
  //  if (attr >= sizeof(tables[0])) {
  //    return -2;
  //  }

      if (attr >= 2) {
        return -2;
      }

  return tables[table][attr];
}

/**
 * Reset all attributes to `0` in `table`
 */
int attr_reset(enum attr_tables table) {
  if (table >= LAST_TABLE_ELEMENT) {
    return -1;
  }

  memset(&tables[table], 0, sizeof(tables[0]));
  return 1;
}
