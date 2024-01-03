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
    if (currencies.size() == 0)
        return "Your wallet is empty.";
    std::string s;
    for (std::pair<std::string, double> pair : currencies)
    {
        s += pair.first + ": " + std::to_string(pair.second) + "\n";
    }
    return s;
}

std::ostream& operator<<(std::ostream& os, Wallet& wallet)
{
    os << wallet.toString();
    return os;
}