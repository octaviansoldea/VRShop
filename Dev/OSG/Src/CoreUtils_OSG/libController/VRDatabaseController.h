/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
*
* This library is open source and may be redistributed and/or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.  The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* OpenSceneGraph Public License for more details.
*/

#ifndef VR_DATABASE_CONTROLLER_H
#define VR_DATABASE_CONTROLLER_H

#include <string>
#include <vector>

namespace VR {
	class Scene;

	struct DatabaseController	{
		enum DB_OPERATION {ADD, REMOVE, UPDATE};

		DatabaseController(
			const std::string * apstrScene,
			std::vector<std::string> * apvecstrData,
			DB_OPERATION aenumDBOperation);	//End of constructor

		~DatabaseController();

	private:
		const std::string * m_pstrScene;
		std::vector<std::string> * m_pvecstrData;
		int m_nDBOperation;
	};
}
#endif //VR_DATABASE_CONTROLLER_H