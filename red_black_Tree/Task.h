#pragma once
#include<coroutine>
#include <stack>
#include <map>
using namespace std;
template<typename Ty>
struct Task
{
	struct promise_type {
		using value_pointer_v = Ty;
		auto get_return_object() {
			return Task<Ty>{ Handle::from_promise(*this) };
		}
		suspend_always initial_suspend() noexcept {
			return {};
		}
		suspend_always final_suspend() noexcept {
			return {};
		}
		void unhandled_exception() {
			std::terminate();
		}
		std::suspend_always yield_value(value_pointer_v value) noexcept {
			Task::current_p = value;
			return {};
		}
		void return_value(value_pointer_v p)
		{
			return ;
		}
	};
	using value_pointer_v = Ty;
	using Handle = std::coroutine_handle<promise_type>;
	static Handle _m_coroutine;
	static value_pointer_v current_p;
public:
	Task(Handle m_coroutine) {
		_m_coroutine = m_coroutine;
	}
};

template<typename Ty>
Ty Task<Ty>::current_p = nullptr;

template<typename Ty>
std::coroutine_handle<typename Task<Ty>::promise_type> Task<Ty>::_m_coroutine = nullptr;


template<typename Ty>
Task<Ty> inorder(Ty p) {
	if (p)
	{
		stack<pair<Ty, bool>>sp;
		sp.push({ p,false });
		while (!sp.empty())
		{
			auto root = sp.top().first;
			auto visited = sp.top().second;
			sp.pop();
			if(!root)
				continue;
			if (visited)
			{
				co_yield root;
			}
			else
			{
				sp.push({ root->right, false });
				sp.push({ root, true });
				sp.push({ root->left, false });
			}
		}
	}
	co_return p;
}
