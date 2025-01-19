#pragma once

#include <Volund/Volund.h>

#include <memory>

#define EDITOR_CMD_LOAD_SCENE (VOLUND_EVENT_USER + 1)
#define EDITOR_CMD_RELOAD_SCENE (VOLUND_EVENT_USER + 2)
#define EDITOR_CMD_SAVE_SCENE (VOLUND_EVENT_USER + 3)
#define EDITOR_CMD_NEW_SCENE (VOLUND_EVENT_USER + 4)
#define EDITOR_CMD_PLAY (VOLUND_EVENT_USER + 5)
#define EDITOR_CMD_PAUSE (VOLUND_EVENT_USER + 6)

#define EDITOR_EVENT_RESET (VOLUND_EVENT_USER + 10)

class Editor;

class EditorContext
{
public:

    VL::Entity selectedEntity = VOLUND_ENTITY_NULL;
    std::shared_ptr<VL::LuaState> state;

    bool IsPaused();

    void Enqueue(const VL::Event& e);

    EditorContext(std::shared_ptr<VL::Dispatcher> dispatcher);

private:

    friend class Editor;

    bool m_paused = true;

    std::shared_ptr<VL::Dispatcher> m_dispatcher;
};
