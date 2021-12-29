#pragma once
class CNumberEvent : public singleton<CNumberEvent>
{
    public:
        auto    AddNumber(LPCHARACTER ch, DWORD dwNumber) -> void;
        auto    Draw() -> void;

    private:
        using number_map = std::map<DWORD, DWORD>; // number, character ID
        number_map   m_number_map;
};