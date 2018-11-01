/*
Let There Be Light
Copyright (C) 2012 Eric Laukien

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*
Update by Adrian Michalek 2018.10.18
- Some functions were updated and shorten.
- Some code were deleted due to regressions and depracations.
- Names of variables and functions were changed.
- Functionality stays the same.
*/

#include "shadowfin.h"

namespace ls
{
	ShadowFin::ShadowFin()
	{
		umbraBrightness = 1.0f;
		penumbraBrightness = 1.0f;
	}

	ShadowFin::~ShadowFin()
	{
		// ...
	}

	void ShadowFin::render(float transparency)
	{
		if(penumbraBrightness != 1.0f)
		{
			glColor4f(1.0f, 1.0f, 1.0f, penumbraBrightness * transparency);
	
			glBlendFunc(GL_ZERO, GL_SRC_ALPHA);

			glBegin(GL_TRIANGLES);
				glTexCoord2i(0, 1); glVertex2f(rootPos.x, rootPos.y);
				glTexCoord2i(1, 0); glVertex2f(rootPos.x + penumbra.x, rootPos.y + penumbra.y);
				glTexCoord2i(0, 0); glVertex2f(rootPos.x + umbra.x, rootPos.y + umbra.y);
			glEnd();
		}
		else
		{
			if(umbraBrightness != 1.0f)
			{
				float brightness = (1.0f - umbraBrightness) * transparency;
				glColor4f(1.0f, 1.0f, 1.0f, brightness);
			}
			else
				glColor4f(1.0f, 1.0f, 1.0f, transparency);

			glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_TRIANGLES);
				glTexCoord2i(0, 1); glVertex2f(rootPos.x, rootPos.y);
				glTexCoord2i(0, 0); glVertex2f(rootPos.x + penumbra.x, rootPos.y + penumbra.y);
				glTexCoord2i(1, 0); glVertex2f(rootPos.x + umbra.x, rootPos.y + umbra.y);
			glEnd();
		}
	
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
}
