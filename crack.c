#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings

void trim(char input[]);

// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    trim(plaintext);
    char *targetHash = md5(plaintext, strlen(plaintext));
    //printf("%s\n", targetHash);

    // Open the hash file
    FILE *hashFile = fopen(hashFilename, "r");
    if (hashFile == NULL)
    {
        printf("Could not open file %s.\n", hashFilename);
        exit(1);
    }

    // Loop through the hash file, one line at a time.

    // Attempt to match the hash from the file to the
    // hash of the plaintext.

    // If there is a match, you'll return the hash.
    // If not, return NULL.
    
    char hash[255];
    int hashFound = 0;
    while (hashFound == 0 && fgets(hash, 255, hashFile) != NULL)
    {
        // remove the newline
        trim(hash);

        // hash
        if (strcmp(hash, targetHash) == 0)
        {
            hashFound = 1;
        }
    }

    // Before returning, do any needed cleanup:
    
    fclose(hashFile);
    free(targetHash);

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    if (hashFound)
        return hash;
    else
        return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // Open the dictionary file for reading.
    FILE *dictFile = fopen(argv[2], "r");
    if (dictFile == NULL)
    {
        printf("Could not open file %s.\n", argv[2]);
        exit(1);
    }
    
    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    int hashCount = 0;
    char word[255];
    while (fgets(word, 255, dictFile) != NULL)
    {
        // remove the newline
        trim(word);
        char *hash = tryWord(word, argv[1]);
        if (hash != NULL)
        {
            // If we got a match, display the hash and the word. For example:
            // 5d41402abc4b2a76b9719d911017c592 hello

            // also i don't know why, but 50% of the time it will not print the first hash
            // and the other 50% of the time it will. no idea how to diagnose that
            hashCount++;
            printf("%s %s\n", hash, word);
        }
    }
    
    // Close the dictionary file.
    fclose(dictFile);

    // Display the number of hashes that were cracked.
    printf("%d hashes cracked!", hashCount);
}

void trim(char input[])
{
    // change the newline to the null character
    for (int i = 0; i < strlen(input); i++)
        if (input[i] == '\n')
            input[i] = '\0';
}