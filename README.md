# Fake Bitcoin Wallet Checker

This is a fake wallet miner that can be used for educational or testing purposes. It simulates the process of mining new blocks and adding them to a blockchain.

## Installation

1. Clone the repository: `git clone https://github.com/dynastyoak/Fake-wallet-miner-cpp.git`
2. Install the required dependencies: `sudo apt-get install libcurl4-openssl-dev`
3. Compile the program: `g++ -o btc_wallet_checker btc_wallet_checker.cpp -lcurl`

## Usage

1. Run the program: `./btc_wallet_checker`
2. Enter your license key when prompted.
3. Enter the Bitcoin wallet address you want to check.
4. The program will generate a random Bitcoin address and check its balance using the Coinbase API.
5. If the address has a balance, the program will display the balance in USD and BTC.

## Credits

This program was created by DynastyOak.


