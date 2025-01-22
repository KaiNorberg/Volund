#pragma once

#include "EditorContext.hpp"

#include "Utils.hpp"

#include <Volund/Volund.hpp>

class Panel
{
public:

    bool IsWindowHovered();

    void SetName(std::string const& name);
    std::string GetName();
	std::string GetId();

	void Procedure(const VL::Event& e);
	virtual void OnProcedure(const VL::Event& e) = 0;

    virtual ~Panel() = default;

protected:

    bool m_isActive = true;
    bool m_isWindowHovered = false;
    std::string m_name = "";
	std::string m_id = std::to_string(rand());

    std::shared_ptr<EditorContext> m_context;
};
