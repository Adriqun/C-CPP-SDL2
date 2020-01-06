#include <thread>
#include <mutex>
#include <string>

void send_data(double x)
{
}

std::string receive_data(double x)
{
	return std::to_string(x);
}

class X
{
	int connection_details;
	double data;
	std::once_flag connection_init_flag;

	void open_connection()
	{
		data = 1.0f;
	}

public:
	X(int const& x) : connection_details(x)
	{
	}

	void send_data(std::string const& data)
	{
		std::call_once(connection_init_flag, &X::open_connection, this);
		send_data(data);
	}

	std::string receive_data()
	{
		std::call_once(connection_init_flag, &X::open_connection, this);
		return ::receive_data(data);
	}
};

int main()
{
	return 0;
}