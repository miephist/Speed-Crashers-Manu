#include "dos.h"

Cuenta::Cuenta(unsigned time)
    : m_time(time)
{}

unsigned Cuenta::step(){

    if(m_time)
        --m_time;

    return m_time;
}

unsigned Cuenta::status() const { return m_time; }