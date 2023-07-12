#include "MerkelMain.h"
#include <iostream>
#include <algorithm>

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    std::string command;
    std::cout << "Advisorbot> Please enter a command, or help for a list of commands" << std::endl;

    while (true)
    {
        std::cout << "Advisorbot> ";
        std::getline(std::cin, command);

        if (command.empty())
            continue;

        std::istringstream iss(command);
        std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

        if (tokens.empty())
            continue;

        std::string cmd = tokens[0];

        if (cmd == "help")
        {
            if (tokens.size() == 1)
            {
                printHelp();
            }
            else if (tokens.size() == 2)
            {
                printHelpCommand(tokens[1]);
            }
            else
            {
                std::cout << "Invalid command. Usage: help or help <cmd>" << std::endl;
            }
        }
        else if (cmd == "prod")
        {
            listAvailableProducts();
        }
        else if (cmd == "min")
        {
            if (tokens.size() == 3)
            {
                findMinimum(tokens[1], tokens[2]);
            }
            else
            {
                std::cout << "Invalid command. Usage: min product bid/ask" << std::endl;
            }
        }
        else if (cmd == "max")
        {
            if (tokens.size() == 3)
            {
                findMaximum(tokens[1], tokens[2]);
            }
            else
            {
                std::cout << "Invalid command. Usage: max product bid/ask" << std::endl;
            }
        }
        else if (cmd == "avg")
        {
            if (tokens.size() == 4)
            {
                int timesteps = std::stoi(tokens[3]);
                calculateAverage(tokens[1], tokens[2], timesteps);
            }
            else
            {
                std::cout << "Invalid command. Usage: avg product bid/ask timesteps" << std::endl;
            }
        }
        else if (cmd == "predict")
        {
            if (tokens.size() == 3)
            {
                if (tokens[1] == "max")
                {
                    predictMinMax(tokens[2], "bid", true);
                }
                else if (tokens[1] == "min")
                {
                    predictMinMax(tokens[2], "ask", false);
                }
                else
                {
                    std::cout << "Invalid command. Usage: predict max/min product bid/ask" << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid command. Usage: predict max/min product bid/ask" << std::endl;
            }
        }
        else if (cmd == "time")
        {
            displayCurrentTime();
        }
        else if (cmd == "step")
        {
            goToNextTimeStep();
        }
        else if (cmd == "custom")
        {
            processCustomCommand();
        }
        else if (cmd == "optimize")
        {
            optimizeExchangeCode();
        }
        else
        {
            std::cout << "Invalid command. Type 'help' for a list of available commands." << std::endl;
        }
    }
}

void MerkelMain::printHelp()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "  help                           : List all available commands" << std::endl;
    std::cout << "  help <cmd>                     : Output help for the specified command" << std::endl;
    std::cout << "  prod                           : List available products" << std::endl;
    std::cout << "  min <product> <bid/ask>        : Find the minimum bid or ask for a product" << std::endl;
    std::cout << "  max <product> <bid/ask>        : Find the maximum bid or ask for a product" << std::endl;
    std::cout << "  avg <product> <bid/ask> <timesteps> : Compute the average bid or ask for a product over a number of timesteps" << std::endl;
    std::cout << "  predict max <product> <bid/ask>      : Predict the maximum bid or ask for a product in the next time step" << std::endl;
    std::cout << "  predict min <product> <bid/ask>      : Predict the minimum bid or ask for a product in the next time step" << std::endl;
    std::cout << "  time                           : State the current time in the dataset" << std::endl;
    std::cout << "  step                           : Move to the next time step" << std::endl;
    std::cout << "  custom                         : Execute your own custom command" << std::endl;
    std::cout << "  optimize                       : Optimize the exchange code" << std::endl;
}

void MerkelMain::printHelpCommand(const std::string& command)
{
    // Implement help command for each specific command
}

void MerkelMain::listAvailableProducts()
{
    std::vector<std::string> products = orderBook.getKnownProducts();

    std::cout << "Available products:" << std::endl;
    for (const std::string& product : products)
    {
        std::cout << "  " << product << std::endl;
    }
}

void MerkelMain::findMinimum(const std::string& product, const std::string& type)
{
    std::vector<OrderBookEntry> orders = orderBook.getOrders(OrderBookType::stringToOrderBookType(type), product, currentTime);

    if (orders.empty())
    {
        std::cout << "No " << type << " entries found for " << product << " in the current time step." << std::endl;
        return;
    }

    double minPrice = OrderBook::getLowPrice(orders);

    std::cout << "The min " << type << " for " << product << " is " << minPrice << std::endl;
}


void MerkelMain::findMaximum(const std::string& product, const std::string& type)
{
    std::vector<OrderBookEntry> orders = orderBook.getOrders(OrderBookType::stringToOrderBookType(type), product, currentTime);

    if (orders.empty())
    {
        std::cout << "No " << type << " entries found for " << product << " in the current time step." << std::endl;
        return;
    }

    double maxPrice = OrderBook::getHighPrice(orders);

    std::cout << "The max " << type << " for " << product << " is " << maxPrice << std::endl;
}


void MerkelMain::calculateAverage(const std::string& product, const std::string& type, int timesteps)
{
    std::vector<OrderBookEntry> orders;
    std::string timestamp = currentTime;

    for (int i = 0; i < timesteps; i++)
    {
        std::vector<OrderBookEntry> currentOrders = orderBook.getOrders(OrderBookType::stringToOrderBookType(type), product, timestamp);

        if (!currentOrders.empty())
        {
            orders.insert(orders.end(), currentOrders.begin(), currentOrders.end());
        }

        timestamp = orderBook.getNextTime(timestamp);
    }

    if (orders.empty())
    {
        std::cout << "No " << type << " entries found for " << product << " over the specified number of time steps." << std::endl;
        return;
    }

    double total = 0.0;
    for (const OrderBookEntry& order : orders)
    {
        total += order.price;
    }

    double average = total / orders.size();

    std::cout << "The average " << product << " " << type << " price over the last " << timesteps << " timesteps was " << average << std::endl;
}


void MerkelMain::predictMinMax(const std::string& product, const std::string& type, bool isMax)
void MerkelMain::predictMinMax(const std::string& product, const std::string& type, bool isMax)
{
    std::vector<OrderBookEntry> currentOrders = orderBook.getOrders(OrderBookType::stringToOrderBookType(type), product, currentTime);

    if (currentOrders.empty())
    {
        std::cout << "No " << type << " entries found for " << product << " in the current time step." << std::endl;
        return;
    }

    double prediction = 0.0;

    // Perform prediction using an appropriate algorithm
    // For example, using moving average
    double sum = 0.0;
    int count = 0;
    for (const OrderBookEntry& order : currentOrders)
    {
        sum += order.price;
        count++;
    }

    if (count > 0)
    {
        double average = sum / count;
        prediction = isMax ? average + 0.1 : average - 0.1;
    }

    std::string predictionType = isMax ? "max" : "min";

    std::cout << "The " << predictionType << " " << type << " for " << product << " in the next time step might be " << prediction << std::endl;
}

void MerkelMain::displayCurrentTime()
{
    std::cout << "Current time: " << currentTime << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "Now at " << currentTime << std::endl;
}


void MerkelMain::processCustomCommand()
{
    // Implement your own custom command
}

void MerkelMain::optimizeExchangeCode()
{
    // Implement optimizing the exchange code
}
