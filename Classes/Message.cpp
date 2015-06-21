#include "Message.h"

Message::Message()
{
}

void Message::putInt(std::string key, int value)
{
	int_map_.insert(std::pair<std::string, int>(key, value));
}

void Message::putFloat(std::string key, float value)
{
	float_map_.insert(std::pair<std::string, float>(key, value));
}

void Message::putString(std::string key, std::string value)
{
	string_map_.insert(std::pair<std::string, std::string>(key, value));
}

int Message::getInt(std::string key)
{
	auto iter = int_map_.find(key);
	if (iter != int_map_.end())
		return iter->second;
	return 0;
}

float Message::getFloat(std::string key)
{
	auto iter = float_map_.find(key);
	if (iter != float_map_.end())
		return iter->second;
	return 0.0f;
}

std::string Message::getString(std::string key)
{
	auto iter = string_map_.find(key);
	if (iter != string_map_.end())
		return iter->second;
	return "";
}