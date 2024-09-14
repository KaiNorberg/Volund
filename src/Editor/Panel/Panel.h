#pragma once

#include "EditorContext.h"

#include "Utils.h"

#include <Volund.h>

class Panel
{
public:

    bool IsWindowHovered();

    void SetName(const std::string& name);
    std::string GetName();
	std::string GetId();

	void Procedure(const VL::Event& e);
	virtual void OnProcedure(const VL::Event& e) = 0;

    virtual ~Panel() = default;

protected:

    bool m_IsActive = true;
    bool m_IsWindowHovered = false;
    std::string m_Name = "";
	std::string m_Id = std::to_string(rand());

    std::shared_ptr<EditorContext> m_Context;
};
