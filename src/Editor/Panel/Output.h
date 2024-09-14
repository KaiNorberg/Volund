#pragma once

#include "Panel.h"

class Output : public Panel
{
public:

    void OnProcedure(const VL::Event& e) override;

    Output(std::shared_ptr<EditorContext> context);

private:
};
