#include <enginethingy.hpp>
#include <iostream>

class TestEvent : public EngineThingy::Event {
public:
	TestEvent() = default;
	virtual EngineThingy::EventCategory CategoryMask() const override {
		return ET_EVENT_CATEGORY_MASK(EngineThingy::EventCategory::Mouse);
	}
	ET_EVENT_CLASS_TYPE(EngineThingy::EventType::MouseButtonPress)
};

int main(int argc, char const *argv[]) {
	using namespace EngineThingy;
	static constexpr auto mask =
		buildEventCategoryMask<EventCategory::Application,
							   EventCategory::Window>();
	static_assert(checkCategory(mask, EventCategory::Application));
	static_assert(checkCategory(mask, EventCategory::Window));
	static_assert(!checkCategory(mask, EventCategory::Mouse));

	TestEvent evt;
	assert(evt.HasCategory(EngineThingy::EventCategory::Mouse));
	assert(evt.Type() == EngineThingy::EventType::MouseButtonPress);
	assert(!strcmp(evt.Name(), "EngineThingy::EventType::MouseButtonPress"));
	return 0;
}
