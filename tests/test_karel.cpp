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

TEST_F(TestKarel, LINE) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LINE, 2, 5}
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(2, runtime->line) << "Line was not set correctly";
  ASSERT_EQ(5, runtime->column) << "Column was not set correclty";
}

TEST_F(TestKarel, SRET) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LOAD, 12},
    {karel::Opcode::SRET}
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(12, runtime->ret) << "RET was not set correctly";
}

TEST_F(TestKarel, LRET) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LRET},
    {karel::Opcode::INC, 1},
    {karel::Opcode::SRET},
  };
  runtime->ret = 10;
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(runtime->ret, 11) << "RET not set correclty";
}

TEST_F(TestKarel, INC) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LOAD, 10},
    {karel::Opcode::INC, 4},
    {karel::Opcode::SRET},
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(14, runtime->ret) << "RET was not set correctly";
}

TEST_F(TestKarel, DEC) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LOAD, 10},
    {karel::Opcode::DEC, 4},
    {karel::Opcode::SRET},
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(6, runtime->ret) << "RET was not set correctly";
}

TEST_F(TestKarel, LT_3_5) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LOAD, 3},
    {karel::Opcode::LOAD, 5},
    {karel::Opcode::LT},
    {karel::Opcode::SRET},
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(1, runtime->ret) << "RET was not set correctly";
}

TEST_F(TestKarel, LT_5_3) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LOAD, 5},
    {karel::Opcode::LOAD, 3},
    {karel::Opcode::LT},
    {karel::Opcode::SRET},
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(0, runtime->ret) << "RET was not set correctly";
}

TEST_F(TestKarel, LT_5_5) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LOAD, 5},
    {karel::Opcode::LOAD, 5},
    {karel::Opcode::LT},
    {karel::Opcode::SRET},
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(0, runtime->ret) << "RET was not set correctly";
}



TEST_F(TestKarel, LTE_3_5) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LOAD, 3},
    {karel::Opcode::LOAD, 5},
    {karel::Opcode::LTE},
    {karel::Opcode::SRET},
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(1, runtime->ret) << "RET was not set correctly";
}

TEST_F(TestKarel, LTE_5_3) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LOAD, 5},
    {karel::Opcode::LOAD, 3},
    {karel::Opcode::LTE},
    {karel::Opcode::SRET},
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(0, runtime->ret) << "RET was not set correctly";
}

TEST_F(TestKarel, LTE_5_5) {
  std::vector<karel::Instruction> program = {
    {karel::Opcode::LOAD, 5},
    {karel::Opcode::LOAD, 5},
    {karel::Opcode::LTE},
    {karel::Opcode::SRET},
  };
  auto result = karel::Run(program,runtime);
  ASSERT_EQ(result, karel::RunResult::OK) << "Run did not end in OK status";
  ASSERT_EQ(1, runtime->ret) << "RET was not set correctly";
}