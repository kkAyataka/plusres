#include "gtest/gtest.h"

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
   plusres::Error e1("1");
   plusres::Error e2("2", e1);
   plusres::Error e3("3", e2);
   plusres::Error e4("4", e3);


   for (const auto e : e1.stack()) {
       std::cout << e->message() << " ";
   }
   std::cout << std::endl;

   for (const auto e : e2.stack()) {
       std::cout << e->message() << " ";
   }
   std::cout << std::endl;

   for (const auto e : e3.stack()) {
       std::cout << e->message() << " ";
   }
   std::cout << std::endl;

   for (const auto e : e4.stack()) {
       std::cout << e->message() << " ";
   }
   std::cout << std::endl;

   plusres::Result<> res = plusres::Error(false);
   std::cout << res.error().ok() << std::endl;
   */
