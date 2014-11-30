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

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#include <curl/curl.h>

#include <Objectively/Once.h>
#include <Objectively/URLSession.h>

#define __Class __URLSession

#pragma mark - ObjectInterface

/**
 * @see ObjectInterface::dealloc(Object *)
 */
static void dealloc(Object *self) {

	URLSession *this = (URLSession *) self;

	$(this, invalidateAndCancel);

	super(Object, self, dealloc);
}

#pragma mark - URLSessionInterface

static URLSession *__sharedInstance;

/**
 * @see URLSessionInterface::sharedInstance(void)
 */
static URLSession *sharedInstance(void) {
	static Once once;

	DispatchOnce(once, {
		__sharedInstance = $(alloc(URLSession), init);
	});

	return __sharedInstance;
}

/**
 * @see URLSessionInterface::dataTaskWithRequest(URLSession *, URLRequest *)
 */
static URLSessionDataTask *dataTaskWithRequest(URLSession *self, URLRequest *request) {

	URLSessionTask *task = (URLSessionTask *) alloc(URLSessionDataTask);
	return (URLSessionDataTask *) $(task, initWithRequestInSession, request, self);
}

/**
 * @see URLSessionInterface::dataTaskWithURL(URLSession *, URL *)
 */
static URLSessionDataTask *dataTaskWithURL(URLSession *self, URL *url) {

	URLRequest *request = $(alloc(URLRequest), initWithURL, url);
	URLSessionDataTask *task = $(self, dataTaskWithRequest, request);

	release(request);
	return task;
}

/**
 * @see URLSessionInterface::downloadTaskWithRequest(URLSession *, URLRequest *)
 */
static URLSessionDownloadTask *downloadTaskWithRequest(URLSession *self, URLRequest *request) {

	URLSessionTask *task = (URLSessionTask *) alloc(URLSessionDownloadTask);
	return (URLSessionDownloadTask *) $(task, initWithRequestInSession, request, self);
}

/**
 * @see URLSessionInterface::downloadTaskWithURL(URLSession *, URL *)
 */
static URLSessionDownloadTask *downloadTaskWithURL(URLSession *self, URL *url) {

	URLRequest *request = $(alloc(URLRequest), initWithURL, url);
	URLSessionDownloadTask *task = $(self, downloadTaskWithRequest, request);

	release(request);
	return task;
}

/**
 * @see URLSessionInterface::init(URLSession *)
 */
static URLSession *init(URLSession *self) {

	self = (URLSession *) super(Object, self, init);
	if (self) {

	}

	return self;
}

/**
 * @see URLSessionInterface::init(URLSession *)
 */
static void invalidateAndCancel(URLSession *self) {

	assert(self != __sharedInstance);

	// TODO
}

#pragma mark - Class lifecycle

/**
 * @see Class::initialize(Class *)
 */
static void initialize(Class *clazz) {

	((ObjectInterface *) clazz->interface)->dealloc = dealloc;

	URLSessionInterface *session = (URLSessionInterface *) clazz->interface;

	session->sharedInstance = sharedInstance;
	session->dataTaskWithRequest = dataTaskWithRequest;
	session->dataTaskWithURL = dataTaskWithURL;
	session->downloadTaskWithRequest = downloadTaskWithRequest;
	session->downloadTaskWithURL = downloadTaskWithURL;
	session->init = init;
	session->invalidateAndCancel = invalidateAndCancel;

	const CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
	assert(code == CURLE_OK);
}

/**
 * @see Class::destroy(Class *)
 */
static void destroy(Class *clazz) {

	if (__sharedInstance) {
		release(__sharedInstance);
	}

	curl_global_cleanup();
}

Class __URLSession = {
	.name = "URLSession",
	.superclass = &__Object,
	.instanceSize = sizeof(URLSession),
	.interfaceOffset = offsetof(URLSession, interface),
	.interfaceSize = sizeof(URLSessionInterface),
	.initialize = initialize,
	.destroy = destroy,
};

#undef __Class
