#ifndef FACTORY_H
#define FACTORY_H
#include <functional>
#include <map>

#include <IConverter.h>


namespace Factory
{
    template <typename T>
    class Creator
    {
    private:
        std::function<std::shared_ptr<T>()> create_function_;
    public:
        explicit Creator(std::function<std::shared_ptr<T>()> create_function)
            : create_function_{std::move(create_function)}
        {}

        std::shared_ptr<T> create()
        {
            return create_function_();
        }
    };


    template <typename T>
    class Factory
    {
    private:
        std::map<std::string, Creator<T>> creators_;
    public:
        std::shared_ptr<T> create(const std::string & converter_name)
        {
            auto it = creators_.find(converter_name);
            if (it != creators_.end()) {
                return it->second.create();
            }
            return nullptr;
        }
        void register_creator(std::string name, Creator<T> creator) {
            creators_.insert({name, creator});
        }


    };

}

#endif