//#pragma once
//#include<coroutine>
//template<typename Ty>
//struct Task
//{
//	struct promise_type {
//		using value_pointer_v = Ty;
//		auto get_return_object() {
//			return Task<Ty>{ Handle::from_promise(*this) };
//		}
//		auto initial_suspend() {
//			return std::suspend_never{};
//		}
//		auto final_suspend() {
//			return std::suspend_never{};
//		}
//		void unhandled_exception() {
//			std::terminate();
//		}
//		std::suspend_always yield_value(value_pointer_v value) noexcept {
//			current_p = value;
//			return {};
//		}
//		Task return_value() {
//			return {};
//		}
//		using value_pointer_v = Ty;
//		value_pointer_v current_p;
//		Handle _m_coroutine;
//	};
//	using value_pointer_v = Ty;
//	using Handle = std::coroutine_handle<promise_type>;
//	Handle _m_coroutine;
//	static value_pointer_v current_p;
//public:
//	bool await_ready() const { return false; }
//	void await_resume() { return ; }
//	void await_suspend(std::coroutine_handle<> handle) {
//		_m_coroutine = handle;
//	}
//	Task setPtr(value_pointer_v p) {
//		current_p = p;
//	}
//	static auto getPtr() {
//		return current_p;
//	}
//	Task(Handle m_coroutine){
//		_m_coroutine = m_coroutine;
//	}
//	Handle getHandle() {
//		return _m_coroutine;
//	}
//};
//template<typename Ty>
// Task<Ty> inorder(Ty p) {
//	if (!p)
//		co_return;
//	inorder(p->left);
//	co_await p;
//	inorder(p->right);
//}
