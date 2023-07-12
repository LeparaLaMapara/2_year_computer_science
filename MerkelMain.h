#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

// class MerkelMain
// {
//     public:
//         MerkelMain();
//         /** Call this to start the sim */
//         void init();
//     private: 
//         void printMenu();
//         void printHelp();
//         void printMarketStats();
//         void enterAsk();
//         void enterBid();
//         void printWallet();
//         void gotoNextTimeframe();
//         int getUserOption();
//         void processUserOption(int userOption);

//         std::string currentTime;

//         OrderBook orderBook{"20200317.csv"};

// };

class MerkelMain
{
public:
    MerkelMain();
    void init();

private:
    void printMenu();
    void printHelp();
    void printHelpCommand(const std::string& command);
    void listAvailableProducts();
    void findMinimum(const std::string& product, const std::string& type);
    void findMaximum(const std::string& product, const std::string& type);
    void calculateAverage(const std::string& product, const std::string& type, int timesteps);
    void predictMinMax(const std::string& product, const std::string& type, bool isMax);
    void displayCurrentTime();
    void goToNextTimeStep();
    void processCustomCommand();
    void optimizeExchangeCode();

    std::string currentTime;

    OrderBook orderBook{"20200317.csv"};
};
