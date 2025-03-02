#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

class EventSubscriptionToken;

class EventDispatcher
{
public:
	static EventDispatcher* inst();

	void subscribe(const std::string& event_type, const std::string subscriber_name, std::function<bool(const std::string, const void*)> callback);
	void un_subscribe(const std::string& event_type, std::string subscriber_name);
	void un_subscribe(const EventSubscriptionToken& token);
	void publish(const std::string& event_type, const std::string& publisher_name, const void* payload);

private:
	EventDispatcher();
	~EventDispatcher();

private:
	static EventDispatcher* m_instance;

	std::unordered_map<std::string, std::unordered_map<std::string, std::function<bool(const std::string, const void*)>>> m_event_type_to_subscriber_name_to_callback;
};