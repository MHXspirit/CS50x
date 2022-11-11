#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validate(int argc, string key);
string encipher(string plaintext, string key);

int main(int argc, string argv[])
{
    int result = validate(argc, argv[1]);

    if (result == 1)
    {
        return 1;
    }
    else
    {
        string plaintext = get_string("plaintext: ");
        string ciphertext = encipher(plaintext, argv[1]);
        printf("ciphertext: %s\n", ciphertext);
    }

    return 0;
}

int validate(int argc, string key)
{
    int alphabetic[26] = {0};

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < 26; i ++)
        {
            key[i] = toupper(key[i]);

            if (key[i] > 'Z' || key[i] < 'A')
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }

            alphabetic[key[i] - 'A'] ++;
            if (alphabetic[key[i] - 'A'] > 1)
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    return 0;
}

string encipher(string plaintext, string key)
{
    string ciphertext = plaintext;
    for (int i = 0, n = strlen(ciphertext); i < n; i ++)
    {
        if (islower(ciphertext[i]))
        {
            ciphertext[i] = tolower(key[ciphertext[i] - 'a']);
        }
        else if (isupper(ciphertext[i]))
        {
            ciphertext[i] = toupper(key[ciphertext[i] - 'A']);
        }
    }

    return ciphertext;
}