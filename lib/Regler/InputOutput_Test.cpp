//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: InputOutput_Test.cpp
//
// Code generated for Simulink model 'InputOutput_Test'.
//
// Model version                  : 1.8
// Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
// C/C++ source code generated on : Sat Jan  5 17:49:18 2019
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "InputOutput_Test.h"
#define NumBitsPerChar                 8U

extern "C" {
  extern real_T rtInf;
  extern real_T rtMinusInf;
  extern real_T rtNaN;
  extern real32_T rtInfF;
  extern real32_T rtMinusInfF;
  extern real32_T rtNaNF;
  extern void rt_InitInfAndNaN(size_t realSize);
  extern boolean_T rtIsInf(real_T value);
  extern boolean_T rtIsInfF(real32_T value);
  extern boolean_T rtIsNaN(real_T value);
  extern boolean_T rtIsNaNF(real32_T value);
  typedef struct {
    struct {
      uint32_T wordH;
      uint32_T wordL;
    } words;
  } BigEndianIEEEDouble;

  typedef struct {
    struct {
      uint32_T wordL;
      uint32_T wordH;
    } words;
  } LittleEndianIEEEDouble;

  typedef struct {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  } IEEESingle;
}                                      // extern "C"
  extern "C"
{
  real_T rtInf;
  real_T rtMinusInf;
  real_T rtNaN;
  real32_T rtInfF;
  real32_T rtMinusInfF;
  real32_T rtNaNF;
}

extern "C" {
  extern real_T rtGetInf(void);
  extern real32_T rtGetInfF(void);
  extern real_T rtGetMinusInf(void);
  extern real32_T rtGetMinusInfF(void);
}                                      // extern "C"
  extern "C"
{
  extern real_T rtGetNaN(void);
  extern real32_T rtGetNaNF(void);
}                                      // extern "C"

extern "C" {
  //
  // Initialize the rtInf, rtMinusInf, and rtNaN needed by the
  // generated code. NaN is initialized as non-signaling. Assumes IEEE.
  //
  void rt_InitInfAndNaN(size_t realSize)
  {
    (void) (realSize);
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }

  // Test if value is infinite
  boolean_T rtIsInf(real_T value)
  {
    return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }

  // Test if single-precision value is infinite
  boolean_T rtIsInfF(real32_T value)
  {
    return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }

  // Test if value is not a number
  boolean_T rtIsNaN(real_T value)
  {
    return (boolean_T)((value!=value) ? 1U : 0U);
  }

  // Test if single-precision value is not a number
  boolean_T rtIsNaNF(real32_T value)
  {
    return (boolean_T)(((value!=value) ? 1U : 0U));
  }
}
  extern "C"
{
  //
  // Initialize rtInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  real_T rtGetInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T inf = 0.0;
    if (bitsPerReal == 32U) {
      inf = rtGetInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
    }

    return inf;
  }

  //
  // Initialize rtInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  real32_T rtGetInfF(void)
  {
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
  }

  //
  // Initialize rtMinusInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  real_T rtGetMinusInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T minf = 0.0;
    if (bitsPerReal == 32U) {
      minf = rtGetMinusInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
    }

    return minf;
  }

  //
  // Initialize rtMinusInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  real32_T rtGetMinusInfF(void)
  {
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
  }
}

extern "C" {
  //
  // Initialize rtNaN needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  real_T rtGetNaN(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T nan = 0.0;
    if (bitsPerReal == 32U) {
      nan = rtGetNaNF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      nan = tmpVal.fltVal;
    }

    return nan;
  }

  //
  // Initialize rtNaNF needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  real32_T rtGetNaNF(void)
  {
    IEEESingle nanF = { { 0 } };

    nanF.wordL.wordLuint = 0xFFC00000U;
    return nanF.wordL.wordLreal;
  }
}
// Function for MATLAB Function: '<S1>/Evaluate Rule Antecedents'
  real_T InputOutput_TestModelClass::trapmf(real_T x, const real_T params[4])
{
  real_T y;
  real_T b_y1;
  b_y1 = 0.0;
  y = 0.0;
  if (x >= params[1]) {
    b_y1 = 1.0;
  }

  if (x < params[0]) {
    b_y1 = 0.0;
  }

  if ((params[0] <= x) && (x < params[1]) && (params[0] != params[1])) {
    b_y1 = 1.0 / (params[1] - params[0]) * (x - params[0]);
  }

  if (x <= params[2]) {
    y = 1.0;
  }

  if (x > params[3]) {
    y = 0.0;
  }

  if ((params[2] < x) && (x <= params[3]) && (params[2] != params[3])) {
    y = 1.0 / (params[3] - params[2]) * (params[3] - x);
  }

  if ((b_y1 < y) || rtIsNaN(y)) {
    y = b_y1;
  }

  return y;
}

// Function for MATLAB Function: '<S1>/Evaluate Rule Antecedents'
real_T InputOutput_TestModelClass::trimf(real_T x, const real_T params[3])
{
  real_T y;
  y = 0.0;
  if ((params[0] != params[1]) && (params[0] < x) && (x < params[1])) {
    y = 1.0 / (params[1] - params[0]) * (x - params[0]);
  }

  if ((params[1] != params[2]) && (params[1] < x) && (x < params[2])) {
    y = 1.0 / (params[2] - params[1]) * (params[2] - x);
  }

  if (x == params[1]) {
    y = 1.0;
  }

  return y;
}

// Function for MATLAB Function: '<S1>/Evaluate Rule Antecedents'
void InputOutput_TestModelClass::createInputMFCache(const real_T inputs[4],
  real_T inputMFCache[15])
{
  static const real_T b[4] = { -32.6523809523809, -32.1523809523809,
    -15.9523809523809, -10.7123809523809 };

  static const real_T c[3] = { -20.1, -10.7, -0.0793650793650826 };

  static const real_T d[3] = { -6.58730158730159, -0.317, 6.43 };

  static const real_T e[3] = { -0.238, 9.28571428571428, 19.4 };

  static const real_T f[4] = { 9.44444444444445, 16.0, 30.0, 30.0 };

  static const real_T g[4] = { -78.3142857142857, -49.5142857142857,
    -26.3142857142857, -9.88428571428572 };

  static const real_T h[3] = { -25.9095238095238, -10.4095238095238,
    9.17047619047619 };

  static const real_T i[3] = { -9.21, 9.16666666666666, 26.9 };

  static const real_T j[4] = { 10.6428571428572, 23.4428571428572,
    45.4428571428572, 62.5428571428572 };

  static const real_T k[3] = { -1.8, -1.0, -0.2 };

  real_T tmp[3];
  inputMFCache[0] = trapmf(inputs[0], b);
  inputMFCache[1] = trimf(inputs[0], c);
  inputMFCache[2] = trimf(inputs[0], d);
  inputMFCache[3] = trimf(inputs[0], e);
  inputMFCache[4] = trapmf(inputs[0], f);
  inputMFCache[5] = trapmf(inputs[1], g);
  inputMFCache[6] = trimf(inputs[1], h);
  inputMFCache[7] = trimf(inputs[1], i);
  inputMFCache[8] = trapmf(inputs[1], j);
  inputMFCache[9] = trimf(inputs[2], k);
  tmp[0] = -0.8;
  tmp[1] = 0.0;
  tmp[2] = 0.8;
  inputMFCache[10] = trimf(inputs[2], tmp);
  tmp[0] = 0.2;
  tmp[1] = 1.0;
  tmp[2] = 1.8;
  inputMFCache[11] = trimf(inputs[2], tmp);
  inputMFCache[12] = trimf(inputs[3], k);
  tmp[0] = -0.8;
  tmp[1] = 0.0;
  tmp[2] = 0.8;
  inputMFCache[13] = trimf(inputs[3], tmp);
  tmp[0] = 0.2;
  tmp[1] = 1.0;
  tmp[2] = 1.8;
  inputMFCache[14] = trimf(inputs[3], tmp);
}

// Function for MATLAB Function: '<S1>/Evaluate Rule Antecedents'
int32_T InputOutput_TestModelClass::abs_e(int32_T x)
{
  int32_T y;
  if (x < 0) {
    if (x <= MIN_int32_T) {
      y = MAX_int32_T;
    } else {
      y = -x;
    }
  } else {
    y = x;
  }

  return y;
}

// Function for MATLAB Function: '<S1>/Evaluate Rule Antecedents'
real_T InputOutput_TestModelClass::evaluateAndMethod(const real_T x[2])
{
  real_T y;
  if (x[0] > x[1]) {
    y = x[1];
  } else if (rtIsNaN(x[0])) {
    if (!rtIsNaN(x[1])) {
      y = x[1];
    } else {
      y = x[0];
    }
  } else {
    y = x[0];
  }

  return y;
}

// Function for MATLAB Function: '<S1>/Evaluate Rule Consequents'
void InputOutput_TestModelClass::trapmf_l(const real_T x[101], const real_T
  params[4], real_T y[101])
{
  real_T a;
  real_T b;
  real_T c;
  real_T d;
  int32_T i;
  real_T b_y1;
  real_T y2;
  a = params[0];
  b = params[1];
  c = params[2];
  d = params[3];
  for (i = 0; i < 101; i++) {
    b_y1 = 0.0;
    y2 = 0.0;
    if (x[i] >= b) {
      b_y1 = 1.0;
    }

    if (x[i] < a) {
      b_y1 = 0.0;
    }

    if ((a <= x[i]) && (x[i] < b) && (a != b)) {
      b_y1 = 1.0 / (b - a) * (x[i] - a);
    }

    if (x[i] <= c) {
      y2 = 1.0;
    }

    if (x[i] > d) {
      y2 = 0.0;
    }

    if ((c < x[i]) && (x[i] <= d) && (c != d)) {
      y2 = 1.0 / (d - c) * (d - x[i]);
    }

    if ((b_y1 < y2) || rtIsNaN(y2)) {
      y[i] = b_y1;
    } else {
      y[i] = y2;
    }
  }
}

// Function for MATLAB Function: '<S1>/Evaluate Rule Consequents'
void InputOutput_TestModelClass::trimf_k(const real_T x[101], const real_T
  params[3], real_T y[101])
{
  real_T a;
  real_T b;
  real_T c;
  int32_T i;
  a = params[0];
  b = params[1];
  c = params[2];
  for (i = 0; i < 101; i++) {
    y[i] = 0.0;
    if ((a != b) && (a < x[i]) && (x[i] < b)) {
      y[i] = 1.0 / (b - a) * (x[i] - a);
    }

    if ((b != c) && (b < x[i]) && (x[i] < c)) {
      y[i] = 1.0 / (c - b) * (c - x[i]);
    }

    if (x[i] == b) {
      y[i] = 1.0;
    }
  }
}

// Function for MATLAB Function: '<S1>/Evaluate Rule Consequents'
void InputOutput_TestModelClass::createMamdaniOutputMFCache(const real_T
  outputSamplePoints[101], real_T outputMFCache[505])
{
  static const real_T b[4] = { -2.23, -1.46, -1.03, -0.517460317460317 };

  static const real_T c[3] = { 0.00952, 0.492, 1.0 };

  static const real_T d[3] = { -0.492, -0.0476, 0.492063492063492 };

  static const real_T e[3] = { -1.0, -0.568, -0.00952 };

  static const real_T f[4] = { 0.498, 0.94920634920635, 1.27, 1.27 };

  real_T tmp[101];
  real_T tmp_0[101];
  real_T tmp_1[101];
  real_T tmp_2[101];
  real_T tmp_3[101];
  int32_T i;
  trapmf_l(outputSamplePoints, b, tmp_3);
  trimf_k(outputSamplePoints, c, tmp_2);
  trimf_k(outputSamplePoints, d, tmp_1);
  trimf_k(outputSamplePoints, e, tmp_0);
  trapmf_l(outputSamplePoints, f, tmp);
  for (i = 0; i < 101; i++) {
    outputMFCache[5 * i] = tmp_3[i];
    outputMFCache[1 + 5 * i] = tmp_2[i];
    outputMFCache[2 + 5 * i] = tmp_1[i];
    outputMFCache[3 + 5 * i] = tmp_0[i];
    outputMFCache[4 + 5 * i] = tmp[i];
  }
}

// Function for MATLAB Function: '<S1>/Evaluate Rule Consequents'
real_T InputOutput_TestModelClass::evaluateOrMethod(const real_T x[2])
{
  real_T y;
  if (x[0] < x[1]) {
    y = x[1];
  } else if (rtIsNaN(x[0])) {
    if (!rtIsNaN(x[1])) {
      y = x[1];
    } else {
      y = x[0];
    }
  } else {
    y = x[0];
  }

  return y;
}

// Model step function
void InputOutput_TestModelClass::step()
{
  int32_T mfIndex;
  real_T mVal;
  real_T inputMFCache[15];
  int32_T ruleID;
  int32_T inputID;
  static const int8_T b[312] = { 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 1, 2,
    3, 3, 4, 5, 1, 2, 2, 3, 3, 3, 3, 4, 5, 1, 2, 3, 3, 4, 5, 1, 2, 3, 4, 4, 5, 5,
    1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 5, 1, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 1, 1, 2, 2,
    3, 4, 5, 1, 2, 3, 3, 4, 5, 4, 0, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 0, 0, 0,
    1, -1, -4, 0, 0, 1, -1, 1, 2, 3, 4, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, -4, 4,
    1, -1, 0, 1, 2, 3, 4, 1, 2, 3, 4, 0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 0, -4,
    4, 1, -1, 0, 0, 0, 0, 0, -4, 4, 0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 3, 3, 3,
    3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 2 };

  static const real_T d[78] = { 0.4, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
    0.1, 0.1, 0.1, 0.4, 0.4, 0.4, 0.1, 0.3, 0.3, 0.4, 0.4, 0.1, 0.3, 0.1, 0.1,
    0.1, 0.1, 0.4, 0.4, 0.4, 0.4, 0.1, 0.3, 0.4, 0.4, 0.4, 0.4, 0.4, 0.3, 0.1,
    0.1, 0.3, 0.4, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.4, 0.4, 0.4, 0.4,
    0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.4, 0.3, 0.1, 0.1, 0.3, 0.4, 0.4,
    0.4, 0.4, 0.4, 0.3, 0.1, 0.4, 0.4, 0.1 };

  real_T outputMFCache[505];
  static const int8_T b_0[78] = { 1, 1, 4, 4, 4, 2, 3, 3, 4, 2, 2, 2, 5, 5, 1, 1,
    1, 4, 2, 5, 1, 1, 4, 2, 2, 2, 5, 5, 5, 1, 1, 1, 4, 3, 5, 1, 1, 1, 3, 1, 2, 5,
    1, 1, 1, 4, 3, 2, 2, 3, 3, 5, 5, 1, 1, 3, 3, 4, 4, 3, 2, 5, 5, 5, 1, 4, 5, 3,
    5, 5, 5, 1, 3, 2, 5, 5, 5, 5 };

  real_T rtb_defuzzifiedOutputs;
  real_T rtb_antecedentOutputs[78];
  real_T rtb_aggregatedOutputs[101];
  real_T tmp[4];
  real_T rtb_antecedentOutputs_0[2];
  real_T rtb_aggregatedOutputs_0[2];
  real_T rtb_antecedentOutputs_j;
  int32_T q0;

  // Outputs for Atomic SubSystem: '<Root>/Controller'
  // MATLAB Function: '<S1>/Evaluate Rule Antecedents'
  // :  if SimulateUsing==1 && coder.target('SFun') ...
  // :          && (isa(inputs,'double') || isa(inputs,'single'))
  // :  else
  // :  [antecedentOutputs,sumAntecedentOutputs] = ...
  // :          fuzzy.internal.codegen.evaluateRuleAntecedent(...
  // :          inputs,fis,diagnostics);
  rtb_defuzzifiedOutputs = 0.0;

  // SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport1' incorporates:
  //   Inport: '<Root>/e1'
  //   Inport: '<Root>/e2'
  //   Inport: '<Root>/e3'
  //   Inport: '<Root>/e4'
  //   MATLAB Function: '<S1>/Evaluate Rule Antecedents'

  tmp[0] = rtU.e1;
  tmp[1] = rtU.e2;
  tmp[2] = rtU.e3;
  tmp[3] = rtU.e4;

  // MATLAB Function: '<S1>/Evaluate Rule Antecedents'
  createInputMFCache(tmp, inputMFCache);
  for (ruleID = 0; ruleID < 78; ruleID++) {
    rtb_antecedentOutputs_j = 1.0;
    mfIndex = (int32_T)std::abs((real_T)b[ruleID]);
    if (mfIndex != 0) {
      q0 = abs_e(0);
      if ((q0 < 0) && (mfIndex < MIN_int32_T - q0)) {
        q0 = MIN_int32_T;
      } else if ((q0 > 0) && (mfIndex > MAX_int32_T - q0)) {
        q0 = MAX_int32_T;
      } else {
        q0 += mfIndex;
      }

      mVal = inputMFCache[q0 - 1];
      if (b[ruleID] < 0) {
        q0 = abs_e(0);
        if ((q0 < 0) && (mfIndex < MIN_int32_T - q0)) {
          q0 = MIN_int32_T;
        } else if ((q0 > 0) && (mfIndex > MAX_int32_T - q0)) {
          q0 = MAX_int32_T;
        } else {
          q0 += mfIndex;
        }

        mVal = 1.0 - inputMFCache[q0 - 1];
      }

      rtb_antecedentOutputs_0[0] = 1.0;
      rtb_antecedentOutputs_0[1] = mVal;
      rtb_antecedentOutputs_j = evaluateAndMethod(rtb_antecedentOutputs_0);
    }

    mfIndex = (int32_T)std::abs((real_T)b[ruleID + 78]);
    if (mfIndex != 0) {
      q0 = abs_e(5);
      if ((q0 < 0) && (mfIndex < MIN_int32_T - q0)) {
        q0 = MIN_int32_T;
      } else if ((q0 > 0) && (mfIndex > MAX_int32_T - q0)) {
        q0 = MAX_int32_T;
      } else {
        q0 += mfIndex;
      }

      mVal = inputMFCache[q0 - 1];
      if (b[ruleID + 78] < 0) {
        q0 = abs_e(5);
        if ((q0 < 0) && (mfIndex < MIN_int32_T - q0)) {
          q0 = MIN_int32_T;
        } else if ((q0 > 0) && (mfIndex > MAX_int32_T - q0)) {
          q0 = MAX_int32_T;
        } else {
          q0 += mfIndex;
        }

        mVal = 1.0 - inputMFCache[q0 - 1];
      }

      rtb_antecedentOutputs_0[0] = rtb_antecedentOutputs_j;
      rtb_antecedentOutputs_0[1] = mVal;
      rtb_antecedentOutputs_j = evaluateAndMethod(rtb_antecedentOutputs_0);
    }

    mfIndex = (int32_T)std::abs((real_T)b[ruleID + 156]);
    if (mfIndex != 0) {
      q0 = abs_e(9);
      if ((q0 < 0) && (mfIndex < MIN_int32_T - q0)) {
        q0 = MIN_int32_T;
      } else if ((q0 > 0) && (mfIndex > MAX_int32_T - q0)) {
        q0 = MAX_int32_T;
      } else {
        q0 += mfIndex;
      }

      mVal = inputMFCache[q0 - 1];
      if (b[ruleID + 156] < 0) {
        q0 = abs_e(9);
        if ((q0 < 0) && (mfIndex < MIN_int32_T - q0)) {
          q0 = MIN_int32_T;
        } else if ((q0 > 0) && (mfIndex > MAX_int32_T - q0)) {
          q0 = MAX_int32_T;
        } else {
          q0 += mfIndex;
        }

        mVal = 1.0 - inputMFCache[q0 - 1];
      }

      rtb_antecedentOutputs_0[0] = rtb_antecedentOutputs_j;
      rtb_antecedentOutputs_0[1] = mVal;
      rtb_antecedentOutputs_j = evaluateAndMethod(rtb_antecedentOutputs_0);
    }

    mfIndex = (int32_T)std::abs((real_T)b[ruleID + 234]);
    if (mfIndex != 0) {
      q0 = abs_e(12);
      if ((q0 < 0) && (mfIndex < MIN_int32_T - q0)) {
        q0 = MIN_int32_T;
      } else if ((q0 > 0) && (mfIndex > MAX_int32_T - q0)) {
        q0 = MAX_int32_T;
      } else {
        q0 += mfIndex;
      }

      mVal = inputMFCache[q0 - 1];
      if (b[ruleID + 234] < 0) {
        q0 = abs_e(12);
        if ((q0 < 0) && (mfIndex < MIN_int32_T - q0)) {
          q0 = MIN_int32_T;
        } else if ((q0 > 0) && (mfIndex > MAX_int32_T - q0)) {
          q0 = MAX_int32_T;
        } else {
          q0 += mfIndex;
        }

        mVal = 1.0 - inputMFCache[q0 - 1];
      }

      rtb_antecedentOutputs_0[0] = rtb_antecedentOutputs_j;
      rtb_antecedentOutputs_0[1] = mVal;
      rtb_antecedentOutputs_j = evaluateAndMethod(rtb_antecedentOutputs_0);
    }

    rtb_antecedentOutputs_j *= d[ruleID];
    rtb_defuzzifiedOutputs += rtb_antecedentOutputs_j;
    rtb_antecedentOutputs[ruleID] = rtb_antecedentOutputs_j;
  }

  // MATLAB Function: '<S1>/Evaluate Rule Consequents' incorporates:
  //   Constant: '<S1>/Output Sample Points'

  // :  if SimulateUsing==1 && coder.target('SFun') ...
  // :          && (isa(inputs,'double') || isa(inputs,'single'))
  // :  else
  // :  if strcmp(char(fis.type),'mamdani')
  // :  aggregatedOutputs = ...
  // :              fuzzy.internal.codegen.evaluateRuleConsequentForMamdaniFIS(... 
  // :              antecedentOutputs,fis,samplePoints);
  memset(&rtb_aggregatedOutputs[0], 0, 101U * sizeof(real_T));
  createMamdaniOutputMFCache(rtConstP.OutputSamplePoints_Value, outputMFCache);
  q0 = abs_e(0);
  for (ruleID = 0; ruleID < 78; ruleID++) {
    if ((q0 < 0) && (b_0[ruleID] < MIN_int32_T - q0)) {
      mfIndex = MIN_int32_T;
    } else if ((q0 > 0) && (b_0[ruleID] > MAX_int32_T - q0)) {
      mfIndex = MAX_int32_T;
    } else {
      mfIndex = q0 + b_0[ruleID];
    }

    for (inputID = 0; inputID < 101; inputID++) {
      rtb_antecedentOutputs_0[0] = outputMFCache[(5 * inputID + mfIndex) - 1];
      rtb_antecedentOutputs_0[1] = rtb_antecedentOutputs[ruleID];
      rtb_aggregatedOutputs_0[0] = rtb_aggregatedOutputs[inputID];
      rtb_aggregatedOutputs_0[1] = evaluateAndMethod(rtb_antecedentOutputs_0);
      rtb_aggregatedOutputs[inputID] = evaluateOrMethod(rtb_aggregatedOutputs_0);
    }
  }

  // End of MATLAB Function: '<S1>/Evaluate Rule Consequents'

  // MATLAB Function: '<S1>/Defuzzify Outputs' incorporates:
  //   Constant: '<S1>/Output Sample Points'
  //   MATLAB Function: '<S1>/Evaluate Rule Antecedents'

  // :  if SimulateUsing==1 && coder.target('SFun') && ...
  // :          (isa(aggregatedOutputs,'double') || isa(aggregatedOutputs,'single')) 
  // :  else
  // :  if isequal(fis.type,uint8('mamdani'))
  // :  defuzzifiedOutputs = ...
  // :              fuzzy.internal.codegen.applyMamdaniDefuzzificationMethod(... 
  // :              samplePoints,sumAntecedentOutputs,aggregatedOutputs, ...
  // :              fis,diagnostics);
  if (rtb_defuzzifiedOutputs == 0.0) {
    // Outport: '<Root>/reglerausgang'
    rtY.reglerausgang = 0.0;
  } else {
    rtb_defuzzifiedOutputs = 0.0;
    mVal = rtb_aggregatedOutputs[0];
    for (ruleID = 0; ruleID < 100; ruleID++) {
      mVal += rtb_aggregatedOutputs[ruleID + 1];
    }

    if (mVal == 0.0) {
      // Outport: '<Root>/reglerausgang'
      rtY.reglerausgang = 0.0;
    } else {
      for (ruleID = 0; ruleID < 101; ruleID++) {
        rtb_defuzzifiedOutputs += rtConstP.OutputSamplePoints_Value[ruleID] *
          rtb_aggregatedOutputs[ruleID];
      }

      // Outport: '<Root>/reglerausgang' incorporates:
      //   Constant: '<S1>/Output Sample Points'

      rtY.reglerausgang = 1.0 / mVal * rtb_defuzzifiedOutputs;
    }
  }

  // End of MATLAB Function: '<S1>/Defuzzify Outputs'
  // End of Outputs for SubSystem: '<Root>/Controller'
}

// Model initialize function
void InputOutput_TestModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
}

// Constructor
InputOutput_TestModelClass::InputOutput_TestModelClass()
{
}

// Destructor
InputOutput_TestModelClass::~InputOutput_TestModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
RT_MODEL * InputOutput_TestModelClass::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
