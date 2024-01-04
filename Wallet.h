#pragma once
#include <string>
#include <map>
#include <vector>

class Wallet
{
    public:
        Wallet();

        /** insert currency to the wallet */
        void insertCurrency(std::string type, double amount);

        /** remove currency from the wallet */
        bool removeCurrency(std::string type, double amount);

        /** insert to pending currencies of the wallet */
        void insertPendingCurrency(std::string type, double amount);

        /** remove from pending currencies of the wallet */
        void removePendingCurrency(std::string type, double amount);

        /** check if the wallet contains this much currency or more */
        bool containsCurrency(std::string type, double amount);

        /** generate a string representation of the wallet */
        std::string toString();

        /** add a pending order*/
        void insertPendingOrder(std::string order);

        /** clear all items in pending orders*/
        void clearPendingOrder();

        friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

    private:
        std::map<std::string, double> currencies;
        std::map<std::string, double> pending_currencies;
        std::vector<std::string> pending_order;
};