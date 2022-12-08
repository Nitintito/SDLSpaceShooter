#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 16;
constexpr std::size_t maxGroups = 16;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component(){}
};

class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	GroupBitset groupBitset;

public:
	Entity(Manager& manager) : manager(manager){}

	void update()
	{
		for (auto& c : components) c->update();
	}
	void draw()
	{
		for (auto & c : components) c->draw();
	}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group group)
	{
		return groupBitset[group];
	}

	void addGroup(Group group);
	void deleteGroup(Group group)
	{
		groupBitset[group] = false;
	}

	template <typename T> bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... tArgs>
	T& addComponent(tArgs&&... mArgs)
	{
		T* c(new T(std::forward<tArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->init();

		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupEntities;
public:

	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		for (auto i(0u); i = maxGroups; i++)
		{
			auto& vector(groupEntities[i]);
			vector.erase(std::remove_if(std::begin(vector), std::end(vector), [i](Entity* entity)
				{
					return !entity->isActive() || !entity->hasGroup(i);
				}),
				std::end(vector));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& entity)
		{
			return !entity->isActive();
		}),
			std::end(entities));
	}

	void AddToGroup(Entity* entity, Group group)
	{
		groupEntities[group].emplace_back(entity);
	}

	std::vector<Entity*>& getGeroup(Group group)
	{
		return groupEntities[group];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};