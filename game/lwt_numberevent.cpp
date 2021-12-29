#include "stdafx.h"
#ifdef ENABLE_NUMBER_EVENT
#include "lwt_numberevent.h"
#include "char_manager.h"
#include "char.h"
#include <random>
// #define LOG

auto CNumberEvent::AddNumber(LPCHARACTER ch, const DWORD dwNumber) -> void
{
    for (const auto& [key , value] : m_number_map)
    {
        if (ch->GetPlayerID() == value)
        {
            ch->ChatPacket(1, "You have already entered a number!");
            return;
        }
    }

    if (m_number_map.contains(dwNumber))
    {
        ch->ChatPacket(1, "This number is already used.");
    }
    else
    {
        m_number_map.emplace(dwNumber, ch->GetPlayerID());
    }
}

auto CNumberEvent::Draw() -> void
{
    if (m_number_map.empty()) [[unlikely]]
        return;

#ifdef LOG // test
    for (BYTE i = 0; i < 100; ++i)
        m_number_map.emplace(i, i);
#endif

    std::vector<DWORD> nVec;
    for (const auto& [key, value] : m_number_map)
    {
        nVec.push_back(key);
    }
    std::shuffle(std::begin(nVec), std::end(nVec), std::random_device());
    DWORD minMax = number(0, nVec.size()-1);
#ifdef LOG
    sys_err("Winner number: %d", nVec[minMax]);
#endif
    if (const auto& it = m_number_map.find(nVec[minMax]); it != m_number_map.end())
    {
        if (auto ch = CHARACTER_MANAGER::instance().FindByPID(it->second); ch)
            ch->ChatPacket(1, "It's your lucky day! You won!");
    }
    m_number_map.clear();
}
#endif