//
// Copyright (c) 2017 The Khronos Group Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "tools.h"

#include "TestNonUniformWorkGroup.h"

REGISTER_TEST(non_uniform_3d_basic)
{
  SubTestExecutor exec(device, context, queue);

  size_t maxWgSize;
  int err;
  err = exec.calculateWorkGroupSize(maxWgSize, Range::BASIC);
  if (err) {
    log_error ("Cannot calculate work group size.");
    return -1;
  }

  // non_uniform_3d_max_wg_size_plus_1_basic
  {
    size_t globalSize[] = {maxWgSize+1, maxWgSize/24, maxWgSize/24};
    size_t localSize[] = {maxWgSize, 1, 1};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BASIC);
  }

  // non_uniform_3d_prime_number_basic
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize, 2*maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    size_t globalSize[] = {maxWgSize/25, primeNumber, maxWgSize/25};
    size_t localSize[] = {2, std::max<size_t>(maxWgSize/4,1), 2};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BASIC);
  }

  // non_uniform_3d_two_prime_numbers_basic
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize, 2*maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    int primeNumber2 = 13;
    size_t globalSize[] = {primeNumber2, maxWgSize/8, primeNumber};
    size_t localSize[] = {8, 4, std::max<size_t>(maxWgSize/32,1)};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BASIC);
  }

  // non_uniform_3d_prime_number_basic_2
  {
    int primeNumber = 113;
    size_t globalSize[] = {primeNumber, primeNumber, primeNumber};
    size_t localSize[] = {8, std::max<size_t>(maxWgSize/32,1), 4};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BASIC);
  }

  // non_uniform_3d_two_prime_numbers_and_ls_null_basic
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize, 2*maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    unsigned int primeNumber2 = 23;
    size_t globalSize[] = {primeNumber, primeNumber2, maxWgSize/16};
    size_t *localSize = NULL;

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BASIC);
  }

  // non_uniform_3d_prime_number_and_ls_null_basic
  {
    unsigned int primeNumber = 113;
    size_t globalSize[] = {primeNumber, primeNumber, primeNumber};
    size_t *localSize = NULL;

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BASIC);
  }

  // non_uniform_3d_three_prime_numbers_basic
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize/2, maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    unsigned int primeNumber2 = 10711;
    unsigned int primeNumber3 = 13;
    size_t globalSize[] = {primeNumber2, primeNumber3, primeNumber3};
    size_t localSize[] = {primeNumber, 1, 1};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BASIC);
  }

  // non_uniform_3d_four_prime_numbers_basic
  {
    unsigned int primeNumber = 541;
    unsigned int primeNumber2 = 251;
    unsigned int primeNumber3 = 13;
    unsigned int primeNumber4 = 17;
    PrimeNumbers::Result2d fit2dResult;
    fit2dResult = PrimeNumbers::fitMaxPrime2d(primeNumber3, primeNumber4, maxWgSize);

    size_t globalSize[] = {primeNumber, primeNumber2, primeNumber3};
    size_t localSize[] = {fit2dResult.Val1, fit2dResult.Val2, 1};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BASIC);
  }

  // non_uniform_3d_six_prime_numbers_basic
  {
    unsigned int primeNumber = 373;
    unsigned int primeNumber2 = 13;
    unsigned int primeNumber3 = 279;
    unsigned int primeNumber4 = 3;
    unsigned int primeNumber5 = 5;
    unsigned int primeNumber6 = 7;
    PrimeNumbers::Result3d fit3dResult;
    fit3dResult = PrimeNumbers::fitMaxPrime3d(primeNumber4,primeNumber5,primeNumber6,maxWgSize );

    size_t globalSize[] = {primeNumber, primeNumber2, primeNumber3};
    size_t localSize[] = {fit3dResult.Val1, fit3dResult.Val2, fit3dResult.Val3};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BASIC);
  }

  return exec.status();
}

REGISTER_TEST(non_uniform_3d_atomics)
{
  SubTestExecutor exec(device, context, queue);

  size_t maxWgSize;
  int err;
  err = exec.calculateWorkGroupSize(maxWgSize, Range::ATOMICS);
  if (err) {
    log_error ("Cannot calculate work group size.");
    return -1;
  }

  // non_uniform_3d_max_wg_size_plus_1_atomics
  {
    size_t globalSize[] = {maxWgSize+1, maxWgSize/24, maxWgSize/24};
    size_t localSize[] = {maxWgSize, 1, 1};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::ATOMICS);
  }

  // non_uniform_3d_prime_number_atomics
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize, 2*maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    size_t globalSize[] = {maxWgSize/25, primeNumber, maxWgSize/25};
    size_t localSize[] = {2, std::max<size_t>(maxWgSize/4,1), 2};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::ATOMICS);
  }

  // non_uniform_3d_two_prime_numbers_atomics
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize, 2*maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    int primeNumber2 = 13;
    size_t globalSize[] = {primeNumber2, maxWgSize/8, primeNumber};
    size_t localSize[] = {8, 4, std::max<size_t>(maxWgSize/32,1)};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::ATOMICS);
  }

  // non_uniform_3d_prime_number_atomics_2
  {
    int primeNumber = 113;
    size_t globalSize[] = {primeNumber, primeNumber, primeNumber};
    size_t localSize[] = {8, std::max<size_t>(maxWgSize/32,1), 4};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::ATOMICS);
  }

  // non_uniform_3d_two_prime_numbers_and_ls_null_atomics
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize, 2*maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    unsigned int primeNumber2 = 23;
    size_t globalSize[] = {primeNumber, primeNumber2, maxWgSize/16};
    size_t *localSize = NULL;

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::ATOMICS);
  }

  // non_uniform_3d_prime_number_and_ls_null_atomics
  {
    unsigned int primeNumber = 113;
    size_t globalSize[] = {primeNumber, primeNumber, primeNumber};
    size_t *localSize = NULL;

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::ATOMICS);
  }

  // non_uniform_3d_three_prime_numbers_atomics
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize/2, maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    unsigned int primeNumber2 = 10711;
    unsigned int primeNumber3 = 13;
    size_t globalSize[] = {primeNumber2, primeNumber3, primeNumber3};
    size_t localSize[] = {primeNumber, 1, 1};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::ATOMICS);
  }

  // non_uniform_3d_four_prime_numbers_atomics
  {
    unsigned int primeNumber = 541;
    unsigned int primeNumber2 = 251;
    unsigned int primeNumber3 = 13;
    unsigned int primeNumber4 = 17;
    PrimeNumbers::Result2d fit2dResult;
    fit2dResult = PrimeNumbers::fitMaxPrime2d(primeNumber3, primeNumber4, maxWgSize);

    size_t globalSize[] = {primeNumber, primeNumber2, primeNumber3};
    size_t localSize[] = {fit2dResult.Val1, fit2dResult.Val2, 1};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::ATOMICS);
  }

  // non_uniform_3d_six_prime_numbers_atomics
  {
    unsigned int primeNumber = 373;
    unsigned int primeNumber2 = 13;
    unsigned int primeNumber3 = 279;
    unsigned int primeNumber4 = 3;
    unsigned int primeNumber5 = 5;
    unsigned int primeNumber6 = 7;
    PrimeNumbers::Result3d fit3dResult;
    fit3dResult = PrimeNumbers::fitMaxPrime3d(primeNumber4, primeNumber5, primeNumber6, maxWgSize);

    size_t globalSize[] = {primeNumber, primeNumber2, primeNumber3};
    size_t localSize[] = {fit3dResult.Val1, fit3dResult.Val2, fit3dResult.Val3};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::ATOMICS);
  }

  return exec.status();
}

REGISTER_TEST(non_uniform_3d_barriers)
{
  SubTestExecutor exec(device, context, queue);

  size_t maxWgSize;
  int err;
  err = exec.calculateWorkGroupSize(maxWgSize, Range::BARRIERS);
  if (err) {
    log_error ("Cannot calculate work group size.");
    return -1;
  }

  // non_uniform_3d_max_wg_size_plus_1_barriers
  {
    size_t globalSize[] = {maxWgSize+1, maxWgSize/24, maxWgSize/24};
    size_t localSize[] = {maxWgSize, 1, 1};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BARRIERS);
  }

  // non_uniform_3d_prime_number_barriers
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize, 2*maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    size_t globalSize[] = {maxWgSize/25, primeNumber, maxWgSize/25};
    size_t localSize[] = {2, std::max<size_t>(maxWgSize/4,1), 2};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BARRIERS);
  }

  // non_uniform_3d_two_prime_numbers_barriers
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize, 2*maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    int primeNumber2 = 13;
    size_t globalSize[] = {primeNumber2, maxWgSize/8, primeNumber};
    size_t localSize[] = {8, 4, std::max<size_t>(maxWgSize/32,1)};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BARRIERS);
  }

  // non_uniform_3d_prime_number_barriers_2
  {
    int primeNumber = 113;
    size_t globalSize[] = {primeNumber, primeNumber, primeNumber};
    size_t localSize[] = {8, std::max<size_t>(maxWgSize/32,1), 4};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BARRIERS);
  }

  // non_uniform_3d_two_prime_numbers_and_ls_null_barriers
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize, 2*maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    unsigned int primeNumber2 = 23;
    size_t globalSize[] = {primeNumber, primeNumber2, maxWgSize/16};
    size_t *localSize = NULL;

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BARRIERS);
  }

  // non_uniform_3d_prime_number_and_ls_null_barriers
  {
    unsigned int primeNumber = 113;
    size_t globalSize[] = {primeNumber, primeNumber, primeNumber};
    size_t *localSize = NULL;

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BARRIERS);
  }

  // non_uniform_3d_three_prime_numbers_barriers
  {
    int primeNumber = PrimeNumbers::getPrimeNumberInRange(maxWgSize/2, maxWgSize);
    if (primeNumber < 1) {
      log_error ("Cannot find proper prime number.");
      return -1;
    }
    unsigned int primeNumber2 = 10711;
    unsigned int primeNumber3 = 13;
    size_t globalSize[] = {primeNumber2, primeNumber3, primeNumber3};
    size_t localSize[] = {primeNumber, 1, 1};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BARRIERS);
  }

  // non_uniform_3d_four_prime_numbers_barriers
  {
    unsigned int primeNumber = 541;
    unsigned int primeNumber2 = 251;
    unsigned int primeNumber3 = 13;
    unsigned int primeNumber4 = 17;
    PrimeNumbers::Result2d fit2dResult;
    fit2dResult = PrimeNumbers::fitMaxPrime2d(primeNumber3, primeNumber4, maxWgSize);

    size_t globalSize[] = {primeNumber, primeNumber2, primeNumber3};
    size_t localSize[] = {fit2dResult.Val1, fit2dResult.Val2, 1};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BARRIERS);
  }


  // non_uniform_3d_six_prime_numbers_barriers
  {
    unsigned int primeNumber = 373;
    unsigned int primeNumber2 = 13;
    unsigned int primeNumber3 = 279;
    unsigned int primeNumber4 = 3;
    unsigned int primeNumber5 = 5;
    unsigned int primeNumber6 = 7;
    PrimeNumbers::Result3d fit3dResult;
    fit3dResult = PrimeNumbers::fitMaxPrime3d(primeNumber4,primeNumber5,primeNumber6,maxWgSize );

    size_t globalSize[] = {primeNumber, primeNumber2, primeNumber3};
    size_t localSize[] = {fit3dResult.Val1, fit3dResult.Val2, fit3dResult.Val3};

    exec.runTestNonUniformWorkGroup(sizeof(globalSize)/sizeof(globalSize[0]), globalSize, localSize, Range::BARRIERS);
  }

  return exec.status();
}
