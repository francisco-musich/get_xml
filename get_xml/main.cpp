#include "xml_getter.h"

int main()
{
	xml_getter getter("blogs.nasa.gov/stationreport/feed/");
	getter.getXml();
	bool okay = getter.isGetOkay();
	if (okay)
	{
		getter.trim();
	}
	cout << getter.returnXml() << endl;

}