#ifndef PAGETABLELEVEL_HPP
#define PAGETABLELEVEL_HPP

struct level {
    // Necessary variable initializations from pagetable.pdf and a1.pdf
    unsigned int depth;
    unsigned int numOfAccess;
    level **nextLevelPtr;
};

struct pageTable {
    // Necessary variable and function initializations from pagetable.pdf and a1.pdf
    unsigned int levelCount;
    unsigned int *bitmaskAry;
    unsigned int *shiftAry;
    unsigned int *entryCount;
    level *rootNodePtr;

    unsigned int recordPageAccess(unsigned int address);
    unsigned int extractPageNumberFromAddress(unsigned int address, unsigned int mask, unsigned int shift);
};

#endif