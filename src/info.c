#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#pragma comment(lib, "psapi.lib")
PROCESS_MEMORY_COUNTERS_EX pmc;

unsigned int func(void) {
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS* ) &pmc, sizeof(pmc))) {
        return (unsigned int)pmc.WorkingSetSize / 1024;
    }
    return 0;
}