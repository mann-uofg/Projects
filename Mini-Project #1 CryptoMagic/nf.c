#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encrypt(char *filename) {
  char *hex;
  hex = malloc(3 * sizeof(char));
  if (hex == NULL) {
    printf("Cannot allocate memory for hex buffer.\n");
    return 1;
  }

  FILE *fp1;
  fp1 = fopen(filename, "rb");
  if (fp1 == NULL) {
    printf("Cannot open file: %s\n", filename);
    return 1;
  }

  FILE *fp2;
  char encrypted_filename[256];
  sprintf(encrypted_filename, "%s.crp", filename);
  fp2 = fopen(encrypted_filename, "w");
  if (fp2 == NULL) {
    printf("Cannot open file: %s\n", encrypted_filename);
    return 1;
  }

  int ch;
  while ((ch = fgetc(fp1)) != EOF) {
    if (ch == 10) { // newline character
      fputs("TT", fp2); // add a special character to the encrypted text
    } else {
      int ascii = ch;

      int outChar = ascii - 16;
      if (outChar < 32) {
        outChar = (outChar - 32) + 144;
      }

      sprintf(hex, "%X", outChar);

      fputs(hex, fp2);
    }
  }

  fclose(fp1);
  fclose(fp2);

  free(hex);

  return 0;
}

int decrypt(char *filename) {
  char *hex;
  hex = malloc(2 * sizeof(char));
  if (hex == NULL) {
    printf("Cannot allocate memory for hex buffer.\n");
    return 1;
  }

  FILE *fp1;
  fp1 = fopen(filename, "r");
  if (fp1 == NULL) {
    printf("Cannot open file: %s\n", filename);
    return 1;
  }

  char decrypted_filename[256];
  strcpy(decrypted_filename, filename);
  char *ext = strrchr(decrypted_filename, '.');
  if (ext != NULL) {
    *ext = '\0';
  }
  strcat(decrypted_filename, ".txt");

  FILE *fp2;
  fp2 = fopen(decrypted_filename, "w");
  if (fp2 == NULL) {
    printf("Cannot open file: %s\n", decrypted_filename);
    return 1;
  }

  int c1, c2;
  int isNewline = 0;
  while (1) {
    c1 = fgetc(fp1);
    if (c1 == EOF) {
      break;
    }

    c2 = fgetc(fp1);
    if (c2 == EOF) {
      break;
    }

    hex[0] = c1;
    hex[1] = c2;
    hex[2] = '\0';

    if (strcmp(hex, "TT") == 0) {
      if (isNewline) {
        isNewline = 0;
      } else {
        fputc(10, fp2); // Handle newline character
        isNewline = 1;
      }
    } else {
      int outChar;
      sscanf(hex, "%x", &outChar);

      outChar = outChar + 16;
      if (outChar > 127) {
        outChar = (outChar - 144) + 32;
      }

      fputc(outChar, fp2);
    }
  }

  fclose(fp1);
  fclose(fp2);

  free(hex);

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s [-E|-D] filename\n", argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "-E") == 0) {
    encrypt(argv[2]);
  } else if (strcmp(argv[1], "-D") == 0) {
    decrypt(argv[2]);
  } else {
    printf("Invalid command-line option: %s\n", argv[1]);
    return 1;
  }

  return 0;
}
