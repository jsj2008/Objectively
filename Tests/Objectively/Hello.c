// Hello.h

#include <stdio.h>

#include <Objectively.h>

typedef struct Hello Hello;
typedef struct HelloInterface HelloInterface;

struct Hello {
	Object object;
	const char *greeting;
};

struct HelloInterface {
	ObjectInterface objectInterface;

	Hello *(*initWithGreeting)(Hello *self, const char *greeting);
	void (*sayHello)(const Hello *self);
};

extern Class __Hello;

// Hello.c

#pragma mark - Object instance methods

static Object *init(Object *self) {
	return (Object *) $(Hello, self, initWithGreeting, NULL);
}

#pragma mark - Hello instance methods

static Hello *initWithGreeting(Hello *self, const char *greeting) {

	self = (Hello *) super(Object, self, init);
	if (self) {
		self->greeting = greeting ?: "hello";
	}
	return self;
}

static void sayHello(const Hello *self) {
	printf("%s\n", self->greeting);
}

#pragma mark - Hello class methods

static void initialize(Class *self) {

	((ObjectInterface *) self->interface)->init = init;

	((HelloInterface *) self->interface)->initWithGreeting = initWithGreeting;
	((HelloInterface *) self->interface)->sayHello = sayHello;
}

Class __Hello = {
	.name = "Hello",
	.superclass = &__Object,
	.instanceSize = sizeof(Hello),
	.interfaceSize = sizeof(HelloInterface),
	.initialize = initialize,
};

#pragma mark - main

int main(int argc, char **argv) {

	Hello *hello = $(Hello, alloc(Hello), initWithGreeting, "Hello World!");
	$(Hello, hello, sayHello);
	release(hello);
}
