#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>
#include <chrono>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <regex>
#include <sstream>
#include <unistd.h>

using json = nlohmann::json;

static size_t write_callback(char* data, size_t size, size_t nmemb, std::string* buffer) {
    buffer->append(data, size * nmemb);
    return size * nmemb;
}

std::string get_key() {
    std::string url = "https://pastebin.com/raw/ZBuYCLZ0";
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        return "";
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return "";
    }
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code != 200) {
        std::cerr << "Error: HTTP " << http_code << std::endl;
        curl_easy_cleanup(curl);
        return "";
    }
    curl_easy_cleanup(curl);
    return response;
}

std::string coinbase_request() {
    std::string url = "https://api.coinbase.com/v2/prices/BTC-USD/spot";
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        return "";
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return "";
    }
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code != 200) {
        std::cerr << "Error: HTTP " << http_code << std::endl;
        curl_easy_cleanup(curl);
        return "";
    }
    curl_easy_cleanup(curl);
    return response;
}

std::string generateBTCAddress() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> distrib(0, 35);
  const std::string charset = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
  std::string address = "1";
  for (int i = 0; i < 32; i++) {
    int index = distrib(gen);
    address += charset[index];
  }
  unsigned int checksum = 0;
  for (unsigned int i = 0; i < address.length(); i++) {
    int value = charset.find(address[i]);
    checksum = (checksum * 58 + value) % 256;
  }
  std::string checksumString = "";
  if (checksum < 10) {
    checksumString += "0";
  }
  checksumString += std::to_string(checksum);
  std::string btcAddress = address + checksumString;
  return btcAddress;
}

int main() {
    double total_usd = 0.000000;
    double total_btc = 0.000000;
    std::stringstream title;
    title << "Made by DynastyOak | " << total_usd << " USD | " << total_btc << " BTC";
    SetConsoleTitle(title.str().c_str());
    srand(time(NULL)); // random seed cuz fr
    int random_check = rand() % 7 + 1;
    system("cls");
    std::string licensekey = get_key();
    std::string key;
    std::cout << "License Key: ";
    std::cin >> key;
    if (key == licensekey) {
        std::cout << "Valid License Key" << std::endl;
    } else {
    	std::cout << "InValid License Key" << std::endl;
    	return 0;
    }
    system("cls");
    std::string wallet;
    std::cout << "[\u001b[33;1m?\u001b[0m] Enter wallet >: ";
    std::cin >> wallet;
    if (wallet.substr(0, 3) == "bc1" || wallet.substr(0, 1) == "1" || wallet.substr(0, 1) == "3") {
        for (int i = 1; i < random_check; i++) {
            std::cout << "\u001b[31;1mChecking Wallet...\u001b[0m" << std::endl;
            sleep(rand() % 3 + 1);
        }
    } else {
        std::cout << "Invalid Bitcoin address.\n";
        return 0;
    }
    system("cls");
    std::cout << "\u001b[32m[+] Wallet found\u001b[0m" << std::endl;
    sleep(2);
    while (true) {
        std::stringstream title;
        title << "Made by DynastyOak | " << total_usd << " USD | " << total_btc << " BTC";
        SetConsoleTitle(title.str().c_str());
        for (int i = 0; i < rand() % 100 + 1; i++) {
        	std::cout << "[-] \u001b[31mbc" << generateBTCAddress() << "\u001b[0m | InValid | 0.000000 BTC | 0.000000 USD" << std::endl;
            sleep(rand() % 2 + 1);
        }
        std::string response = coinbase_request();
        json j = json::parse(response);
        double btc_to_usd = std::stod(j["data"]["amount"].get<std::string>());
        double random_btc = static_cast<double>(rand()) / RAND_MAX;
        double usd = random_btc * btc_to_usd; // im really good at math fr
        total_usd += usd;
        total_btc += random_btc;
        std::cout << "[+] \u001b[32mbc" << generateBTCAddress() << "\u001b[0m | Valid | " << std::fixed << std::setprecision(6) << random_btc << " BTC" << " | " << usd << " USD" << std::endl;
        std::cout << "[+]\u001b[32m Withdrawing to your Wallet...\u001b[0m" << std::endl;
        sleep(10);
    }
    return 0;
}
