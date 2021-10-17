/*
** EPITECH PROJECT, 2021
** ex5
** File description:
** SafeQueue
*/

#include "Queue.hpp"

template<class T>
safe::Queue<T>::Queue(void) noexcept
 : _stop(false), _ready(false)
{}

template<class T>
void safe::Queue<T>::push(T value)
{
    enc::UniqueLock lock(_mutex);

    _queue.push_back(value);
    _ready = true;
    _cv.notify_one();
}

template<class T>
bool safe::Queue<T>::pop(T &value)
{
    enc::UniqueLock lock(_mutex);

    while (_queue.empty()) {
        _ready = false;
        _cv.wait(lock, [this]{return (this->_ready || _stop);});
        if (_stop)
            return (false);
    }
    value = _queue.front();
    _queue.pop_front();
    return (true);
}

template<class T>
std::string safe::Queue<T>::dump(void)
{
    std::stringstream s;
    enc::UniqueLock lock(_mutex);

    if (_queue.empty())
        s << "        Empty" << std::endl;
    for (T n : _queue) {
        s << "        " << n.unpack() << std::endl;
    }
    return (s.str());
}

template<class T>
void safe::Queue<T>::stop(void)
{
    enc::UniqueLock lock(_mutex);

    _stop = true;
    _cv.notify_all();
}

template safe::Queue<int>::Queue(void);
template safe::Queue<Plazza::Pizza>::Queue(void);
template safe::Queue<double>::Queue(void);

template bool safe::Queue<int>::pop(int &value);
template bool safe::Queue<Plazza::Pizza>::pop(Plazza::Pizza &value);
template bool safe::Queue<double>::pop(double &value);

template void safe::Queue<int>::push(int value);
template void safe::Queue<Plazza::Pizza>::push(Plazza::Pizza value);
template void safe::Queue<double>::push(double value);

template std::string safe::Queue<Plazza::Pizza>::dump(void);

template void safe::Queue<int>::stop(void);
template void safe::Queue<Plazza::Pizza>::stop(void);
template void safe::Queue<double>::stop(void);
