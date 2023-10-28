#include <et/core.hpp>
#include <et/logsystem.hpp>
#include <et/events/event.hpp>

class S {
	static S *_instance;
	S() = default;

	int x;

public:
	static void Init(int x) {
		static S obj;
		obj.x = x;
		_instance = &obj;
	}
	S(const S &) = delete;
	S &operator=(const S &) = delete;
	static S &Instance() { return *_instance; }
	operator int() const { return x; }

	~S() = default;
};
S *S::_instance = nullptr;

struct E {};

int &dummy(int &x) {
	return ++x;
}

int main(int argc, char const *argv[]) {
	static_assert(std::is_same_v<int, EngineThingy::remove_cv_t<int>>,
				  "remove_cv test failed");
	static_assert(std::is_same_v<int, EngineThingy::remove_cv_t<const int>>,
				  "remove_cv test failed");
	static_assert(std::is_same_v<int &, EngineThingy::remove_cv_t<const int &>>,
				  "remove_cv test failed");
	static_assert(EngineThingy::is_singleton_v<S, int>,
				  "is_singleton test failed");
	static_assert(!EngineThingy::is_singleton_v<E>, "is_singleton test failed");
	static_assert(EngineThingy::is_singleton_v<EngineThingy::LogSystem>);

	struct Foo {
		int x = 0;
		virtual int f() const noexcept { return x; }
		int g(int n) { return x += n; }
	} f;
	struct Bar : public Foo {
		int f() const noexcept override { return x + 1; }
	};
	using M1 = decltype(&Foo::f);
	using M2 = decltype(&Foo::g);

	namespace _impl = EngineThingy::_impl;

	static_assert(
		std::is_same_v<_impl::Pack_t<>, _impl::function_info<M1>::ArgPack>);
	static_assert(
		std::is_same_v<_impl::Pack_t<int>, _impl::function_info<M2>::ArgPack>);
	static_assert(std::is_same_v<int, _impl::function_info<M1>::ResType>);

	{
		auto b = EngineThingy::BindMethod(&Foo::f, &f);
		assert(b() == 0);
		auto b2 = EngineThingy::BindMethod(&Foo::g, &f);
		assert(b2(10) == 10);
		assert(f.x == 10);
	}
	{
		f.x = 0;
		auto b = EngineThingy::Bind(&Foo::g, &f, 1);
		assert(b() == 1);
		assert(f.x == 1);
	}
	int x = 1;
	auto b = EngineThingy::Bind(dummy, std::ref(x));
	assert(b() == 2);
	assert(x == 2);

	enum class EnumType : unsigned short {};
	static_assert(
		std::is_same_v<_impl::make_int<EnumType>::type, unsigned short>);
	static_assert(std::is_same_v<int, _impl::make_int<int>::type>);
	static_assert(std::is_same_v<unsigned, _impl::make_int<unsigned>::type>);

	static_assert(EngineThingy::BinaryOr<int>(1, 2, 4) == 7);
	static_assert(_impl::is_static_castable_to<char, int>::value);
	static_assert(
		_impl::is_static_castable_to<EngineThingy::EventType, int>::value);

	static constexpr auto mask =
		EngineThingy::BinaryOr<int>(EngineThingy::EventCategory::Application,
									EngineThingy::EventCategory::Window);
	static_assert(mask == 3);

	static_assert(EngineThingy::MakeLayerMask(0U, 1U, 2U) == 7);
}
