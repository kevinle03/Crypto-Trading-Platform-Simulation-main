#include "Wallet.h"
#include <iostream>

Wallet::Wallet()
{
    
}

void Wallet::insertCurrency(std::string type, double amount)
{
    if (amount < 0)
    {
        throw std::invalid_argument("Amount must be positive");
    }
    if (currencies.count(type) == 0)
    {
        currencies[type] = 0;
    }

    currencies[type] += amount;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (containsCurrency(type, amount))
    {
        currencies[type] -= amount;
        return true;
    }
    return false;
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    if (amount < 0)
        throw std::invalid_argument("Amount must be positive");

    if (currencies.count(type) == 0)
        return false;
    if (currencies[type] >= amount)
        return true;

    return false;
}

std::string Wallet::toString()
{
    std::string s;

    s += "Currencies:\n";
    if (currencies.size() == 0)
        s += "Your currencies wallet is empty.\n";

    for (std::pair<std::string, double> pair : currencies)
    {
        s += pair.first + ": " + std::to_string(pair.second) + "\n";
    }

    s += "\nPending Currencies:\n";
    if (pending_currencies.size() == 0)
        s += "You have no coins on hold.\n";
    for (std::pair<std::string, double> pair : pending_currencies)
    {
        s += pair.first + ": " + std::to_string(pair.second) + "\n";
    }

    s += "\nPending orders:\n";
    if (pending_order.size() == 0)
        s += "You have no pending orders.\n";
    for (std::string order : pending_order)
    {
        s += order + "\n";
    }
    return s;
}

void Wallet::insertPendingOrder(std::string order)
{
    pending_order.push_back(order);
}

std::ostream& operator<<(std::ostream& os, Wallet& wallet)
{
    os << wallet.toString();
    return os;
}