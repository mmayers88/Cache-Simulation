#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

//parameters given
#define CAPACITY 16000000
#define LINE_SIZE 64
#define SET_ASS 8
//#define LINES (CAPACITY/LINE_SIZE) / SET_ASS
#define LINES 32768

//has a write allocate policy
// MESI protocol
// replacement: pseudo-LRU

//parameters derived
typedef struct cLine
{
    char mesi;
    uint8_t pLUR;      //bits for the way
    bool valid;
    bool dirty;
    uint32_t tag;     //won't use the whole 32 bits
    uint8_t byte_sel; //will only need 6 bits
} cLine;

cLine cache[LINES][SET_ASS];

uint32_t address;
/*
* Bus Operation types
*/
#define READ 1       /* Bus Read */
#define WRITE 2      /* Bus Write */
#define INVALIDATE 3 /* Bus Invalidate */
#define RWIM 4       /* Bus Read With Intent to Modify */
/*
* Snoop Result types
*/
#define NOHIT 0 /* No hit */
#define HIT 1   /* Hit */
#define HITM 2  /* Hit to modified line */
/*
* L2 to L1 message types
*/
#define GETLINE 1        /* Request data for modified line in L1 */
#define SENDLINE 2       /* Send requested cache line to L1 */
#define INVALIDATELINE 3 /* Invalidate a line in L1 */
#define EVICTLINE 4      /* Evict a line from L1 */
// this is when L2's replacement policy causes eviction of a line that
// may be present in L1. It could be done by a combination of GETLINE
// (if the line is potentially modified in L1) and INVALIDATELINE.

/*
Used to simulate a bus operation and to capture the snoop results of last
level caches of other processors
*/
void BusOperation(char BusOp, unsigned int Address, char *SnoopResult);
/*
Used to simulate the reporting of snoop results by other caches
*/
int GetSnoopResult(unsigned int Address);
/*
Used to report the result of our snooping bus operations performed by other
caches
*/
void PutSnoopResult(unsigned int Address, char SnoopResult);
/*
Used to simulate communication to our upper level cache
*/
void MessageToCache(char Message, unsigned int Address);





int initCache(cLine cache[][SET_ASS]);
int printCache(cLine cache[][SET_ASS]);

int parser(FILE *fp);

int breakup(char *line);

int switchInstruction(int instruct, int address);

int addToCLine(uint32_t address, cLine cache[][SET_ASS], int way);
int verify(uint32_t address, cLine cache[][SET_ASS]);
int emptyInLine(uint32_t index, uint32_t testTag, cLine cache[][SET_ASS]);
int findMatch(uint32_t index, uint32_t testTag, cLine cache[][SET_ASS]);
int findEmpty(uint32_t index,cLine cache[][SET_ASS]);
int getIndex(uint32_t address);

/*same for snoopWr, snoopX, and snoopInvalid*/
int snoopInval(int address,cLine cache[][SET_ASS]);

int snoopRd(int address,cLine cache[][SET_ASS]);

int snoopWr(int address,cLine cache[][SET_ASS]);

int snoopX(int address,cLine cache[][SET_ASS]);
