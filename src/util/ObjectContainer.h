#pragma once

#include <vector>
#include <exception>

template <typename ... TTypes>
class ObjectContainer;

template <>
class ObjectContainer<> {};

template <typename TFirst, typename ... TRest>
class ObjectContainer<TFirst, TRest ...>
{
private:
	std::vector<TFirst> first;

	ObjectContainer<TRest ...> restContainer;

public:
	template <typename TType>
	std::vector<TType>& getContainer()
	{
		return restContainer.getContainer<TType>();
	}

	template <>
	std::vector<TFirst>& getContainer<TFirst>()
	{
		return first;
	}

	void update()
	{
		for (auto it = first.begin(); it != first.end();)
		{
			it->update();

			if (Game::unflagDestruction())
				it = first.erase(it);
			else
				++it;
		}

		if constexpr (sizeof ...(TRest))
			restContainer.update();
	}

	void draw()
	{
		for (TFirst& f : first)
			f.draw();

		if constexpr (sizeof ...(TRest))
			restContainer.draw();
	}

	void clear()
	{
		first.clear();

		if constexpr (sizeof ...(TRest))
			restContainer.clear();
	}
};