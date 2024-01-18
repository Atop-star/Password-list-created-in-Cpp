std::string generatePassword(int length, int alphaPercentage, int numeralPercentage, int specialPercentage) {
    const std::string alphabets = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string numerals = "0123456789";
    const std::string specialChars = "!@#$%^&*()-=_+[]{}|;:',.<>?";
    
    std::string password;

    for (int i = 0; i < length; ++i) {
        int choice = rand() % 100; // Random number between 0 and 99

        if (choice < alphaPercentage) {
            char selectedChar = alphabets[rand() % alphabets.length()];
            if (islower(selectedChar)) {
                password += selectedChar;
            } else {
                // If uppercase is selected, ensure previous character is not uppercase
                if (i == 0 || islower(password.back())) {
                    password += selectedChar;
                } else {
                    --i; // Retry selecting alpha character without duplicating casing
                }
            }
        } else if (choice < alphaPercentage + numeralPercentage) {
            password += numerals[rand() % numerals.length()];
        } else {
            password += specialChars[rand() % specialChars.length()];
        }
    }

    return password;
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    const int numPasswords = 10000;
    const int passwordLength = 10;
    const int alphaPercentage = 40;
    const int numeralPercentage = 30;
    const int specialPercentage = 30;
    const std::string defaultFilename = "passwords.txt";

    // Generate passwords
    std::ofstream outputFile(defaultFilename);
    if (outputFile.is_open()) {
        for (int i = 0; i < numPasswords; ++i) {
            outputFile << generatePassword(passwordLength, alphaPercentage, numeralPercentage, specialPercentage) << std::endl;
        }
        outputFile.close();
        std::cout << "Passwords saved to " << defaultFilename << std::endl;

        // Ask user for destination path
        std::string destinationPath;
        std::cout << "Enter destination path for download (including filename): ";
        std::cin >> destinationPath;

        // Copy the file to the specified destination
        std::ifstream src(defaultFilename, std::ios::binary);
        std::ofstream dest(destinationPath, std::ios::binary);
        dest << src.rdbuf();

        std::cout << "File downloaded to " << destinationPath << std::endl;
    } else {
        std::cerr << "Unable to open file: " << defaultFilename << std::endl;
    }

    return 0;
}
