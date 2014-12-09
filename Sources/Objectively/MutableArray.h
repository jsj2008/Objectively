/*
 * Objectively: Ultra-lightweight object oriented framework for c99.
 * Copyright (C) 2014 Jay Dolan <jay@jaydolan.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef _Objectively_MutableArray_h
#define _Objectively_MutableArray_h

#include <Objectively/Array.h>

typedef struct MutableArray MutableArray;
typedef struct MutableArrayInterface MutableArrayInterface;

/**
 * @brief The MutableArray type.
 */
struct MutableArray {

	/**
	 * @brief The parent.
	 */
	Array array;

	/**
	 * @brief The typed interface.
	 */
	MutableArrayInterface *interface;

	/**
	 * @brief The Array capacity.
	 */
	size_t capacity;

	/**
	 * @brief The Array initial capacity.
	 */
	size_t initialCapacity;
};

/**
 * @brief The MutableArray type.
 */
struct MutableArrayInterface {

	/**
	 * @brief The parent.
	 */
	ArrayInterface arrayInterface;

	/**
	 * @brief Adds the specified Object to this Array.
	 */
	void (*addObject)(MutableArray *self, const id obj);

	/**
	 * @brief Initializes this MutableArray.
	 *
	 * @return The initialized MutableArray, or `NULL` on error.
	 */
	MutableArray *(*init)(MutableArray *self);

	/**
	 * @brief Initializes this Array with the specified capacity.
	 *
	 * @param capacity The desired initial capacity.
	 *
	 * @return The initialized Array, or `NULL` on error.
	 */
	MutableArray *(*initWithCapacity)(MutableArray *self, size_t capacity);

	/**
	 * @brief Removes all Objects from this Array.
	 */
	void (*removeAllObjects)(MutableArray *self);

	/**
	 * @brief Removes the specified Object from this Array.
	 */
	void (*removeObject)(MutableArray *self, const id obj);

	/**
	 * @brief Removes the Object at the specified index.
	 *
	 * @param index The index of the Object to remove.
	 */
	void (*removeObjectAtIndex)(MutableArray *self, const int index);

	/**
	 * @brief Resizes this Array to an appropriate capacity based on count.
	 *
	 * @remark This operation is entirely optional, but can reclaim memory
	 * after large removal operations have executed.
	 */
	void (*resize)(MutableArray *self);

	/**
	 * @brief Replaces the Object at the specified index.
	 *
	 * @param obj The Object with which to replace.
	 * @param index The index of the Object to replace.
	 *
	 * @remark The index must not exceed the size of the Array.
	 */
	void (*setObjectAtIndex)(MutableArray *self, const id obj, const int index);
};

/**
 * @brief The MutableArray Class.
 */
extern Class __MutableArray;

#endif
