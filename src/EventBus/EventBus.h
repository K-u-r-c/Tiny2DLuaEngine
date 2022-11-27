#ifndef DF21D5BB_889E_495D_BAA7_16728C67F6B1
#define DF21D5BB_889E_495D_BAA7_16728C67F6B1

#include "Event.h"
#include <map>
#include <typeindex>
#include <functional>
#include <list>
#include <memory>

class IEventCallback {
   private:
    virtual void Call(Event& e) = 0;

   public:
    virtual ~IEventCallback() = default;

    void Execute(Event& e) { Call(e); }
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
   private:
    typedef void (TOwner::*CallbackFunction)(TEvent&);

    TOwner* ownerInstance;
    CallbackFunction callbackFunction;

    virtual void Call(Event& e) override { std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e)); }

   public:
    EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
        this->ownerInstance = ownerInstance;
        this->callbackFunction = callbackFunction;
    }

    virtual ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus {
   private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

   public:
    EventBus() = default;
    ~EventBus() = default;

    // Clears the subscribers list
    void Reset() { subscribers.clear(); }

    /**Subscribe to event of type <T>
     * In my implementation, a listener subscribes to an event
     * Example: eventBus->SubscribeToEvent<CollisionEvent>(this, &Game::onCollision);
     */
    template <typename TEvent, typename TOwner>
    void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
        if (!subscribers[typeid(TEvent)].get()) {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }

        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);

        // ? Since subscriber is a unique pointer we need to use std::move to change ownership of an object to from one unique_ptr to
        // ? another
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

    /**Emit event of type <T>
     * In my implementation, as soon as something emits an event
     * we go ahead and execute all the listener callbacks functions
     * Example: eventBus->EmitEvent<CollisionEvent>(player, enemy);
     */
    template <typename TEvent, typename... TArgs>
    void EmitEvent(TArgs&&... args) {
        auto handlers = subscribers[typeid(TEvent)].get();
        if (handlers) {
            for (auto it = handlers->begin(); it != handlers->end(); it++) {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Execute(event);
            }
        }
    }
};

#endif /* DF21D5BB_889E_495D_BAA7_16728C67F6B1 */
