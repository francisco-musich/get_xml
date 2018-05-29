#include "xml_getter.h"

int main()
{
	xml_getter getter("cyber.harvard.edu/rss/examples/rss2sample.xml");
	getter.getXml();
	bool okay = getter.isGetOkay();
	if (okay)
	{
		getter.trim();
	}
	cout << getter.returnXml() << endl;

}