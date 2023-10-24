#include <et/meta.hpp>
#include <et/logsystem.hpp>

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
	static S &Instance() { return *_instance; }
	operator int() const { return x; }

	~S() = default;
};
S *S::_instance = nullptr;

struct E {};

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
}
