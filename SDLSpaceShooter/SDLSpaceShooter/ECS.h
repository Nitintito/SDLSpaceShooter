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

constexpr std::size_t maxComponents = 64;
constexpr std::size_t maxGroups = 64;

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
		auto& self = *this;
		for (size_t i = 0; i < components.size(); i++)
		{
			auto& c = components[i];
			if (c == nullptr)
			{
				std::cout << "Null";
				return;
			}
			c->update();
		}
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
	using EntityHandle = std::unique_ptr<Entity>;
	using EntityHandleRef = EntityHandle*;
	std::vector<EntityHandle> entities;
	std::array<std::vector<Entity*>, maxGroups> groupEntities;
public:

	void update()
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			auto& e = entities[i];
			e->update();
		}
	}
	void draw()
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			auto& e = entities[i];
			e->draw();
		}
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupEntities[i]);
			v.erase( std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	void AddToGroup(Entity* entity, Group group)
	{
		groupEntities[group].emplace_back(entity);
	}

	std::vector<Entity*>& getGroup(Group group)
	{
		return groupEntities[group];
	}

	bool isGroupEmpty(Group group)
	{
		if (group == groupEntities.empty())
		{
			return true;
		}
		else
			return false;
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};