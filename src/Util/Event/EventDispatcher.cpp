#include "EventDispatcher.h"
#include "EventSubscriptionToken.h"

EventDispatcher* EventDispatcher::m_instance = nullptr;

EventDispatcher* EventDispatcher::inst()
{
	if (!m_instance)
	{
		m_instance = new EventDispatcher();
	}

	return m_instance;
}

void EventDispatcher::subscribe(const std::string& event_type, const std::string subscriber_name, std::function<bool(const std::string, const void*)> callback)
{
	// If event is not registered
	if (m_event_type_to_subscriber_name_to_callback.find(event_type) == m_event_type_to_subscriber_name_to_callback.end())
	{
		m_event_type_to_subscriber_name_to_callback[event_type] = std::unordered_map<std::string, std::function<bool(const std::string, const void*)>>();
	}

	// If subscriber is not already a subscriber
	if (m_event_type_to_subscriber_name_to_callback[event_type].find(subscriber_name) == m_event_type_to_subscriber_name_to_callback[event_type].end())
	{
		m_event_type_to_subscriber_name_to_callback[event_type][subscriber_name] = callback;
	}
}

void EventDispatcher::un_subscribe(const std::string& event_type, std::string subscriber_name)
{
	// If event is registered
	if (m_event_type_to_subscriber_name_to_callback.find(event_type) != m_event_type_to_subscriber_name_to_callback.end())
	{
		// If listener is a subscriber
		if (m_event_type_to_subscriber_name_to_callback[event_type].find(subscriber_name) != m_event_type_to_subscriber_name_to_callback[event_type].end())
		{
			m_event_type_to_subscriber_name_to_callback[event_type].erase(subscriber_name);
		}
	}
}

void EventDispatcher::un_subscribe(const EventSubscriptionToken& token)
{
	// We know event type and subscriber name are valid in both maps as tokens are created from subscriptions
	m_event_type_to_subscriber_name_to_callback[token.m_event_type].erase(token.m_subscriber_name);
}

void EventDispatcher::publish(const std::string& event_type, const std::string& publisher_name, const void* payload)
{
	// If event type is registered
	if (m_event_type_to_subscriber_name_to_callback.find(event_type) != m_event_type_to_subscriber_name_to_callback.end())
	{
		// publish event with payload to all event subscribers
		for (auto it = m_event_type_to_subscriber_name_to_callback[event_type].begin(); it != m_event_type_to_subscriber_name_to_callback[event_type].end();)
		{
			if (it->second)
			{
				it->second(publisher_name, payload);
				++it;
			}
			else
			{
				// Subscriber's callback is not valid pointer
				// Do not increment iterator if we erase
				m_event_type_to_subscriber_name_to_callback[event_type].erase(it);
			}
		}
	}
}

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
	for (auto& it : m_event_type_to_subscriber_name_to_callback)
	{
		it.second.clear();
	}

	m_event_type_to_subscriber_name_to_callback.clear();
}