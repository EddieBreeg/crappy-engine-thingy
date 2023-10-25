#include <et/hash.hpp>

int main(int argc, char const *argv[]) {
	using namespace EngineThingy;

	static_assert(Hash<int>{}(1) == 1, "hash test failed");
	static_assert(Hash<int>{ 1 }(1) == 0, "hash test failed");

	enum class E : uint8_t { Foo = 0, Bar, Baz };

	static_assert(get_hash(E::Baz, 0xff00) == 0xff02, "hash test failed");
	assert(get_hash(std::string_view{ "" }) == 0);
	assert(get_hash(std::string_view{ "" }, 1) != 0);
	return 0;
}
