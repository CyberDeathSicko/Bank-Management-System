#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <regex>

class Firewall {
public:
    Firewall() {}

    void addRule(const std::string& rule) {
        rules.push_back(rule);
    }

    bool isTrafficAllowed(const std::string& ipAddress, int port) {
        for (const std::string& rule : rules) {
            if (matchesRule(rule, ipAddress, port)) {
                return true;
            }
        }
        return false;
    }

private:
    std::vector<std::string> rules;

    bool matchesRule(const std::string& rule, const std::string& ipAddress, int port) {
        std::regex rulePattern(R"((\d+\.\d+\.\d+\.\d+):(\d+))");
        std::smatch match;

        if (std::regex_match(rule, match, rulePattern)) {
            std::string ruleIP = match[1].str();
            int rulePort = std::stoi(match[2]);

            if (ipAddress.find(ruleIP) == 0 && port == rulePort) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    Firewall firewall;

    firewall.addRule("192.168.0.1:80");
    firewall.addRule("10.0.0.5:443");
    firewall.addRule("203.0.113.0:22");
    firewall.addRule("0.0.0.0:0");

    struct Traffic {
        std::string ipAddress;
        int port;
    };

    std::vector<Traffic> testTraffic = {
        {"192.168.0.1", 80},
        {"10.0.0.5", 443},
        {"203.0.113.0", 22},
        {"8.8.8.8", 53}
    };

    for (const Traffic& t : testTraffic) {
        if (firewall.isTrafficAllowed(t.ipAddress, t.port)) {
            std::cout << "Traffic from " << t.ipAddress << " on port " << t.port << " is allowed." << std::endl;
        } else {
            std::cout << "Traffic from " << t.ipAddress << " on port " << t.port << " is blocked." << std::endl;
        }
    }

    return 0;
}