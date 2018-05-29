#include "Client.h"


using namespace boost::asio;
Client::Client(string ip, const char * port_)		
{
	this->IOHandler = new io_service();
	this->clientSocket = new ip::tcp::socket(*IOHandler);
	this->clientResolver = new ip::tcp::resolver(*IOHandler);

	ipToConect = ip;
	port = port_;
}

//using namespace boost::asio;
void Client::link()	//Conecto al ip enviado
{

	auto q = ip::tcp::resolver::query(ipToConect.c_str(), this->port);
	this->endpoint = clientResolver->resolve(q);
	cout << "Connecting to Server" << endl;
	try {
		connect(*clientSocket, endpoint);
	}
	catch (const std::exception& error) {
		// Should print the actual error message
		std::cerr << error.what() << std::endl;
	}
	
	clientSocket->non_blocking(true);
	

	cout << "Client trying to connect to " << ipToConect.c_str() << endl;
}

void Client::sendMessage(string msg)	//Envio mensaje
{
	std::cout << "Trying to send message" << std::endl;
	size_t lenght = 0;
	boost::system::error_code error;


	lenght = this->clientSocket->write_some(boost::asio::buffer(msg, msg.size()), error);

	std::cout << "Message sent, lenght =" <<lenght <<std::endl;


}

/*bool Client::sendMessageTimed(string msg, int ms)
{
	std::cout << "Trying to send message" << std::endl;
	Timer timer;
	timer.start();
	bool timeout = false;

	size_t lenght = 0;
	boost::system::error_code error;

	do {
		lenght = this->clientSocket->write_some(boost::asio::buffer(msg, msg.size()), error);
		timer.stop();
		if (timer.getTime() > ms && lenght == 0)
			timeout = true;
	} while (error && !timeout);

	return !timeout;
}
*/
std::string Client::getInfo() {

	char buffer[1 + 255 + 1];
	size_t lenght = 0;
	boost::system::error_code error;

	do {
		lenght = this->clientSocket->read_some(boost::asio::buffer(buffer), error);
	} while (error);

	buffer[lenght] = 0;
	std::string retValue = buffer;
	std::cout << "Recieved a message" << std::endl;

	return retValue;
}

string Client::getInfoTimed(int ms)	//ESTO HAY QUE REHACER
{
	Timer timer;



	string buffer;
	size_t lenght = 0;
	boost::system::error_code error;

	timer.start();

	bool timeout = false;
	try
	{
		do {
			lenght = this->clientSocket->read_some(boost::asio::buffer(buffer), error);
			timer.stop();
			if (timer.getTime() < ms) {
				timeout = false;
			}
			else
			{
				timeout = true;
			}

		} while ((error.value() == WSAEWOULDBLOCK) || !timeout);
		int erval = error.value();
		if (error == boost::asio::error::eof)
			cout << "Mensaje recibido bien";
		else if (error)
			throw boost::system::system_error(error); // Some other error.
	}

	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	

  

	std::string retValue;

	if (!timeout) 
	{
		retValue = buffer;
		std::cout << "Recieved a message" << std::endl;
	}
	else
		retValue = CLIENT_TIMEOUT;

	return retValue;
}


Client::~Client()
{
	std::cout << "Closing connection" << std::endl;
	this->clientSocket->close();
	delete this->clientResolver;
	delete this->clientSocket;
	delete this->IOHandler;
}
