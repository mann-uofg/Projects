cryptoMagic

Input

The Program takes two command-line arguments:

•	-E or -D : Specifies whether to encrypt or decrypt the file.
•	filename: The name of the file to encrypt or decrypt.

If the -E flag is specified, the program will encrypt the file and produce an encrypted file with the same base filename and a .crp file extension. If the -D flag is specified, the program will decrypt the file and produce a decrypted file with the same base filename and a .txt file extension.

Output

The Program produces an encrypted or decrypted file, depending on the command-line argument that is specified.

Example

To encrypt the file encp.txt, run the following command:

./cryptoMagic -E encp.txt

This will create an encrypted file called ‘encp.crp’.
To decrypt the encrypted file, run the following command:

./cryptoMagic -D encp.crp

This will create a new file called ‘decp.txt’ that contains the decrypted text. 
