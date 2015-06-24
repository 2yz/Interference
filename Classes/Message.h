#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <map>

class Message
{
public:
	Message();
	void putInt(std::string key, int value);
	void putFloat(std::string key, float value);
	void putString(std::string key, std::string value);
	int getInt(std::string key);
	float getFloat(std::string key);
	std::string getString(std::string key);
protected:
	std::map<std::string, int> int_map_;
	std::map<std::string, float> float_map_;
	std::map<std::string, std::string> string_map_;
};

#endif /* MESSAGE_H_ */