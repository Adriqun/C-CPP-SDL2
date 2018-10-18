#pragma once
#include "light.h"

namespace ls
{
	class LightPoint : public Light
	{
	public:
		float directionAngle;
		float spreadAngle;
		float softSpreadAngle;
		float lightSubdivisionSize;

		LightPoint();
		~LightPoint();

		void setDirectionAngle(float newDirectionAngle);
		void incDirectionAngle(float increment);
		const float &getDirectionAngle() const;

		void setSpreadAngle(float newSpreadAngle);
		void incSpreadAngle(float increment);
		const float &getSpreadAngle() const;

		// Inherited
		void renderLightSolidPortion();
		void renderLightSoftPortion();
		void calculateAABB();
	};
}