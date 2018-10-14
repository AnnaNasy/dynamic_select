#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

using namespace std;

void* cpuLoad(void *arg) {
	pid_t		pid;
	pthread_t 	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u\n", (char*)s, pid, tid);

	return nullptr;
}

int main() {
	int ret;
	pthread_t cputid;

	ret = pthread_create(&cputid, nullptr, cpuLoad, "cpuLoad");
	if (ret != 0) {
		fprintf(stderr, "can't create thread: %s\n", strerror(err));
		exit(1);
	}
	sleep(1);
	return 0;
}