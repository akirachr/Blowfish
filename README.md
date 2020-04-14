# Blowfish

This is a Blowfish (Encription/Decryption) module developed by using C++.<br>
You can freely use this library without any restrictions.<br>
<br>
The application of Console gets your input of the license expirationdate (ex: 2021/05/31), encrypts it, <br>
and stores the encrypted string in the file of license.txt.<br>
The license.txt is created in the same directory where the Console exists.<br>
<br>
The customer of your application places the license.txt in his distribution of application.<br>
And the Blowfish library embedded in your application checks if the expiration date is valid or not.<br>
<br>
Usage:
   1. Place the files below in the currect directory.

      Console.cpp<br>
      LicenseValidator.h<br>
      Makefile

   2. Create the directory below in the current directory.

      lib

   3. Place the files below in the lib directory.

      AlterPWithKey.h<br>
      Blowfish.h<br>
      BlowfishDecipher.h<br>
      BlowfishEncipher.h<br>
      CharLibrary.h<br>
      Common.h<br>
      F.h<br>
      FileLibrary.h<br>
      KeyGenerator.h<br>

   4. Execute the command of make in the directory where the Makefile exists.

      make

   5. Start the application of Console.
      This application creates the license file of license.txt in the same directory.
      You can provide your clients with this license.txt.

      ./Console

   6. Your application can check and validate the license.txt by using the files below.

      ./LicenseValidator.h<br>
      ./lib/AlterPWithKey.h<br>
      ./lib/Blowfish.h<br>
      ./lib/BlowfishDecipher.h<br>
      ./lib/BlowfishEncipher.h<br>
      ./lib/CharLibrary.h<br>
      ./lib/Common.h<br>
      ./lib/F.h<br>
      ./lib/FileLibrary.h<br>
      ./lib/KeyGenerator.h
      
