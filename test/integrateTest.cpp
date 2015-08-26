#include <nbody/Vector.h>
#include <nbody/Integrator.h>
#include <gtest/gtest.h>

TEST( vectorTest,  ) {

  auto v = Vector3f{ 1, 0, 0 };
  auto v_perp = Vector3f{ 0, 1, -1 };
  auto Integrator<float> iv{v, v_perp, 1.0f};
  ASSERT_FLOAT_EQ( iv.next() , Vector3f{ );
}

TEST( vectorTest, crossProduct ) {
  auto v = Vector3f{ 1, 2, 3 };
  auto i = Vector3f{ 1, 0, 0 };
  auto j = Vector3f{ 0, 1, 0 };
  auto k = Vector3f{ 0, 0, 1 };
  ASSERT_FLOAT_EQ( cross( v, v ).norm(), 0.0f );
  ASSERT_FLOAT_EQ( ( cross( i, j ) - k ).norm(), 0.0f );
  ASSERT_FLOAT_EQ( ( cross( j, k ) - i ).norm(), 0.0f );
  ASSERT_FLOAT_EQ( ( cross( k, i ) - j ).norm(), 0.0f );
}
