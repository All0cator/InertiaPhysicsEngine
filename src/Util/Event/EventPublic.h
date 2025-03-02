#pragma once

#include <string>

#include "EventPayloads.h"
#include "EventDispatcher.h"
#include "EventSubscriptionToken.h"

#define GET_FUNCTION_POINTER(f, x) std::bind(&f, (x), std::placeholders::_1, std::placeholders::_2)

namespace EventType
{
	static const std::string KeyPressed = "KeyPressed";
	static const std::string KeyRepeated = "KeyRepeated";
	static const std::string KeyReleased = "KeyReleased";

	static const std::string MouseMoved = "MouseMoved";
	static const std::string MouseButtonPressed = "MouseButtonPressed";
	static const std::string MouseButtonReleased = "MouseButton Released";
	static const std::string MouseScrolled = "MouseScrolled";
}

/*
	For each event type create an EventPayload for it
	when passing an eventlistener the callback should be of type std::function<bool(std::string, void*)>
	where std::string is publisher's name and void* is the event's payload that needs to be casted
	to the correct EventPayload type
*/

/*
* The Event System
*/

/*
* Consists of the following systems/abstractions:
*/

/*
* EventType: a std::string, symbolizes the type of the event
* eg "EventKeyPressed", "EventApplicationExit",
* any custom event type not included in the built in event namespace EventType,
* ... etc
*/

/*
* EventPayload: an object of a class/structure casted to void* and is passed to the callback function during the Publication of an event
* Recommended Practices:
* Built-In payload types are named in the following manner: [EventType]Payload eg KeyPressedPayload where "KeyPressed" Event type
* Create payload structures for each custom event type
*/

/*
* EventDispatcher: singleton class responsible for managing subscriptions and calls the callback methods when
* an event is Raised with each successful subscription it issues a token with the information of the subscriber
* to unsubscribe you have to give the correct token for security reasons, you cannot unsubscribe another person unless you have it's token (permission)
* Data:
*				EventType				      Subscriber Name     Subscriber's callback function
*    map from std::string to another map from std::string to callback function(std::string, void*) returns bool
*
* Functions:
*    Subscribe: Links subscriber to a specific EventType
*		Input: EventType, Subscriber's name, Subscriber's callback
*		Output: EventSubscriptionToken
*    UnSubscribe Unlinks Subscriber from an EventType:
*
*		Not like this XDDD only with token
*		Input: EventType, Subscriber's name
*		Output: void
*
*		Input: EventSubscriptionToken
*		Output: void
*
*    Publish: Calls the callbacks of all linked subscriber's of a specific EventType with the specified payload
*		Input: EventType, Publisher name, Payload
*		Output: void
*
*
*	Open to Future expansions as deemed necessary: eg Currently the system publishes to all subscribers but filters could be supplied to exclude some of the subscribers
*   or publish to specific subscribers
*/

/*
* Event Subscription Token:
*
* it is returned by the EventDispatcher::Subscribe function
* It belongs to the object of the method that is passed as a callback function
* The token is alive as long as the subscription is alive (
* when the token is expired (destroyed) the subscription gets terminated
*
* A token cannot be created without a valid callback method/function and they are only created by the dispatcher
* Tokens are bound tightly with their callback's method/function lifetime if the callback method gets invalidated then the token expires (gets deleted) for example with the object's deletion
* For this reason tokens must belong to the same scope as the callback method
* They cannot be copied they must expire when the function callback gets invalidated but you can get a pointer to a token at your own risk
*/


/*
* USAGE EXAMPLE
*/

// Example with Member function and global function

/*
#include <iostream>
#include "Event/EventPublic.h"

class Player
{
public:
	Player(std::string name)
	{
		m_name = name;
	}
	bool player_key_pressed_callback(const std::string publisher_name, const void* p)
	{
		KeyPressedPayload* pay = (KeyPressedPayload*)p;
		std::cout << "Player Name: " << m_name << " Key pressed in player callback is : " << pay->keycode << std::endl;

		return true;
	}
private:
	std::string m_name;
};


bool listener1_key_pressed_callback(const std::string publisher_name, const void* p)
{
	const KeyPressedPayload * pPayload = (const KeyPressedPayload *)(p);

	std::cout << "Listener 1 got payload of key pressed from " << publisher_name << " " << pPayload->keycode << " " << pPayload->shift_pressed << std::endl;

	return true;
}

bool listener2_key_pressed_callback(const std::string publisher_name, const void* p)
{
	std::cout << "Listener 2 key pressed callback from " << publisher_name << std::endl;
	return true;
}

int main() 
{
	// Example Using 2 global functions
	EventDispatcher::inst()->subscribe(EventType::KeyPressed, "Subscriber1", listener1_key_pressed_callback);
	EventDispatcher::inst()->subscribe(EventType::KeyPressed, "Subscriber2", listener2_key_pressed_callback);

	// Example using member function of Player class
	Player player("Allocator");

	EventDispatcher::inst()->subscribe(EventType::KeyPressed, "Player 1", GET_FUNCTION_POINTER(Player::player_key_pressed_callback, player));

	KeyPressedPayload p;
	p.keycode = 15;
	p.shift_pressed = false;

	EventDispatcher::inst()->publish(EventType::KeyPressed, "Main", (const void*)&p);

	EventDispatcher::inst()->un_subscribe(EventType::KeyPressed, "Subscriber1");

	EventDispatcher::inst()->publish(EventType::KeyPressed, "Main", (const void*)&p);

	EventDispatcher::inst()->un_subscribe(EventType::KeyPressed, "Subscriber2");
	EventDispatcher::inst()->un_subscribe(EventType::KeyPressed, "Player 1");
	EventDispatcher::inst()->un_subscribe("Event123", "Sub1");
	
	return 0;
}
*/

/*
* Output
*/

/*
Listener 1 got payload of key pressed from Main 15 0
Player Name: Allocator Key pressed in player callback is : 15
Listener 2 key pressed callback from Main
Player Name: Allocator Key pressed in player callback is : 15
Listener 2 key pressed callback from Main
*/
