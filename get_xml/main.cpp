#include "xml_getter.h"

int main()
{
	xml_getter getter("news.mit.edu/rss/school/engineering");
	getter.getXml();
	cout << getter.returnXml() << endl;

}