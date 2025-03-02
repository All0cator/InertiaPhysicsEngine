#include "EventSubscriptionToken.h"
#include "EventDispatcher.h"

EventSubscriptionToken::~EventSubscriptionToken()
{
	EventDispatcher::inst()->un_subscribe(m_event_type, m_subscriber_name);
}
// Only EventDispatcher friend can access these fields

std::function<bool(const std::string, const void*)> EventSubscriptionToken::get_callback()
{
	return m_callback;
}

std::string EventSubscriptionToken::get_subscriber_name()
{
	return m_subscriber_name;
}

std::string EventSubscriptionToken::get_event_type()
{
	return m_event_type;
}

EventSubscriptionToken::EventSubscriptionToken(std::string event_type, std::string subscriber_name, std::function<bool(const std::string, const void*)> callback)
{
	m_callback = callback;
	m_subscriber_name = subscriber_name;
	m_event_type = event_type;
}

EventSubscriptionToken::EventSubscriptionToken()
{
	m_callback = nullptr;
	m_subscriber_name = "";
	m_event_type = "";
}