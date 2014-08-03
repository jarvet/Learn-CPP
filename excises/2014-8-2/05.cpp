#include <iostream>
using namespace std;

class transactions
{
public:
	transactions(int ac_num, int num_transactions, const float transaction_values[]);
	transactions(const transactions& tr);
	~transactions();
	void display() const;
	const transactions& operator=(const transactions& t);
private:
	int account_number;
	int number_of_transactions;
	void modify_transaction(int transaction_index, float amount);
	float *transaction_amounts;
};

transactions::transactions(int ac_num, int num_transactions, const float transaction_values[])
{
	account_number = ac_num;
	number_of_transactions = num_transactions;
	transaction_amounts = new float[number_of_transactions];
	for (int i = 0; i < number_of_transactions; i++)
	{
		transaction_amounts[i] = transaction_values[i];
	}
}

transactions::transactions(const transactions& tr)
{
	account_number = tr.account_number;
	number_of_transactions = tr.number_of_transactions;
	transaction_amounts = new float[number_of_transactions];
	for (int i = 0; i < number_of_transactions; ++i)
	{
		transaction_amounts[i] = tr.transaction_amounts[i];
	}
}

transactions::~transactions()
{
	delete[] transaction_amounts;
}

void transactions::display() const
{
	cout << "Account Number " << account_number << " Transactions: ";
	for (int i = 0; i < number_of_transactions; i++)
	{
		cout << transaction_amounts[i] << ' ';
	}
	cout << endl;
}

const transactions& transactions::operator=(const transactions& t)
{
	if (this != &t)
	{
		account_number = t.account_number;
		number_of_transactions = t.number_of_transactions;
		delete[] transaction_amounts;
		transaction_amounts = new float[number_of_transactions];
		for (int i = 0; i < number_of_transactions; ++i)
		{
			transaction_amounts[i] = t.transaction_amounts[i];
		}
	}
	return *this;
}

int main(int argc, char const *argv[])
{
	float transaction_amounts1[] = {25.67, 6.12, 19.86, 23.41, 1.21};
	transactions trans_object1(1, 5, transaction_amounts1);
	transactions trans_object2 = trans_object1;
	cout << "trans_object1:" << endl;
	trans_object1.display();
	cout << "trans_object2:" << endl;
	trans_object2.display();
	return 0;
}

// int main(int argc, char const *argv[])
// {
// 	float transaction_amounts1[] = {25.67, 6.12, 19.86, 23.41, 1.21};
// 	transactions trans_object1(1, 5, transaction_amounts1);
// 	float transaction_amounts2[] = {16.82, 8.45, 56.19};
// 	transactions trans_object2(2, 3, transaction_amounts2);
// 	cout << "Before assignment:" << endl;
// 	cout << "trans_object1:" << endl;
// 	trans_object1.display();
// 	cout << "trans_object2:" << endl;
// 	trans_object2.display();

// 	trans_object2 = trans_object1;

// 	cout << endl << "After assignment:" << endl;
// 	cout << "trans_object1:" << endl;
// 	trans_object1.display();
// 	cout << "trans_object2:" << endl;
// 	trans_object2.display();
// 	return 0;
// }