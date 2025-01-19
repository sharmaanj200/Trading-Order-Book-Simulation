#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>

struct Order {
    int id;
    std::string type; // "buy" or "sell"
    double price;
    int quantity;
    unsigned long timestamp;

    Order(int id, const std::string& type, double price, int quantity, unsigned long timestamp)
        : id(id), type(type), price(price), quantity(quantity), timestamp(timestamp) {}
};

// Comparator for Buy Orders (max-heap based on price, min timestamp for tie)
struct BuyComparator {
    bool operator()(const Order& a, const Order& b) {
        return (a.price < b.price) || (a.price == b.price && a.timestamp > b.timestamp);
    }
};

// Comparator for Sell Orders (min-heap based on price, min timestamp for tie)
struct SellComparator {
    bool operator()(const Order& a, const Order& b) {
        return (a.price > b.price) || (a.price == b.price && a.timestamp > b.timestamp);
    }
};

class OrderBook {
private:
    std::priority_queue<Order, std::vector<Order>, BuyComparator> buyOrders;
    std::priority_queue<Order, std::vector<Order>, SellComparator> sellOrders;
    unsigned long currentTimestamp;

    void matchOrders() {
        while (!buyOrders.empty() && !sellOrders.empty()) {
            const Order& topBuy = buyOrders.top();
            const Order& topSell = sellOrders.top();

            // A match occurs if buy price >= sell price
            if (topBuy.price >= topSell.price) {
                int tradeQuantity = std::min(topBuy.quantity, topSell.quantity);
                double tradePrice = topSell.price; 

                std::cout << "Match! Buyer " << topBuy.id << " and Seller " << topSell.id
                          << " trade " << tradeQuantity << " units at $" << tradePrice << "\n";

                // Update quantities
                const_cast<Order&>(topBuy).quantity -= tradeQuantity;
                const_cast<Order&>(topSell).quantity -= tradeQuantity;

                // Remove fulfilled orders
                if (topBuy.quantity == 0) buyOrders.pop();
                if (topSell.quantity == 0) sellOrders.pop();
            } else {
                break; 
            }
        }
    }

public:
    OrderBook() : currentTimestamp(0) {}

    void addOrder(const std::string& type, double price, int quantity) {
        Order newOrder(currentTimestamp++, type, price, quantity, currentTimestamp);
        if (type == "buy") {
            buyOrders.push(newOrder);
        } else if (type == "sell") {
            sellOrders.push(newOrder);
        }
        matchOrders();
    }

    void displayOrders() {
        std::cout << "\nCurrent Order Book:\n";
        std::cout << std::setw(10) << "Type" << std::setw(10) << "Price"
                  << std::setw(10) << "Quantity" << "\n";

        auto buyCopy = buyOrders;
        auto sellCopy = sellOrders;

        std::cout << "Buy Orders:\n";
        while (!buyCopy.empty()) {
            const Order& order = buyCopy.top();
            std::cout << std::setw(10) << "Buy" << std::setw(10) << order.price
                      << std::setw(10) << order.quantity << "\n";
            buyCopy.pop();
        }

        std::cout << "Sell Orders:\n";
        while (!sellCopy.empty()) {
            const Order& order = sellCopy.top();
            std::cout << std::setw(10) << "Sell" << std::setw(10) << order.price
                      << std::setw(10) << order.quantity << "\n";
            sellCopy.pop();
        }
    }
};

int main() {
    OrderBook orderBook;
    int choice;

    while (true) {
        std::cout << "\n1. Add Order\n2. Display Orders\n3. Exit\nEnter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string type;
            double price;
            int quantity;

            std::cout << "Enter order type (buy/sell): ";
            std::cin >> type;
            std::cout << "Enter price: ";
            std::cin >> price;
            std::cout << "Enter quantity: ";
            std::cin >> quantity;

            if (type == "buy" || type == "sell") {
                orderBook.addOrder(type, price, quantity);
            } else {
                std::cout << "Invalid order type! Use 'buy' or 'sell'.\n";
            }
        } else if (choice == 2) {
            orderBook.displayOrders();
        } else if (choice == 3) {
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
