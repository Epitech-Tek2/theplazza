/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** ConditionVariable
*/

#include "ConditionVariable.hpp"

void enc::ConditionVariable::notify_one(void)
{
    _cv.notify_one();
}

void enc::ConditionVariable::notify_all(void)
{
    _cv.notify_all();
}
