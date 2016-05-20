#include "descriptors.h"
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 255
#define DESCRIPTORS_POOL_SIZE_INCREMENT_VALUE 100

struct FileDescriptor {
	char* fileName;
	int flags;
	mode_t mode;
};

struct DescriptorIdx {
	int idx;
	struct DescriptorIdx* next;
};

static struct FileDescriptor* descriptorsPool = 0;
static int currentPoolSize = 0;
static int nextDescriptorIdx = 0;
static struct DescriptorIdx* freedDescriptorsIds = 0;

int useNextDescriptor();
int allocateNewDescriptor();
int reuseOldDescriptor();
void initializeDescriptor(int descriptorIdx);
int isThereAnyDescriptorToReuse();
int isDescriptorsPoolCreated();
void createDescriptorsPool();
void resizeDescriptorsPool();

int open(const char *pathname, int flags, mode_t mode) {
	return useNextDescriptor();
}

int useNextDescriptor() {
	if(isThereAnyDescriptorToReuse()) {
		return reuseOldDescriptor();
	}
	else {
		return allocateNewDescriptor();
	}
}

int isThereAnyDescriptorToReuse() {
	return freedDescriptorsIds != 0;
}

int allocateNewDescriptor() {
	if(!isDescriptorsPoolCreated()) {
		createDescriptorsPool();
	}
	else if(nextDescriptorIdx >= currentPoolSize) {
		resizeDescriptorsPool();
	}

	initializeDescriptor(nextDescriptorIdx);

	return nextDescriptorIdx++;
}

int isDescriptorsPoolCreated() {
	return descriptorsPool != 0;
}

void createDescriptorsPool() {
	currentPoolSize = DESCRIPTORS_POOL_SIZE_INCREMENT_VALUE;
	descriptorsPool = calloc(currentPoolSize, sizeof(struct FileDescriptor));
}

void resizeDescriptorsPool() {
	currentPoolSize += DESCRIPTORS_POOL_SIZE_INCREMENT_VALUE;
	descriptorsPool = realloc(descriptorsPool, currentPoolSize*DESCRIPTORS_POOL_SIZE_INCREMENT_VALUE);
}

int reuseOldDescriptor() {
	initializeDescriptor(freedDescriptorsIds->idx);

	freedDescriptorsIds = freedDescriptorsIds->next;

	return nextDescriptorIdx;
}

void initializeDescriptor(int descriptorIdx) {
	memset(&descriptorsPool[descriptorIdx], 0, sizeof(struct FileDescriptor));
}
