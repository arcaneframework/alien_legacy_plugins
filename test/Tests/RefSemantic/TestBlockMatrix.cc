#include <gtest/gtest.h>

#include <alien/ref/AlienRefSemantic.h>

namespace Environment {
extern Arccore::MessagePassing::IMessagePassingMng* parallelMng();
}

TEST(TestBlockMatrix, DefaultConstructor)
{
  Alien::BlockMatrix m;
  ASSERT_EQ(m.rowSpace().size(), 0);
  ASSERT_EQ(m.colSpace().size(), 0);
  // ASSERT_THROW(m.distribution(), Alien::FatalErrorException);
  ASSERT_THROW(m.block(), Alien::FatalErrorException);
}

TEST(TestBlockMatrix, OneSpaceConstructor)
{
  Alien::Space s(10, "MySpace");
  Alien::MatrixDistribution mdist(s, s, Environment::parallelMng());
  Alien::Block block(2);
  Alien::BlockMatrix m(block, mdist);
  ASSERT_EQ(m.rowSpace().size(), 10);
  ASSERT_EQ(m.colSpace().size(), 10);
  ASSERT_EQ(m.distribution().globalRowSize(), 10);
  ASSERT_EQ(m.distribution().globalColSize(), 10);
  ASSERT_NO_THROW(m.block());
  ASSERT_EQ(m.block().size(), 2);
}

TEST(TestBlockMatrix, TwoSpacesConstructor)
{
  Alien::Space rowS(10, "MySpace");
  Alien::Space colS(5, "MySpace2");
  Alien::MatrixDistribution mdist(rowS, colS, Environment::parallelMng());
  Alien::Block block(2);
  Alien::BlockMatrix m(block, mdist);
  ASSERT_EQ(m.rowSpace().size(), 10);
  ASSERT_EQ(m.colSpace().size(), 5);
  ASSERT_EQ(m.distribution().globalRowSize(), 10);
  ASSERT_EQ(m.distribution().globalColSize(), 5);
  ASSERT_NO_THROW(m.block());
  ASSERT_EQ(m.block().size(), 2);
}

TEST(TestBlockMatrix, OneSizeConstructor)
{
  Alien::MatrixDistribution mdist(10, 10, Environment::parallelMng());
  Alien::Block block(2);
  Alien::BlockMatrix m(block, mdist);
  ASSERT_EQ(m.rowSpace().size(), 10);
  ASSERT_EQ(m.colSpace().size(), 10);
  ASSERT_EQ(m.distribution().globalRowSize(), 10);
  ASSERT_EQ(m.distribution().globalColSize(), 10);
  ASSERT_NO_THROW(m.block());
  ASSERT_EQ(m.block().size(), 2);
}

TEST(TestBlockMatrix, TwoSizesConstructor)
{
  Alien::MatrixDistribution mdist(10, 5, Environment::parallelMng());
  Alien::Block block(2);
  Alien::BlockMatrix m(block, mdist);
  ASSERT_EQ(m.rowSpace().size(), 10);
  ASSERT_EQ(m.colSpace().size(), 5);
  ASSERT_EQ(m.distribution().globalRowSize(), 10);
  ASSERT_EQ(m.distribution().globalColSize(), 5);
  ASSERT_NO_THROW(m.block());
  ASSERT_EQ(m.block().size(), 2);
}

TEST(TestBlockMatrix, RValueConstructor)
{
  Alien::MatrixDistribution mdist(10, 10, Environment::parallelMng());
  Alien::Block block(2);
  Alien::BlockMatrix m(block, mdist);
  Alien::BlockMatrix m2(std::move(m));
  ASSERT_EQ(m2.rowSpace().size(), 10);
  ASSERT_EQ(m2.colSpace().size(), 10);
  ASSERT_EQ(m2.distribution().globalRowSize(), 10);
  ASSERT_EQ(m2.distribution().globalColSize(), 10);
  ASSERT_NO_THROW(m2.block());
  ASSERT_EQ(m2.block().size(), 2);
  // Seg fault as m doesn't have an impl any more but should it not raise an exception
  // (like DefaultConstructor) ?
  // ASSERT_THROW(m.rowSpace(), Alien::FatalErrorException);
  // ASSERT_THROW(m.colSpace(), Alien::FatalErrorException);
  // ASSERT_THROW(m.distribution(), Alien::FatalErrorException);
  // ASSERT_THROW(m.block(), Alien::FatalErrorException);
}

TEST(TestBlockMatrix, RValueAssignment)
{
  Alien::MatrixDistribution mdist(10, 10, Environment::parallelMng());
  Alien::Block block(2);
  Alien::BlockMatrix m(block, mdist);
  Alien::BlockMatrix m2;
  m2 = std::move(m);
  ASSERT_EQ(m2.rowSpace().size(), 10);
  ASSERT_EQ(m2.colSpace().size(), 10);
  ASSERT_EQ(m2.distribution().globalRowSize(), 10);
  ASSERT_EQ(m2.distribution().globalColSize(), 10);
  ASSERT_NO_THROW(m2.block());
  ASSERT_EQ(m2.block().size(), 2);
  // Seg fault as m doesn't have an impl any more but should it not raise an exception
  // (like DefaultConstructor) ?
  // ASSERT_THROW(m.rowSpace(), Alien::FatalErrorException);
  // ASSERT_THROW(m.colSpace(), Alien::FatalErrorException);
  // ASSERT_THROW(m.distribution(), Alien::FatalErrorException);
  // ASSERT_THROW(m.block(), Alien::FatalErrorException);
}

TEST(TestBlockMatrix, InitMethod)
{
  Alien::BlockMatrix m;
  Alien::MatrixDistribution mdist(10, 10, Environment::parallelMng());
  Alien::Block block(2);
  m.init(block, mdist);
  ASSERT_EQ(m.rowSpace().size(), 10);
  ASSERT_EQ(m.colSpace().size(), 10);
  ASSERT_EQ(m.distribution().globalRowSize(), 10);
  ASSERT_EQ(m.distribution().globalColSize(), 10);
  ASSERT_NO_THROW(m.block());
  ASSERT_EQ(m.block().size(), 2);
}
