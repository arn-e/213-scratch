#include<stdio.h>
#include<math.h>
#include<getopt.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct cache {
	int valid[4];
	char *tag[4];
	int lru[4];
};

char *hexLookup(char hexValue){
	switch(hexValue){
		case '0': return("0000"); break;
             	case '1': return("0001"); break;
             	case '2': return("0010"); break;
             	case '3': return("0011"); break;
             	case '4': return("0100"); break;
             	case '5': return("0101"); break;
             	case '6': return("0110"); break;
             	case '7': return("0111"); break;
             	case '8': return("1000"); break;
             	case '9': return("1001"); break;
             	case 'A': return("1010"); break;
             	case 'B': return("1011"); break;
             	case 'C': return("1100"); break;
             	case 'D': return("1101"); break;
             	case 'E': return("1110"); break;
             	case 'F': return("1111"); break;
             	case 'a': return("1010"); break;
             	case 'b': return("1011"); break;
            	case 'c': return("1100"); break;
             	case 'd': return("1101"); break;
             	case 'e': return("1110"); break;
             	case 'f': return("1111"); break;
		default: return("foo");
	}
}

char *hexToBin(char *buf, char *address){

	int addressLen = strlen(address);
	
	char bin[100] = {0};
	char *binVal;


	for (int i=0; i<addressLen; i++){
		binVal = hexLookup(address[i]);
		strcat(bin, binVal);
	}

	buf = bin;
	return buf;

}

char *paddedBits(char *buf, char *bits){
	int len = 64 - strlen(bits);
	char paddedBits[len];

	for (int i = 0; i < len; i ++){
		paddedBits[i] = '0';
	}

	paddedBits[len] = '\0';
	strcat(paddedBits, bits);
	bits = paddedBits;
	strncpy(buf, bits, strlen(bits));

	return buf;
}

char *parseTagBits(int setBitCount, int blockBitCount, char *buf, char *bits){
	int tagBitCount = 64 - (setBitCount + blockBitCount);

	int startPos = 0;
	int endPos = tagBitCount; 

	char tagBits[tagBitCount];

	int j = 0;
	for (int i = startPos; i < endPos; i ++){
		tagBits[j] = bits[i];
		j ++;
	}
	tagBits[tagBitCount] = '\0';
	buf = tagBits;
	return buf;
}
	
char *parseSetBits(int setBitCount, int blockBitCount, char *buf, char *bits){
	int startPos = 64 - (setBitCount + blockBitCount);
	int endPos = 64 - blockBitCount;
	char setBits[setBitCount];

	int j = 0;
	for (int i = startPos; i < endPos; i ++){
		setBits[j] = bits[i];	
		j ++;
	}

	setBits[setBitCount] = '\0';
	buf = setBits;
	return buf;
}

char *parseBlockBits(int bitCount, char *buf, char *bits){
	int startPos = 64 - bitCount;	
	int len = strlen(bits); 
	char blockBits[bitCount];

	int j = 0;	
	for (int i = startPos; i < len; i ++){
		blockBits[j] = bits[i];
		j ++;
	}

	blockBits[bitCount] = '\0';
	buf = blockBits;
	return buf;
}

void checkCacheHit(int *lineCount, struct cache *newCache, char *tagBits, int *lru, int *hitFlag, int *cacheHitCount, int *setContents, int *setIndex){
	// printf("setContents : %i\n", *setContents);
	for (int i = 0; i < *lineCount; i ++){
		(*setContents) ++;
		if (strcmp(newCache)[(setIndex)].tag[i], (tagBits)) == 0){
			(*lru) ++;
			(*newCache)[(*setIndex)].lru[i] = (*lru);
			(*hitFlag) = 1;
			(*cacheHitCount) ++;
		}

	}	
}
char *parseFile(char *inputFile, int setBitCount, int blockBitCount, int lineCount){
	FILE *fp;
	char instruction;
	int address;
	int size;

	int lru = 0;
	int evictionCount = 0;
	int lastUsed;

	int setIndex = 0;
	int cacheHitCount = 0;
	int cacheMissCount = 0;

	char strAddress[10];
	char *binAddress;
	char *padAddress;

	char *blockBitPtr;
	char blockBits[blockBitCount];

	char *setBitPtr;
	char setBits[setBitCount];

	int tagBitCount = 64 - (setBitCount + blockBitCount);
	char *tagBitPtr;
	char tagBits[tagBitCount];

	

	fp = fopen(inputFile, "r");	

	if (fp == NULL){
		printf("file broke\n");
		return 0;
	}

	int setCount = pow(2, setBitCount);
	struct cache newCache[setCount];
	printf("initialized %i sets\n", setCount);

	for (int i = 0; i < setCount; i ++){
		for (int j = 0; j < 4; j ++){
			newCache[i].tag[j] = (char *)malloc(sizeof(char)*(tagBitCount + 1));
			for (int k = 0; k < tagBitCount; k ++ ){
				newCache[i].tag[j][k] = '0';
			}
		newCache[i].valid[j] = 0;
		}
	}

	while(1){
		fscanf(fp, " %c %x, %i", &instruction, &address, &size);
		if (instruction == 'I'){
			continue;
		}
		if (feof(fp)){
			break;
		}

		char *buf = malloc(64 * sizeof(char*));
		char *padBuf = malloc(64 * sizeof(char*));
		char *setBuf = malloc(64 * sizeof(char*));
		char *tagBuf = malloc(64 * sizeof(char*));
		char *blockBuf = malloc(64 * sizeof(char*));
		char *padCpy = malloc(64 * sizeof(char*));

		sprintf(strAddress, "%x", address);

		binAddress = hexToBin(buf, strAddress);
		
		int binLen = strlen(binAddress);

		strncpy(padCpy, binAddress, binLen);
		padCpy[binLen] = '\0';

		padAddress = paddedBits(padBuf,padCpy); 		

		blockBitPtr = parseBlockBits(blockBitCount, blockBuf, padAddress);
		strncpy(blockBits, blockBitPtr, blockBitCount);
		blockBits[blockBitCount] = '\0';

		setBitPtr = parseSetBits(setBitCount, blockBitCount, setBuf, padAddress);
		strncpy(setBits, setBitPtr, setBitCount);
		setBits[setBitCount] = '\0';

		tagBitPtr = parseTagBits(setBitCount, blockBitCount, tagBuf, padAddress);
		strncpy(tagBits, tagBitPtr, tagBitCount);	
		tagBits[tagBitCount] = '\0';
		
		setIndex = 0;
		for (int i = 0; i < setBitCount; i ++){
			setIndex *= 2;
			if (setBits[i] == '1'){
				setIndex += 1;
			}
		}

		int hitFlag = 0;
		int setContents = 0;

		// char *hitBuf = malloc(64 * sizeof(int*));
		int *lineCountPtr = &lineCount;
		struct cache (*newCachePtr)[setCount] = &newCache;
		char (*tagBitsPtr)[tagBitCount] = &tagBits;
		int *lruPtr = &lru;
		int *hitFlagPtr = &hitFlag;
		int *cacheHitCountPtr = &cacheHitCount;	
		int *setContentsPtr = &setContents;
		int *setIndexPtr = &setIndex;

		checkCacheHit(lineCountPtr, newCachePtr, tagBitsPtr, lruPtr, hitFlagPtr, cacheHitCountPtr, setContentsPtr, setIndexPtr);	

		// for (int i = 0; i < lineCount; i ++){
		// 	if  ((newCache[setIndex].valid[i] == 1)) {
		// 		setContents ++;
		// 		if (strcmp(newCache[setIndex].tag[i], tagBits) == 0){
		// 			lru ++;
		// 			newCache[setIndex].lru[i] = lru;
		// 			hitFlag = 1;
		// 			cacheHitCount++;
		// 		}
		// 	}
		// }

		if (hitFlag == 0) {
			cacheMissCount ++;

			for (int i = 0; i < lineCount; i ++){
				if ((newCache[setIndex].valid[i] == 0)){
					lru ++;
					newCache[setIndex].valid[i] = 1;
					newCache[setIndex].lru[i] = lru;
					strcpy(newCache[setIndex].tag[i], tagBits);
					break;
				}
			}

			if (setContents == lineCount){
				evictionCount++;

				lastUsed = 0;

				for (int i = 1; i < lineCount - 1; i++){
					if (newCache[setIndex].lru[i] < newCache[setIndex].lru[i+1]){
						lastUsed = i;
					};
				}

				lru ++;

				newCache[setIndex].lru[lastUsed] = lru;
				newCache[setIndex].valid[lastUsed] = 1;
				strcpy(newCache[setIndex].tag[lastUsed], tagBits);
			}
		}

		if (instruction == 'M'){
			cacheHitCount++;
		}


		free(buf);	
		free(padBuf);
		free(setBuf);
		free(blockBuf);
		free(tagBuf);
		free(padCpy);

					
	}	
	fclose(fp);
	printf("Hits      : %i\n", cacheHitCount);
	printf("Misses    : %i\n", cacheMissCount);
	printf("Evictions : %i\n", evictionCount);
	return inputFile;	
}

int main(int argc, char **argv){
	int opt;
	int setBitCount;
	int blockBitCount;
	char *trace;
	int lineCount;

	while ((opt = getopt(argc, argv, "v:s:E:b:t:")) != -1){
		switch(opt) {
		
		case 'h':
			// help menu
			break;
		case 't':
			trace = optarg;
			break;
		case 's':
			setBitCount = atoi(optarg);
			break;
		case 'b':
			blockBitCount = atoi(optarg);
			break;
		case 'E':
			lineCount = atoi(optarg);
			break;
		}
	}
	// debug, remove
	printf("set bits   : %i\n", setBitCount);
	printf("lineCount  : %i\n", lineCount);
	printf("block bits : %i\n", blockBitCount);
	printf("trace file : %s\n", trace);
	parseFile(trace, setBitCount, blockBitCount, lineCount);	
}


