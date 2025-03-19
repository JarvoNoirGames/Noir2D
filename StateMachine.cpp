#include "StateMachine.h"

namespace Noir2D
{
    void StateMachine::PushState(std::unique_ptr<State> state) 
    {
        _states.push(std::move(state));
        _states.top()->Init();
    }

    void StateMachine::PopState() 
    {
        if (!_states.empty()) {
            _states.top()->Cleanup();
            _states.pop();
        }
    }

    void StateMachine::ChangeState(std::unique_ptr<State> state) 
    {
        while (!_states.empty()) {
            _states.top()->Cleanup();
            _states.pop();
        }
        PushState(std::move(state));
    }

    State* StateMachine::GetActiveState() const 
    {
        return _states.empty() ? nullptr : _states.top().get();
    }

    bool StateMachine::IsEmpty() const
    {
        return _states.empty();
    }

    void StateMachine::Update(float deltaTime) 
    {
        if (!_states.empty()) _states.top()->Update(deltaTime);
    }

    void StateMachine::Render(float deltaTime) 
    {
        if (!_states.empty()) _states.top()->Render(deltaTime);
    }
    void StateMachine::Cleanup()
    {
        while (!_states.empty())
        {
            _states.pop();
        }
    }
}