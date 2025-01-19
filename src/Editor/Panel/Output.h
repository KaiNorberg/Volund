#pragma once

#include "Panel.h"

#include <sstream>

class Output : public Panel
{
public:

    void OnProcedure(const VL::Event& e) override;

    Output(std::shared_ptr<EditorContext> context);

private:
    std::vector<std::string> m_lines;
    std::stringstream m_stream;
};
