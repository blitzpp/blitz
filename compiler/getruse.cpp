#include <sys/resource.h>

int main() 
{ 
    struct rusage resUsage;
    getrusage(RUSAGE_SELF, &resUsage);
    return 0; 
}
