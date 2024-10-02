#include <gtest/gtest.h>
#include "../karel.h"
#include<vector>

struct TestKarel : public ::testing::Test {

  karel::Runtime * runtime;
  virtual void SetUp() override {
    runtime = new karel::Runtime();
    //Start world with zeros
    runtime->buzzers = new uint32_t[runtime->width * runtime->height]();
    runtime->walls  = new uint8_t[runtime->width * runtime->height]();
  }
  
  virtual void TearDown() override {
    delete [] (runtime->buzzers);
    delete [] (runtime->walls);
    delete runtime;
  }
};


TEST_F(TestKarel, HALT) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::HALT}
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
}