#include <iostream>
#include <string>
#include <unordered_map>
#include <iostream>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>

using namespace CryptoPP;

class BankingSystem {
private:
    std::unordered_map<std::string, std::string> userCredentials;

public:
    BankingSystem() {
        userCredentials["user1"] = "salt1";
        userCredentials["user2"] = "salt2";
    }

    bool authenticateUser(const std::string& username, const std::string& password) {
        if (userCredentials.find(username) != userCredentials.end()) {
            const std::string& salt = userCredentials[username];
            std::string hashedPassword = hashPassword(password, salt);

            if (userCredentials[username] == hashedPassword) {
                std::cout << "Authentication successful. Welcome, " << username << "!\n";
                return true;
            } else {
                std::cout << "Incorrect password. Authentication failed.\n";
            }
        } else {
            std::cout << "User not found. Authentication failed.\n";
        }
        return false;
    }

private:
    std::string hashPassword(const std::string& password, const std::string& salt) {
        SHA256 hash;
        std::string saltedPassword = salt + password;

        byte digest[SHA256::DIGESTSIZE];
        hash.CalculateDigest(digest, reinterpret_cast<byte*>(&saltedPassword[0]), saltedPassword.size());

        HexEncoder encoder;
        std::string hashedPassword;
        encoder.Attach(new StringSink(hashedPassword));
        encoder.Put(digest, sizeof(digest));
        encoder.MessageEnd();

        return hashedPassword;
    }
};

int main() {
    BankingSystem bankingSystem;
    std::string username, password;

    std::cout << "Welcome to the Banking System\n";

    while (true) {
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        if (bankingSystem.authenticateUser(username, password)) {
            break;
        }

        std::cout << "Do you want to try again? (yes/no): ";
        std::string choice;
        std::cin >> choice;

        if (choice != "yes") {
            break;
        }
    }

    std::cout << "Thank you for using the Banking System.\n";
    return 0;
}
