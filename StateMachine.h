#pragma once
#include <memory>
#include <stack>
#include "State.hpp"

namespace Noir2D
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
    public:
        void PushState(std::unique_ptr<State> state);
        void PopState();
        void ChangeState(std::unique_ptr<State> state);
        State* GetActiveState() const;
        bool IsEmpty() const;
        void Update(float deltaTime);
        void Render(float deltaTime);
        void Cleanup();
    private:
        std::stack<std::unique_ptr<State>> _states;
	};
}