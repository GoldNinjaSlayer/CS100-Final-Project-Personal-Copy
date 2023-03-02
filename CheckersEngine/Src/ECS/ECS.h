#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <bitset>
#include <array>
using namespace std;
class Component;
class Entity;

using componentID = size_t;//creates an alias for std::size_t that corresponds specifically to components
inline componentID getComponentTypeID() {
	static componentID lastID = 0;
	return lastID++;

}
template<typename T> inline componentID getComponentTypeID() noexcept {
	static componentID typeID = getComponentTypeID();
	return typeID;
}

constexpr size_t maxcomponents = 32;
using  ComponentBitset = bitset<maxcomponents>;
using ComponentArray = array<Component*, maxcomponents>;

class Component {
public:
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
	Entity* entity;
};
//Entity class that has different components. eg. Player entity has a spriteComponent for its appearance and a positionComponent for location on screen
class Entity {
private:
	bool active = true;
	vector<unique_ptr<Component>> components;//unique_ptr creates smart pointer that manages and auomatically deletes the object when out of scope

	ComponentArray componentArray;
	ComponentBitset componentBitset;
public:
	void update() {
		for (auto& c : components)c->update();

	}
	void draw() {
		for (auto& c : components)c->draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	template<typename T> bool hasComponent()const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs... mArgs) {
		T* c(new T(forward<TArgs>(mArgs)...));
		c->entity = this;
		unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;//components of same type get put into the same spot in array
		componentBitset[getComponentTypeID<T>()] = true;
		c->init();//initializes added entity
		return *c;
	}
	template<typename T> T& getComponent()const {//for eg. gamobject.getComponent<positionComponent>().setxpos(25)
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};
//Entity Manager class
class Manager {
private:
	vector<unique_ptr<Entity>> entities;
public:
	void update() {//updates entities in entity manager
		for (auto& e : entities)e->update();
	}
	void draw() {
		for (auto& e : entities)e->draw();
	}
	void refresh() {
		entities.erase(remove_if(begin(entities), end(entities), [](const unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			end(entities));
	}
	Entity& addEntity() {
		Entity* e = new Entity();
		unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(move(uPtr));

		return *e;
	}

};
