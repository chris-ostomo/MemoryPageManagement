#include "pageTableLevel.hpp"
#include <stdio.h> // For NULL
#include <unordered_map>

// Function to extract page number from an address based on mask and shift
unsigned int pageTable::extractPageNumberFromAddress(unsigned int address, unsigned int mask, unsigned int shift) {
    return (address & mask) >> shift;
}

// Function to record page access and return the number of accesses
unsigned int pageTable::recordPageAccess(unsigned int address) {
    //Starts from root node and traverses 
    level *currentLevelPtr = rootNodePtr;
    unsigned int pageNum;

    for (unsigned int i = 0; i < levelCount; i++) {
        pageNum = extractPageNumberFromAddress(address, bitmaskAry[i], shiftAry[i]);

        // Checks if the next level exists
        if (currentLevelPtr->nextLevelPtr == nullptr) {
            // Creates and initialize the next level pointer array
            currentLevelPtr->nextLevelPtr = new level*[entryCount[i]];
            
            for (unsigned int j = 0; j < entryCount[i]; j++) {
                currentLevelPtr->nextLevelPtr[j] = nullptr;
            }
        }

        //REQUIRED: Only create the next level nodes as needed
        // Move to the next level, creating it if necessary
        if (currentLevelPtr->nextLevelPtr[pageNum] == nullptr) {
            currentLevelPtr->nextLevelPtr[pageNum] = new level;
            currentLevelPtr->nextLevelPtr[pageNum]->depth = i + 1;
            currentLevelPtr->nextLevelPtr[pageNum]->numOfAccess = 0;
            currentLevelPtr->nextLevelPtr[pageNum]->nextLevelPtr = nullptr;
        }

        currentLevelPtr = currentLevelPtr->nextLevelPtr[pageNum];
    }

    // Increment the access count at the leaf level
    currentLevelPtr->numOfAccess++;
    return currentLevelPtr->numOfAccess;
}