#include <Kal/HashArray.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <rapidcheck/Assertions.h>
#include <rapidcheck/gtest.h>

RC_GTEST_PROP (HashArray,
               The_Size_Increases_By_1_If_A_New_Element_Is_Added_To_The_List,
               (i32 num)) {
  HashArray<i32> arr;
  RC_ASSERT (arr.getSize ( ) == 0);
  arr.push (num);
  RC_ASSERT (arr.getSize ( ) == 1);
}

RC_GTEST_PROP (
  HashArray,
  The_Size_Does_Not_Increase_If_The_Same_Element_Is_Added_To_The_List,
  (i32 num)) {
  HashArray<i32> arr;
  RC_ASSERT (arr.getSize ( ) == 0);
  arr.push (num);
  RC_ASSERT (arr.getSize ( ) == 1);
  arr.push (num);
  RC_ASSERT (arr.getSize ( ) == 1);
}

RC_GTEST_PROP (HashArray, An_Element_Can_Be_Retrieved, (i32 num)) {
  HashArray<i32> arr;
  auto           i = arr.push (num);
  RC_ASSERT (arr.get (i) == num);
}

RC_GTEST_PROP (HashArray, An_Element_Can_Be_Removed, (i32 num)) {
  HashArray<i32> arr;
  auto           i = arr.push (num);
  RC_ASSERT (arr.getSize ( ) == 1);
  RC_ASSERT (arr.get (i) == num);
  RC_ASSERT (arr.contains (num));
  RC_ASSERT (arr.pop (i) == num);
  RC_ASSERT (arr.getSize ( ) == 0);
  RC_ASSERT_FALSE (arr.contains (num));
}
