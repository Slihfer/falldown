#pragma once

#include <string>
#include <unordered_map>

template <class TResource>
class Resource
{
    friend TResource;

private:
    inline static std::unordered_map<std::string, const TResource>& getContainer()
    {
        static std::unordered_map<std::string, const TResource> container;
        return container;
    }

protected:
    Resource() = default;

public:
    static const TResource& get(const std::string& key)
    {
        return getContainer().find(key)->second;
    }

    template <typename ... TArguments>
    static void load(const std::string& key, TArguments&& ... args)
    {
        getContainer().emplace(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(args ...));
    }
};