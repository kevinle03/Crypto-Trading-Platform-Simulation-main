#include "OrderBook.h"
#include <map>
#include <algorithm>


OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string,bool> prodMap;
    for(const OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }
    for (const std::pair<std::string,bool>& productStringBoolPair : prodMap)
    {
        products.push_back(productStringBoolPair.first);
    }

    return products;
}

std::vector<OrderBookEntry*> OrderBook::getOrdersPointers(OrderBookType type,
                                      std::string product,
                                      std::string timestamp)
{
    std::vector<OrderBookEntry*> matchingOrders;
    for (OrderBookEntry& e : orders)
    {
        if (type == e.orderType &&
            product == e.product &&
            timestamp == e.timestamp)
        {
            matchingOrders.push_back(&e);
        }
    }

    return matchingOrders;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                      std::string product,
                                      std::string timestamp)
{
    std::vector<OrderBookEntry> matchingOrders;
    for (OrderBookEntry& e : orders)
    {
        if (type == e.orderType &&
            product == e.product &&
            timestamp == e.timestamp)
        {
            matchingOrders.push_back(e);
        }
    }

    return matchingOrders;
}    

std::string OrderBook::getEarliestTime()
{
    std::string earliestTime = orders[0].timestamp;
    for (const OrderBookEntry& e : orders)
    {
        if (e.timestamp < earliestTime)
        {
            earliestTime = e.timestamp;
        }
    }
    return earliestTime;
} 

std::string OrderBook::getNextTime(const std::string& timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry &e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = getEarliestTime();
    }

    return next_timestamp;
}                            


double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double max = orders[0].price;
    for (const OrderBookEntry& e : orders)
    {
        if (e.price > max)
        {
            max = e.price;
        }
    }

    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    double min = orders[0].price;
    for (const OrderBookEntry& e : orders)
    {
        if (e.price < min)
        {
            min = e.price;
        }
    }

    return min;
}

/** takes a vector of OrderBookEntry and returns the average price as a double*/
double OrderBook::getMeanPrice(std::vector<OrderBookEntry>& orders)
{
    double priceTimesAmount = 0.0;
    double totalAmount = 0.0;
    for (const OrderBookEntry &e : orders)
    {
        priceTimesAmount += (e.price * e.amount);
        totalAmount += e.amount;
    }
    return priceTimesAmount/totalAmount;
}

void OrderBook::insertOrder(OrderBookEntry &order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry*> asks = getOrdersPointers(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry*> bids = getOrdersPointers(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    for (OrderBookEntry* ask : asks)
    {
        for (OrderBookEntry* bid : bids)
        {
            if ((*bid).price >= (*ask).price)
            {
                OrderBookEntry sale{(*ask).price, 0, timestamp, product, OrderBookType::sale};
                if ((*bid).amount == (*ask).amount)
                {
                    sale.amount = (*ask).amount;
                    sales.push_back(sale);
                    (*bid).amount = 0;
                    break;
                }
                if ((*bid).amount > (*ask).amount)
                {
                    sale.amount = (*ask).amount;
                    sales.push_back(sale);
                    (*bid).amount = (*bid).amount - (*ask).amount;
                    break;
                }
                if ((*bid).amount < (*ask).amount)
                {
                    sale.amount = (*bid).amount;
                    sales.push_back(sale);
                    (*ask).amount = (*ask).amount - (*bid).amount;
                    (*bid).amount = 0;
                    continue;
                }
            }
        }
    }
    return sales;
}