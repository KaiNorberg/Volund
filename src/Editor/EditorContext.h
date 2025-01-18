#pragma once

#include <Volund.h>

#define EDITOR_EVENT_LOAD_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 1)
#define EDITOR_EVENT_RELOAD_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 2)
#define EDITOR_EVENT_SAVE_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 3)
#define EDITOR_EVENT_NEW_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 4)
#define EDITOR_EVENT_RESET (VOLUND_HIGHEST_EVENT_TYPE + 5)
#define EDITOR_EVENT_PLAY (VOLUND_HIGHEST_EVENT_TYPE + 6)
#define EDITOR_EVENT_PAUSE (VOLUND_HIGHEST_EVENT_TYPE + 7)

class Editor;

class EditorContext
{
public:

    VL::Entity SelectedEntity = VOLUND_NULL_ENTITY;

    std::shared_ptr<VL::LuaState> State;

    bool IsPaused();

    void Enqueue(const VL::Event& e);

    EditorContext(std::shared_ptr<VL::Dispatcher> dispatcher);

private:

    friend class Editor;

    bool m_Paused;

    std::shared_ptr<VL::Dispatcher> m_Dispatcher;
};
