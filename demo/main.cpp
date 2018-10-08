#include <Workflow.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char** argv) {
    GAZE::Workflow workflow;
    workflow.Init (argc, argv);
    workflow.Run ();
    return 0;
}
