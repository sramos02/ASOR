#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	pid_t pid = getpid();
	printf("PID = %d\n", pid);

	int policy = sched_getscheduler(pid);
	printf("POLICY = %d\n", policy);

	int min = sched_get_priority_min(policy);
	int max = sched_get_priority_max(policy);
	printf("MIN_PRIORITY = %d\n", min);
	printf("MAX_PRIORITY = %d\n", max);

	struct sched_param{
        	int sched_priority;
 	};

	struct sched_param p;

	int error = sched_getparam(pid, &p);

	int act = p.sched_priority;
	printf("ACT_PRIORITY = %d\n", act);
	return 0;
}
