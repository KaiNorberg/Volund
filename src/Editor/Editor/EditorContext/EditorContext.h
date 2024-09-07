#pragma once

#include <Volund.h>

#define EDITOR_EVENT_TYPE_LOAD_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 1)
#define EDITOR_EVENT_TYPE_RELOAD_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 2)
#define EDITOR_EVENT_TYPE_SAVE_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 3)
#define EDITOR_EVENT_TYPE_NEW_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 4)
#define EDITOR_EVENT_TYPE_RESET (VOLUND_HIGHEST_EVENT_TYPE + 5)
#define EDITOR_EVENT_TYPE_PLAY (VOLUND_HIGHEST_EVENT_TYPE + 6)
#define EDITOR_EVENT_TYPE_PAUSE (VOLUND_HIGHEST_EVENT_TYPE + 7)

class Editor;

class EditorContext
{
public:

    VL::Entity SelectedEntity = VOLUND_NULL_ENTITY;

    VL::Ref<VL::GameState> GameState;

    bool IsPaused();

    void Enqueue(const VL::Event& e);

    EditorContext(VL::Ref<VL::Dispatcher> dispatcher);

private:
    friend class Editor;

    bool m_Paused;

    VL::Ref<VL::Dispatcher> m_Dispatcher;
};
