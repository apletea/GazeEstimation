#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <Workflow.h>

int main(int argc, char ** argv)
{
  GAZE::Workflow workflow;
  workflow.Init(argc,argv);
  workflow.Run();
  return 0;
}
