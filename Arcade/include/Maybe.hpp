/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Maybe
*/

#ifndef MAYBE_HPP_
#define MAYBE_HPP_

#include <memory>

enum MaybeEnum {
    isNothing,
    isJust,
};

template<typename T>
class MaybeClass {
    public:
        virtual bool operator==(MaybeEnum type) = 0;
};

template<typename T>
class Just : public MaybeClass {
    public:
        Just(T val) : _val(val) {};

        bool operator==(MaybeEnum type) override { return type == MaybeEnum::isJust; };
        virtual T val() { return _val; };

    protected:
    private:
        T _val;
};

template<typename T = int>
class Nothing : public MaybeClass<T> {
    public:
        Nothing() {};

        bool operator==(MaybeEnum type) override { return type == MaybeEnum::isNothing; };

    protected:
    private:
};

#endif /* !MAYBE_HPP_ */
