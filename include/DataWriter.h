#include <bits/stdc++.h>
#include "Scene.h"
#include "BasicTypes.h"

namespace GAZE
{
	class DataWriter
	{
	public:
		DataWriter(Scene & scene);
		void Run(Scene & scene);
	};
	typedef std::shared_ptr<DataWriter> DataWriterPtr;
}
