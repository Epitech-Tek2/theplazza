/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** ConditionVariable
*/

#ifndef CONDITIONVARIABLE_HPP_
#define CONDITIONVARIABLE_HPP_

#include <condition_variable>
#include <chrono>

#include "UniqueLock.hpp"

namespace enc {
    class ConditionVariable {
    public:
        ConditionVariable() = default;
        ~ConditionVariable() = default;

        void notify_one(void);
        void notify_all(void);

        template<typename Predicate>
        void wait(UniqueLock &lock, Predicate p)
        {
            _cv.wait(lock.variable(), p);
        }

        template<typename _Rep, typename _Period, typename _Predicate>
        bool wait_for(UniqueLock &lock, const std::chrono::duration<_Rep, _Period>& rtime, _Predicate p)
        {
            return (_cv.wait_for(lock.variable(), rtime, p));
        }

        template<typename _Rep, typename _Period>
        std::cv_status wait_for(UniqueLock &lock, const std::chrono::duration<_Rep, _Period> &rtime)
        {
            return (_cv.wait_for(lock.variable(), rtime));
        }

    private:
        std::condition_variable _cv;
    };
}

#endif /* !CONDITIONVARIABLE_HPP_ */
