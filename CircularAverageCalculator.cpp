#include "CircularAverageCalculator.hpp"
#include <exception>

CircularAverageCalculator::CircularAverageCalculator(const std::size_t size){
	this->size = size;
	this->buffer.reserve(size);
}

CircularAverageCalculator::~CircularAverageCalculator()
{

}

bool CircularAverageCalculator::isFull() const{
	return this->buffer.size() == this->size;
}

void CircularAverageCalculator::pushValue(const long double value){
	if(this->buffer.size() != this->size){//буффер еще не наполнился
		this->buffer.push_back(value);
		if(this->buffer.size() == this->size)//буффер наполнился
			this->oldestValue = this->buffer.begin();
	}
	else{
		*this->oldestValue = value;
		++this->oldestValue;
		if(this->oldestValue == this->buffer.end())
			this->oldestValue = this->buffer.begin();
	}
}

long double CircularAverageCalculator::calcAverage() const{
	long double result = 0;
	for(const auto value : this->buffer)
		result += value;
	result /= this->buffer.size();
	return result;
}
