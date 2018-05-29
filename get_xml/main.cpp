#include "xml_getter.h"

int main()
{
	xml_getter getter("blogs.nasa.gov/stationreport/feed/");
	getter.getXml();
	cout << getter.returnXml() << endl;

}