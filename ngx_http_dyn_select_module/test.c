#include <stdio.h>
#include "query_memcache_ip.c"


int main() {

	initWeight_t staticWeight;
    int ret;
    ret = getWeight(&staticWeight);
    printf("server1:%d", staticWeight.ser1Weight)
	return 0;
}
