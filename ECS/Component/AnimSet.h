#pragma once
#include <ECS/Component/ComponentEnums.h>
#include <vector>
#include <array>
#include <ECS/Component/Animation.h>
class AnimSet
{
public:
	AnimID animID{ AnimID::Idle };
	AnimSetType type{ AnimSetType::Octo };
	std::array<Animation, 8> animset = { 
		Animation{"Default", Dir::S},
		Animation{"Default", Dir::SE},
		Animation{"Default", Dir::E},
		Animation{"Default", Dir::NE},
		Animation{"Default", Dir::N},
		Animation{"Default", Dir::NW},
		Animation{"Default", Dir::W},
		Animation{"Default", Dir::SW}
	};
	AnimSet()=default;
	~AnimSet()=default;
};