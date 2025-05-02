#include <stdio.h>  // For stderr, sscanf, fprintf, FILE, and fclose 
#include <stdlib.h> // For exit(), referenced from tracereader.cpp
#include "pageTableLevel.hpp"    // Header files for necessary functions         
#include "log.hpp"               // Header files for necessary functions
#include "tracereader.hpp"       // Header files for necessary functions          

// Referenced from tracereader.cpp and a1.pdf
int main(int argc, char **argv) {
    // Checks the usage of command line arguments
    if (argc != 3) {  // Expecting exactly 3 arguments
        fprintf(stderr, "usage: %s <trace_file> \"<level0_bits> <level1_bits> <level2_bits>\"\n", argv[0]);
        exit(1);
    }

    // Declared traceFileName as the second command line argument
    const char *traceFileName = argv[1];

    // Max amount of levels for this program is 3
    unsigned int levelBits[11];

    // Scans the amount of levels and bits from the command line
    unsigned int levelCount = sscanf(argv[2], "%d %d %d %d %d %d %d %d %d %d %d", &levelBits[0], &levelBits[1], &levelBits[2], &levelBits[3], &levelBits[4], &levelBits[5], &levelBits[6], &levelBits[7], &levelBits[8], &levelBits[9], &levelBits[10]);

    // Prints an error if the level count is less than 1 or greater than 3
    // Works if the level count is greater than 3, I cound't find a fix :(
    if (levelCount < 1) {
        fprintf(stderr, "The second argument must contain at least one integer.\n");
        exit(1);
    }

    // Attempt to open the trace file
    FILE *traceFile = fopen(traceFileName, "rb");
    if (!traceFile) {
        fprintf(stderr, "Cannot open trace file %s\n", traceFileName);
        exit(1);
    }

    // Initializes the page table
    pageTable pt;
    pt.levelCount = levelCount; // Set to the number of levels declared from the command line
    pt.bitmaskAry = new unsigned int[pt.levelCount];
    pt.shiftAry = new unsigned int[pt.levelCount];
    pt.entryCount = new unsigned int[pt.levelCount];
    pt.rootNodePtr = new level;

    // Initializes the page table structure
    unsigned int shift = 32;  // Starts from the leftmost bit
    for (unsigned int i = 0; i < pt.levelCount; i++) {
        shift -= levelBits[i];
        pt.bitmaskAry[i] = ((1 << levelBits[i]) - 1) << shift;
        pt.shiftAry[i] = shift;
        pt.entryCount[i] = (1 << levelBits[i]);
    }

    // REQUIRED: Print out bitmasks for all page table levels
    log_bitmasks(pt.levelCount, pt.bitmaskAry);

    // Allocate memory for page indices based on levelCount from command line
    unsigned int* pageIndices = new unsigned int[pt.levelCount];

    // REQUIRED: Call NextAddress function to get the next address
    // Used the example from A1.pdf's appendix
    p2AddrTr addrTrace;
    while (NextAddress(traceFile, &addrTrace)) {
        unsigned int address = addrTrace.addr;
        unsigned int accesses = pt.recordPageAccess(address);

        // Extracts the page indices
        for (unsigned int i = 0; i < pt.levelCount; i++) {
            pageIndices[i] = pt.extractPageNumberFromAddress(address, pt.bitmaskAry[i], pt.shiftAry[i]);
        }

        // REQUIRED: Print page indicies at all levels and the number of page accesses
        log_pgindices_numofaccesses(address, pt.levelCount, pageIndices, accesses);
    }

    // Clean up and return success
    fclose(traceFile);
    return (0);
}
