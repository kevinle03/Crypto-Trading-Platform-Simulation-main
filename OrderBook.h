#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>
#include "Wallet.h"

class OrderBook
{
    public:
    /** construct, reading a csv data file*/
    OrderBook(std::string filename);

    /** return vector of all known products in the dataset*/
    std::vector<std::string> getKnownProducts();

    /** return vector of pointer to Orders according to the sent filters*/
    std::vector<OrderBookEntry*> getOrdersPointers(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);

    /** return vector of Orders according to the sent filters*/
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);                                 

    std::string getEarliestTime();  

    std::string getNextTime(const std::string& timestamp);                                

    /** return the price of the highest bid in the sent set*/
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    
    /** return the price of the lowest bid in the sent set*/
    static double getLowPrice(std::vector<OrderBookEntry>& orders);        

    static double getMeanPrice(std::vector<OrderBookEntry>& orders);   

    void insertOrder(OrderBookEntry& order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp, Wallet& wallet);

    private:
        std::vector<OrderBookEntry> orders;                           
};