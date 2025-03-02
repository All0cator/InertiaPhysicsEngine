#pragma once

#include <string>
#include <functional>

class EventSubscriptionToken
{
public:

	// Prohibit usage of assignment operator, copy, move constructors
	EventSubscriptionToken& operator=(const EventSubscriptionToken& other) = delete;
	EventSubscriptionToken(const EventSubscriptionToken& other) = delete;
	EventSubscriptionToken(EventSubscriptionToken&& other) = delete;

	~EventSubscriptionToken();

	std::function<bool(const std::string, const void*)> get_callback();
	std::string get_subscriber_name();
	std::string get_event_type();

protected:
	// Only EventDispatcher can create EventSubscriptionTokens
	friend class EventDispatcher;
	EventSubscriptionToken(std::string event_type, std::string subscriber_name, std::function<bool(const std::string, const void*)> callback);
	EventSubscriptionToken();
private:
	//				Publisher name  Payload
	std::function<bool(const std::string, const void*)> m_callback;
	std::string m_subscriber_name;
	std::string m_event_type;
};