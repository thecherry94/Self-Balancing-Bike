//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: InputOutput_Test.h
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
#ifndef RTW_HEADER_InputOutput_Test_h_
#define RTW_HEADER_InputOutput_Test_h_
#include <stddef.h>
#include "rtwtypes.h"
#include <cmath>
#include <string.h>
#ifndef InputOutput_Test_COMMON_INCLUDES_
# define InputOutput_Test_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 // InputOutput_Test_COMMON_INCLUDES_

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Forward declaration for rtModel
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_struct_Q4Pn1rzU6xbRZxSLhvKVRF_
#define DEFINED_TYPEDEF_FOR_struct_Q4Pn1rzU6xbRZxSLhvKVRF_

typedef struct {
  uint8_T SimulinkDiagnostic;
  uint8_T Model[16];
  uint8_T Block[27];
  uint8_T OutOfRangeInputValue;
  uint8_T NoRuleFired;
  uint8_T EmptyOutputFuzzySet;
} struct_Q4Pn1rzU6xbRZxSLhvKVRF;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_nDiNttezQ8pHMZv76leKsH_
#define DEFINED_TYPEDEF_FOR_struct_nDiNttezQ8pHMZv76leKsH_

typedef struct {
  uint8_T type[6];
  int32_T origTypeLength;
  real_T params[4];
  int32_T origParamLength;
} struct_nDiNttezQ8pHMZv76leKsH;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_rymdL7RCSjnd1DH1clnSMH_
#define DEFINED_TYPEDEF_FOR_struct_rymdL7RCSjnd1DH1clnSMH_

typedef struct {
  struct_nDiNttezQ8pHMZv76leKsH mf[5];
  int32_T origNumMF;
} struct_rymdL7RCSjnd1DH1clnSMH;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_5gUGpOVEbMgJwViR1uvA9F_
#define DEFINED_TYPEDEF_FOR_struct_5gUGpOVEbMgJwViR1uvA9F_

typedef struct {
  uint8_T type[7];
  uint8_T andMethod[3];
  uint8_T orMethod[3];
  uint8_T defuzzMethod[8];
  uint8_T impMethod[3];
  uint8_T aggMethod[3];
  real_T inputRange[8];
  real_T outputRange[2];
  struct_rymdL7RCSjnd1DH1clnSMH inputMF[4];
  struct_rymdL7RCSjnd1DH1clnSMH outputMF;
  real_T antecedent[312];
  real_T consequent[78];
  real_T connection[78];
  real_T weight[78];
  int32_T numSamples;
  int32_T numInputs;
  int32_T numOutputs;
  int32_T numRules;
  int32_T numInputMFs[4];
  int32_T numCumInputMFs[4];
  int32_T numOutputMFs;
  int32_T numCumOutputMFs;
  real_T outputSamplePoints[101];
  int32_T orrSize[2];
  int32_T aggSize[2];
} struct_5gUGpOVEbMgJwViR1uvA9F;

#endif

// Custom Type definition for MATLAB Function: '<S1>/Evaluate Rule Consequents'
#ifndef struct_tag_s5auVAtj0sXVTykAgnl5VDF
#define struct_tag_s5auVAtj0sXVTykAgnl5VDF

struct tag_s5auVAtj0sXVTykAgnl5VDF
{
  uint8_T type[6];
  int32_T origTypeLength;
  real_T params[4];
  int32_T origParamLength;
};

#endif                                 //struct_tag_s5auVAtj0sXVTykAgnl5VDF

#ifndef typedef_s5auVAtj0sXVTykAgnl5VDF
#define typedef_s5auVAtj0sXVTykAgnl5VDF

typedef struct tag_s5auVAtj0sXVTykAgnl5VDF s5auVAtj0sXVTykAgnl5VDF;

#endif                                 //typedef_s5auVAtj0sXVTykAgnl5VDF

#ifndef struct_tag_s4jCmoFoWlljlAPEg5NRbYB
#define struct_tag_s4jCmoFoWlljlAPEg5NRbYB

struct tag_s4jCmoFoWlljlAPEg5NRbYB
{
  s5auVAtj0sXVTykAgnl5VDF mf[5];
  int32_T origNumMF;
};

#endif                                 //struct_tag_s4jCmoFoWlljlAPEg5NRbYB

#ifndef typedef_s4jCmoFoWlljlAPEg5NRbYB
#define typedef_s4jCmoFoWlljlAPEg5NRbYB

typedef struct tag_s4jCmoFoWlljlAPEg5NRbYB s4jCmoFoWlljlAPEg5NRbYB;

#endif                                 //typedef_s4jCmoFoWlljlAPEg5NRbYB

#ifndef struct_tag_spm715gh8k3F5xDewbCFpPB
#define struct_tag_spm715gh8k3F5xDewbCFpPB

struct tag_spm715gh8k3F5xDewbCFpPB
{
  uint8_T type[7];
  uint8_T andMethod[3];
  uint8_T orMethod[3];
  uint8_T defuzzMethod[8];
  uint8_T impMethod[3];
  uint8_T aggMethod[3];
  real_T inputRange[8];
  real_T outputRange[2];
  s4jCmoFoWlljlAPEg5NRbYB inputMF[4];
  s4jCmoFoWlljlAPEg5NRbYB outputMF;
  real_T antecedent[312];
  real_T consequent[78];
  real_T connection[78];
  real_T weight[78];
  int32_T numSamples;
  int32_T numInputs;
  int32_T numOutputs;
  int32_T numRules;
  int32_T numInputMFs[4];
  int32_T numCumInputMFs[4];
  int32_T numOutputMFs;
  int32_T numCumOutputMFs;
  real_T outputSamplePoints[101];
  int32_T orrSize[2];
  int32_T aggSize[2];
};

#endif                                 //struct_tag_spm715gh8k3F5xDewbCFpPB

#ifndef typedef_spm715gh8k3F5xDewbCFpPB
#define typedef_spm715gh8k3F5xDewbCFpPB

typedef struct tag_spm715gh8k3F5xDewbCFpPB spm715gh8k3F5xDewbCFpPB;

#endif                                 //typedef_spm715gh8k3F5xDewbCFpPB

// Custom Type definition for MATLAB Function: '<S1>/Evaluate Rule Antecedents'
#ifndef struct_tag_shKEn0zNPqxPizUTSmxO7uG
#define struct_tag_shKEn0zNPqxPizUTSmxO7uG

struct tag_shKEn0zNPqxPizUTSmxO7uG
{
  uint8_T SimulinkDiagnostic;
  uint8_T Model[16];
  uint8_T Block[27];
  uint8_T OutOfRangeInputValue;
  uint8_T NoRuleFired;
  uint8_T EmptyOutputFuzzySet;
};

#endif                                 //struct_tag_shKEn0zNPqxPizUTSmxO7uG

#ifndef typedef_shKEn0zNPqxPizUTSmxO7uG
#define typedef_shKEn0zNPqxPizUTSmxO7uG

typedef struct tag_shKEn0zNPqxPizUTSmxO7uG shKEn0zNPqxPizUTSmxO7uG;

#endif                                 //typedef_shKEn0zNPqxPizUTSmxO7uG

// Custom Type definition for MATLAB Function: '<S1>/Evaluate Rule Consequents'
#ifndef struct_tag_sculW9uT2riFhoDCGUFgphB
#define struct_tag_sculW9uT2riFhoDCGUFgphB

struct tag_sculW9uT2riFhoDCGUFgphB
{
  uint8_T type[6];
  real_T params[4];
};

#endif                                 //struct_tag_sculW9uT2riFhoDCGUFgphB

#ifndef typedef_sculW9uT2riFhoDCGUFgphB
#define typedef_sculW9uT2riFhoDCGUFgphB

typedef struct tag_sculW9uT2riFhoDCGUFgphB sculW9uT2riFhoDCGUFgphB;

#endif                                 //typedef_sculW9uT2riFhoDCGUFgphB

#ifndef struct_tag_sXsSeVB4E0ntMvFGNG3D1eC
#define struct_tag_sXsSeVB4E0ntMvFGNG3D1eC

struct tag_sXsSeVB4E0ntMvFGNG3D1eC
{
  uint8_T type[5];
  real_T params[3];
};

#endif                                 //struct_tag_sXsSeVB4E0ntMvFGNG3D1eC

#ifndef typedef_sXsSeVB4E0ntMvFGNG3D1eC
#define typedef_sXsSeVB4E0ntMvFGNG3D1eC

typedef struct tag_sXsSeVB4E0ntMvFGNG3D1eC sXsSeVB4E0ntMvFGNG3D1eC;

#endif                                 //typedef_sXsSeVB4E0ntMvFGNG3D1eC

// Constant parameters (default storage)
typedef struct {
  // Expression: fis.outputSamplePoints
  //  Referenced by: '<S1>/Output Sample Points'

  real_T OutputSamplePoints_Value[101];
} ConstP;

// External inputs (root inport signals with default storage)
typedef struct {
  real_T e1;                           // '<Root>/e1'
  real_T e2;                           // '<Root>/e2'
  real_T e3;                           // '<Root>/e3'
  real_T e4;                           // '<Root>/e4'
} ExtU;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T reglerausgang;                // '<Root>/reglerausgang'
} ExtY;

// Real-time Model Data Structure
struct tag_RTM {
  const char_T * volatile errorStatus;
};

// Constant parameters (default storage)
extern const ConstP rtConstP;

// Class declaration for model InputOutput_Test
class InputOutput_TestModelClass {
  // public data and function members
 public:
  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  InputOutput_TestModelClass();

  // Destructor
  ~InputOutput_TestModelClass();

  // Real-Time Model get method
  RT_MODEL * getRTM();

  // private data and function members
 private:
  // Real-Time Model
  RT_MODEL rtM;

  // private member function(s) for subsystem '<Root>'
  real_T trapmf(real_T x, const real_T params[4]);
  real_T trimf(real_T x, const real_T params[3]);
  void createInputMFCache(const real_T inputs[4], real_T inputMFCache[15]);
  int32_T abs_e(int32_T x);
  real_T evaluateAndMethod(const real_T x[2]);
  void trapmf_l(const real_T x[101], const real_T params[4], real_T y[101]);
  void trimf_k(const real_T x[101], const real_T params[3], real_T y[101]);
  void createMamdaniOutputMFCache(const real_T outputSamplePoints[101], real_T
    outputMFCache[505]);
  real_T evaluateOrMethod(const real_T x[2]);
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S1>/InputConversion' : Eliminate redundant data type conversion


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'InputOutput_Test'
//  '<S1>'   : 'InputOutput_Test/Controller'
//  '<S2>'   : 'InputOutput_Test/Controller/Defuzzify Outputs'
//  '<S3>'   : 'InputOutput_Test/Controller/Evaluate Rule Antecedents'
//  '<S4>'   : 'InputOutput_Test/Controller/Evaluate Rule Consequents'

#endif                                 // RTW_HEADER_InputOutput_Test_h_

//
// File trailer for generated code.
//
// [EOF]
//
