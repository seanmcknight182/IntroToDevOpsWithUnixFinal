#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// start of chatgpt written code

static const uint8_t OBF_KEY[] = "X9fA7pQ2Lm8rT4Kd"; // how secure does this need to be anyways? XOR moment I suppose
#define OBF_KEY_LEN (sizeof(OBF_KEY) - 1)

/* Compile-time encryption macro (GNU C required) */
#define OBF(str) \
({ \
    enum { _len = sizeof(str) - 1 }; \
    static uint8_t _buf[_len + 1]; \
    for (size_t _i = 0; _i < _len; _i++) \
        _buf[_i] = (str)[_i] ^ OBF_KEY[_i % OBF_KEY_LEN]; \
    _buf[_len] = 0; \
    _buf; \
})

/* JIT decrypt into caller-provided buffer */
static inline void obf_jit_decrypt(char *dst, const uint8_t *enc) {
    for (size_t i = 0; enc[i]; i++)
        dst[i] = enc[i] ^ OBF_KEY[i % OBF_KEY_LEN];
    dst[strlen((char*)enc)] = '\0';
}

/* Secure wipe — prevents compiler optimization */
static inline void obf_wipe(char *buf) {
    volatile char *p = buf;
    while (*p) {
        *p++ = 0; // if you were messing with the hardrive instead, this can wipe a whole drive, very dangerous
    }
}

void writeLiscence(){
	FILE *fPtr;
	fPtr = fopen("liscense.txt","w");	
	fprintf(fPtr, "GLORYTODEELTECH");

	fclose(fPtr);
}
 // end of chatgpt written code
// never used chatgpt written code before, interesting that it chooses to use
/* this way of doing comments, even when only commenting a single line*/
// like dude
// this is way easier, and looks better imo
int main(){
	const uint8_t *enc = OBF("4301566149452082"); // this line brought to you by chatgpt, 16 char string also brought by chat gpt
	FILE *fPtr;
	char tmp[32];   // this line brought to you by chatgpt
	obf_jit_decrypt(tmp, enc); // this line brought to you by chatgpt
	//tmp[16] = '\0';
	fPtr = fopen("liscense.txt","r");
	//printf("%s\n", tmp); 
	char InputedKey[32];
	//writeLiscence();
	
	if(fPtr == NULL)
	{
		printf("First start detected, please input liscence\n");
		scanf("%16s", InputedKey); // I lied, scanf is so outclassed by cin.
		if (strcmp(InputedKey, tmp) == 0){
			obf_wipe(tmp);// this line brought to you by chatgpt
			fclose(fPtr);
			writeLiscence();	
			return 0;
		}
		else{
			obf_wipe(tmp); // this line brought to you by chatgpt
			printf("Invalid input, exiting program\n");
			fclose(fPtr);
			return 1;
		}
	}
	if (fPtr){
		fclose(fPtr);
		return 0;
	}

  	fclose(fPtr);


	return 1;


}

