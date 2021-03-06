#include "BasicTypes.h"
#include "Scene.h"
#include <bits/stdc++.h>
#pragma once

namespace GAZE {
class DataWriter {
    public:
    DataWriter (Scene& scene);
    void Run (Scene& scene);
};
typedef std::shared_ptr<DataWriter> DataWriterPtr;
}
