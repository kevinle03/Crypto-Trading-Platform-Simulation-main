#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "OrderBook.h"
#include "Wallet.h"

int main()
{
    Wallet wallet{};
    wallet.insertCurrency("BTC", 10);

    MerkelMain start{};
    start.init();
}


    // Wallet wallet{};
    // std::cout << "Printing wallet before inserting currency:" << std::endl;
    // std::cout << wallet << std::endl;

    // wallet.insertCurrency("BTC", 1.5);

    // std::cout << "Printing wallet after inserting 1.5 BTC:" << std::endl;
    // std::cout << wallet << std::endl;
    
    // wallet.insertCurrency("BTC", 5.0);

    // std::cout << "Printing wallet after inserting an additional 5 BTC:" << std::endl;
    // std::cout << wallet << std::endl;

    // std::cout << "Inserting a negative amount:" << std::endl;
    // wallet.insertCurrency("BTC", -4.0);

    //---------------------------------------------------------------
    //     Wallet wallet{};
    // std::cout << "Printing wallet before:" << std::endl;
    // std::cout << wallet << std::endl;

    // std::cout << "*Trying to remove 3 BTC from an empty wallet*" << std::endl;
    // std::cout << "Function returns (0 if false, 1 if true): " << wallet.removeCurrency("BTC", 3.0) << std::endl;

    // std::cout << "Printing wallet after:" << std::endl;
    // std::cout << wallet << std::endl;

    // std::cout << "*Adding 2 BTC*" << std::endl;
    // wallet.insertCurrency("BTC", 2);

    // std::cout << "Printing wallet after adding 2 BTC:" << std::endl;
    // std::cout << wallet << std::endl;

    // std::cout << "*Trying to remove 3 BTC from a wallet with 2 BTC*" << std::endl;
    // std::cout << "Function returns (0 if false, 1 if true): " << wallet.removeCurrency("BTC", 3.0) << std::endl;

    // std::cout << "Printing wallet after trying to remove 3 BTC:" << std::endl;
    // std::cout << wallet << std::endl;

    // std::cout << "*Adding another 2 BTC*" << std::endl;
    // wallet.insertCurrency("BTC", 2);

    // std::cout << "Printing wallet after adding another 2 BTC:" << std::endl;
    // std::cout << wallet << std::endl;

    // std::cout << "*Trying to remove 3 BTC from a wallet with 4 BTC*" << std::endl;
    // std::cout << "Function returns (0 if false, 1 if true): " << wallet.removeCurrency("BTC", 3.0) << std::endl;

    // std::cout << "Printing wallet after trying to remove 3 BTC:" << std::endl;
    // std::cout << wallet << std::endl;

    // std::cout << "Amount is less than 0:" << std::endl;
    // wallet.removeCurrency("BTC", -3.0);



//     std::vector<OrderBookEntry> orders;

//     orders.push_back(  OrderBookEntry{1000, 
//                           0.02, 
//                         "2020/03/17 17:01:24.884492", 
//                         "BTC/USDT", 
//                         OrderBookType::bid}    );

//     orders.push_back(  OrderBookEntry{2000, 
//                           0.02, 
//                         "2020/03/17 17:01:24.884492", 
//                         "BTC/USDT", 
//                         OrderBookType::bid}    );
        

//    // std::cout << "The price is " << orders[1].price << std::endl;

//     for (OrderBookEntry& order : orders)
//     {
//         std::cout << "The price is " << order.price << std::endl;
//     }

//     for (unsigned int i = 0; i < orders.size() ; ++i)
//     {
//         std::cout << "The price is " << orders[i].price << std::endl;
//     }

//     for (unsigned int i = 0; i < orders.size() ; ++i)
//     {
//         std::cout << "The price is " << orders.at(i).price << std::endl;
//     }




 
