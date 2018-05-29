#pragma once
#include"Client.h"
#include<string>
using namespace std;
#define PORT "80"


class xml_getter
{
public:
	xml_getter(string webpage);
	~xml_getter();
	bool getXml();
	string returnXml();
	bool isGetOkay();
	void trim();

private:
	Client* client;
	string hostToGet;
	string rssFeed;
	string xmlRecieved;
	string fullSite;
};

