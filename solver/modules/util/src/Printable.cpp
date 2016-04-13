
#include <util/Printable.h>

std::ostream& operator<<(std::ostream& ost, const Printable& value){
	value.Print(ost);
	return ost;
}

