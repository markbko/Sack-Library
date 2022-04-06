template <typename T>
Stack<T>::Stack(){ 
}

template <typename T>
Stack<T>::~Stack(){
	stack.clear(); 
}

template <typename T>
Stack<T>::Stack(const Stack<T> & x){ 
	*this = x;
}
	
template <typename T>
Stack<T>::Stack(Stack<T> && x){ 
	*this = x;
}

template <typename T>
Stack<T> & Stack<T>::operator=(const Stack<T> & b){ 
	stack = b.stack;
	return *this;
}

template <typename T>
Stack<T> & Stack<T>::operator=(Stack<T> && b){ 
	stack = b.stack;
	return *this;
}

template <typename T>
bool Stack<T>::empty() const{
	return stack.empty();
}

template <typename T>
void Stack<T>::clear(){
	stack.clear();
}

template <typename T>
void Stack<T>::push(const T& x){ 
	stack.push_back(x);
}

template <typename T>
void Stack<T>::push(T&& x){ 
	stack.push_back(x);
}

template <typename T>
void Stack<T>::pop(){ 
	stack.pop_back();
}

template <typename T>
T& Stack<T>::top(){ 
	return stack.back();
}

template <typename T>
const T& Stack<T>::top() const{ 
	return stack.back();
}
	
template <typename T>
int Stack<T>::size() const{ 
	return stack.size();
}

template <typename T>
void Stack<T>::print(std::ostream & os, char ofc) const{ 
for(auto itr = stack.begin(); itr != stack.end(); ++itr)
	os << *itr << ofc;
}

template <typename T>
std::ostream & operator << (std::ostream & os, const Stack<T> & a){    
	a.print(os);
	return os;
}

template <typename T>
bool operator == (const Stack<T> & a, const Stack<T> & b){   
	if (a.size() != b.size())
	{
		return false;
	}
	return a.getVector() == b.getVector();
}

template <typename T>
bool operator != (const Stack<T> & a, const Stack<T> & b){ 
	if (a.size() != b.size())
	{
		return true;
	}
	return a.getVector() != b.getVector();
}

template <typename T>
bool operator <= (const Stack<T> & a, const Stack<T> & b){ 
	return a.getVector() <= b.getVector();
}

template <typename T>
std::vector<T> Stack<T>::getVector() const{ 
	return stack;
}