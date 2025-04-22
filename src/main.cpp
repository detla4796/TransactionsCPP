#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Transaction
{
    string sender;
    string receiver;
    int amount;
    time_t timestamp;
public:
    static int totalTransactions;
    static int totalAmount;
    static int maxLimit;
    static vector<Transaction> tHistory;
    Transaction(string sender, string receiver, int amount) : sender(sender), receiver(receiver), amount(amount)
    {
        if (amount > maxLimit)
        {
            throw runtime_error("Transaction amount exceeds the maximum limit.");
        }
        timestamp = time(nullptr);
        totalTransactions++;
        totalAmount += amount;
        tHistory.push_back(*this);
    }
    ~Transaction() 
    {
        if (!tHistory.empty())
        {
            tHistory.pop_back();
            totalTransactions--;
            totalAmount -= amount;
        }
    }
    static int getTotalTransactions()
    {
        return totalTransactions;
    }
    static int getTotalAmount()
    {
        return totalAmount;
    }
    static int getAverageAmount()
    {
        if (totalTransactions == 0)
        {
            return 0;
        }
        return totalAmount / totalTransactions;
    }
    static void setMaxLimit(int l)
    {
        maxLimit = l;
    }
    static vector<Transaction> getTransactionsByUser(const string& user)
    {
        vector<Transaction> userTransactions;
        for (const Transaction& t : tHistory)
        {
            if (t.sender == user || t.receiver == user)
            {
                userTransactions.push_back(t);
            }
        }
        return userTransactions;
    }
    string getSender() const
    {
        return sender;
    }
    string getReceiver() const
    {
        return receiver;
    }
    int getAmount() const
    {
        return amount;
    }
    time_t getTimestamp() const
    {
        return timestamp;
    }
};

int Transaction::totalTransactions = 0;
int Transaction::totalAmount = 0;
int Transaction::maxLimit = 1000000;
vector<Transaction> Transaction::tHistory;

int main()
{
    Transaction::setMaxLimit(5000);
    cout << "Max limit: " << Transaction::maxLimit << endl;

    cout << "First transactions: " << endl;
    {
        Transaction t1("Danil", "Eva", 100);
        cout << "Total transactions: " << Transaction::getTotalTransactions() << endl;
        cout << "Total amount: " << Transaction::getTotalAmount() << endl;
        cout << "Average amount: " << Transaction::getAverageAmount() << endl;
    }

    cout << "After destructor: " << endl;
    cout << "Total transactions: " << Transaction::getTotalTransactions() << endl;
    cout << "Total amount: " << Transaction::getTotalAmount() << endl;
    cout << "Average amount: " << Transaction::getAverageAmount() << endl;

    cout << "Second transactions: " << endl;
    {
        Transaction t2("Eva", "Danil", 200);
        cout << "Total transactions: " << Transaction::getTotalTransactions() << endl;
        cout << "Total amount: " << Transaction::getTotalAmount() << endl;
        cout << "Average amount: " << Transaction::getAverageAmount() << endl;
    }

    Transaction t4("Eva", "Danil", 400);
    Transaction t5("Danil", "Eva", 500);
    cout << "Transactions by user: " << endl;
    vector<Transaction> userTransactions = Transaction::getTransactionsByUser("Eva");
    for (const Transaction& t : userTransactions)
    {
        cout << "Sender: " << t.getSender() << ", Receiver: " << t.getReceiver() << ", Amount: " << t.getAmount() << endl;
    }

    cout << "Limit test: " << endl;
    Transaction t3("Danil", "Eva", 6000);
}