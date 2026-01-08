#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*
 * checksum_append_to - Computes 8-bit checksum and appends decimal string to output
 * @input: Input null-terminated string (max 12 characters)
 * @output: Output buffer for result (minimum 18 bytes capacity)
 *
 * Computes the 8-bit checksum (sum of input bytes modulo 256) of the input string,
 * then appends the decimal representation as ASCII characters to the output buffer.
 * The appended checksum excludes itself from the computation.
 * Input is truncated if longer than 12 characters to ensure buffer safety.
 *
 * Return:
 *   uint8_t - Checksum value (0-255) on success
 *   0 - On error (null input/output pointers or input >12 chars)
 */
uint8_t checksumAppend(const char *input, char *output) {
    /* Validate inputs: check for null pointers or excessive length */
    if (!input || !output || strlen(input) > 12) {  /* Reduced to leave room for up to 3 decimal digits + null */
        return 0;  /* Error case: invalid arguments */
    }
    
    /* Determine input length and safely copy to output buffer */
    size_t lenghtInputString = strlen(input);
    strcpy(output, input);  /* Copies null terminator */
    size_t lenghtOutputString = strlen(output);
    
    /* Accumulate 8-bit sum: add each byte value, overflow wraps mod 256 */
    uint8_t checksum8 = 0;
    for (size_t i = 0; i < lenghtInputString; i++) {
        checksum8 += (uint8_t)input[i];  /* Cast ensures byte treatment */
    }
    
    uint8_t sum;
    sum = checksum8;

    /* Convert uint8_t checksum to decimal ASCII digits using division */
    if (sum >= 100) {
        /* Hundreds digit (100-255) */
        output[lenghtOutputString++] = '0' + (sum / 100);
        sum %= 100;
    }
    if (sum >= 10) {
        /* Tens digit */
        output[lenghtOutputString++] = '0' + (sum / 10);
        sum %= 10;
    }
    /* Units digit */
    output[lenghtOutputString++] = '0' + sum;
    
    /* Null-terminate the resulting string */
    output[lenghtOutputString] = '\0';
    
    /* Return computed checksum value for verification */
    return checksum8;
}

int main() {
    char input[16];
    char output[20];
    uint8_t chk;
    
    printf("Enter strings (max 12 chars, '0' to quit):\n");
    
    /* Loop until user enters '0' */
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            /* Handle input read error */
            continue;
        }
        
        /* Remove newline if present */
        input[strcspn(input, "\n")] = 0;
        
        /* Check for quit condition */
        if (strcmp(input, "0") == 0) {
            printf("Goodbye!\n");
            break;
        }
        
        /* Compute checksum and append */
        chk = checksumAppend(input, output);
        
        if (chk != 0) {
            /* Print checksum as decimal integer */
            printf("Checksum: %u\n", chk);
            /* Print new string with appended ASCII decimal checksum */
            printf("Result: '%s'\n\n", output);
        } else {
            printf("Error: Invalid input\n\n");
        }
    }
    
    return 0;
}

