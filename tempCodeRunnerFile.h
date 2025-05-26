int Location::operator< (const Location &rhs) const{
	if(this -> lengthFromStart < rhs.lengthFromStart){
		return 1;
	}
}

int Location::operator> (const Location &rhs) const{
	if(this -> lengthFromStart > rhs.lengthFromStart){
		return 1;
	}
}