//
//  ___FILENAME___
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//___COPYRIGHT___
//

#include <assert.h>

#include <___PROJECTNAME___/___FILEBASENAMEASIDENTIFIER___.h>

#define _Class ____FILEBASENAMEASIDENTIFIER___

#pragma mark - Object

/**
 * @see Object::dealloc(Object *)
 */
static void dealloc(Object *self) {
	
	//..
	
	super(Object, self, dealloc);
}

#pragma mark - ___FILEBASENAMEASIDENTIFIER___

/**
 * @fn ___FILEBASENAMEASIDENTIFIER___ *___FILEBASENAMEASIDENTIFIER___::init(___FILEBASENAMEASIDENTIFIER___ *self)
 *
 * @memberof ___FILEBASENAMEASIDENTIFIER___
 */
static ___FILEBASENAMEASIDENTIFIER___ *init(___FILEBASENAMEASIDENTIFIER___ *self) {
	
	self = (___FILEBASENAMEASIDENTIFIER___ *) super(___VARIABLE_superclass:identifier___, self, init);
	if (self) {
		
		//..
	}
	
	return self;
}

//..

#pragma mark - Class lifecycle

/**
 * @see Class::initialize(Class *)
 */
static void initialize(Class *clazz) {
	
	((ObjectInterface *) clazz->def->interface)->dealloc = dealloc;
	
	((___FILEBASENAMEASIDENTIFIER___Interface *) clazz->def->interface)->init = init;
	
	//..
}

Class ____FILEBASENAMEASIDENTIFIER___ = {
	.name = "___FILEBASENAMEASIDENTIFIER___",
	.superclass = &____VARIABLE_superclass:identifier___,
	.instanceSize = sizeof(___FILEBASENAMEASIDENTIFIER___),
	.interfaceOffset = offsetof(___FILEBASENAMEASIDENTIFIER___, interface),
	.interfaceSize = sizeof(___FILEBASENAMEASIDENTIFIER___Interface),
	.initialize = initialize,
};

#undef _Class

