#include "Message.h"

Message::Message()
{
}

void Message::putInt(std::string key, int value)
{
	_intMap.insert(std::pair<std::string, int>(key, value));
}

void Message::putFloat(std::string key, float value)
{
	_floatMap.insert(std::pair<std::string, float>(key, value));
}

void Message::putString(std::string key, std::string value)
{
	_stringMap.insert(std::pair<std::string, std::string>(key, value));
}

int Message::getInt(std::string key)
{
	auto iter = _intMap.find(key);
	if (iter != _intMap.end())
		return iter->second;
	return 0;
}

float Message::getFloat(std::string key)
{
	auto iter = _floatMap.find(key);
	if (iter != _floatMap.end())
		return iter->second;
	return 0.0f;
}

std::string Message::getString(std::string key)
{
	auto iter = _stringMap.find(key);
	if (iter != _stringMap.end())
		return iter->second;
	return "";
}