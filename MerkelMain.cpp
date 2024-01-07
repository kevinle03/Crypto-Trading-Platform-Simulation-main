#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <limits>

MerkelMain::MerkelMain()
{


}

void MerkelMain::init()
{
    wallet.insertCurrency("BTC", 10);
    wallet.insertCurrency("USDT", 15000);
    wallet.insertCurrency("ETH", 30);
    currentTime = orderBook.getEarliestTime();
    int input;
    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
        std::cout << "============== " << std::endl;
        std::cout<<"Press Enter to continue"<<std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

void MerkelMain::printMenu()
{
    std::cout << "============== " << std::endl;
    std::cout << "Current time: " << currentTime<< std::endl;
    std::cout << "============== " << std::endl;
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make a trade
    std::cout << "3: Make a trade " << std::endl;
    // 4 print wallet
    std::cout << "4: Print wallet " << std::endl;
    // 5 continue   
    std::cout << "5: Continue " << std::endl;

    std::cout << "============== " << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (const std::string &p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;

        std::vector<OrderBookEntry> entries_ask = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Asks seen: " << entries_ask.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries_ask) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries_ask) << std::endl;

        std::vector<OrderBookEntry> entries_bid = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        std::cout << "Bids seen: " << entries_bid.size() << std::endl;
        std::cout << "Max bid: " << OrderBook::getHighPrice(entries_bid) << std::endl;
        std::cout << "Min bid: " << OrderBook::getLowPrice(entries_bid) << "\n" << std::endl;
    }
}

void MerkelMain::makeTrade()
{
    try
    {
        std::cout << "Make a trade" << std::endl;
        std::cout<< "Enter product 1 (you want to buy, eg. ETH, BTC, DOGE, USDT): ";
        std::string prod1;
        std::getline(std::cin, prod1);

        if (!(prod1 == "ETH" || prod1 == "BTC" || prod1 == "DOGE" || prod1 == "USDT")) 
        {
            std::cout<< "The product you entered is either invalid or not available." << std::endl;
            return;
        }
        
        std::cout<< "Enter product 2 (you want to sell, eg. ETH, BTC, DOGE, USDT): ";
        std::string prod2;
        std::getline(std::cin, prod2);

        if (!(prod2 == "ETH" || prod2 == "BTC" || prod2 == "DOGE" || prod2 == "USDT")) 
        {
            std::cout<< "The product you entered is either invalid or not available." << std::endl;
            return;
        }

        if (prod1 == prod2) 
        {
            std::cout<< "Product 1 and 2 cannot be the same." <<std::endl;
            return;
        }
        if ((prod1 == "ETH" || prod1 == "DOGE") && (prod2 == "ETH" || prod2 == "DOGE")) 
        {
            std::cout<< "You can not trade ETH and DOGE directly" <<std::endl;
            return;
        }

        if (!(wallet.containsCurrency(prod2,0))) 
        {
            std::cout<<"You have 0 " << prod2 << " in your wallet." <<std::endl;
            return;
        }
        
        std::cout<< "Enter price (how much of product 2 for one quanity of product 1): ";
        std::string price;
        std::getline(std::cin, price);

        std::cout<< "Enter amount (how much of product 1 you want to buy): ";
        std::string amount;
        std::getline(std::cin, amount);

        double price_double = std::stod(price);
        double amount_double = std::stod(amount);

        if (!(wallet.containsCurrency(prod2,(price_double*amount_double)))) 
        {
            std::cout << "You do not have enough " << prod2 << "." <<std::endl;
            return;
        }

        std::string product;
        OrderBookType orderType;

        if (prod1 == "USDT" || prod1 == "BTC") 
        {
            if (!(prod2 == "USDT")) 
            {
                orderType = OrderBookType::ask;
                product = prod2 + "/" + prod1;
            
                double amount_flip = amount_double * price_double;
                double price_flip = 1/price_double;
                price = std::to_string(price_flip);
                amount = std::to_string(amount_flip);
            }
        }

        if (!(prod1 == "USDT" || prod1 == "BTC") || prod1 == "BTC" && prod2 == "USDT") 
        {
            orderType = OrderBookType::bid;
            product = prod1 + "/" + prod2;
        }
        
        OrderBookEntry obe = CSVReader::stringsToOBE(
            price,
            amount,
            currentTime,
            product,
            orderType);
        orderBook.insertOrder(obe);

        wallet.removeCurrency(prod2, price_double*amount_double);
        wallet.insertPendingCurrency(prod2, price_double*amount_double);

        std::string order = price+","+amount+","+currentTime+","+product+","+((orderType == OrderBookType::ask)?"ask":"bid");
        wallet.insertPendingOrder(order);

    }
    catch(const std::exception& e)
    {
        std::cout<<"The ask that you entered is not formatted correctly." <<std::endl;
    }
    
}

void MerkelMain::printWallet()
{
    std::cout<<wallet.toString()<<std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() <<std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << ", Amount: " <<sale.amount << std::endl;
        }
    }
    wallet.clearPendingOrder();
    //currentTime = orderBook.getNextTime(currentTime);
}
 
int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;

    std::cout << "Type in 1-5" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userOption = std::stoi(line);
    }
    catch(const std::exception& e)
    {
    }
    
    std::cout << "You chose: " << userOption << std::endl;
    std::cout << "============== " << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption <= 0 || userOption >= 6) // bad input
    {
        std::cout << "Invalid choice. Choose 1-5" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printMarketStats();
    }
    if (userOption == 3) 
    {
        makeTrade();
    }
    if (userOption == 4) 
    {
        printWallet();
    }
    if (userOption == 5) 
    {
        gotoNextTimeframe();
    }       
}
 
