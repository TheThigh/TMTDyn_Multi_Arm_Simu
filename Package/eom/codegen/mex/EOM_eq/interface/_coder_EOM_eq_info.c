/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_EOM_eq_info.c
 *
 * Code generation for function 'EOM_eq'
 *
 */

/* Include files */
#include "_coder_EOM_eq_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void);

/* Function Definitions */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char_T *data[9] = {
      "789ced9a3b6fd35014c71d68cb43826681952c8c94bc94b66c79a755e3388df36c50ead8"
      "37a91b5fdbf1234d2a5666243684ba33c2c682040312940f006c0cf0"
      "01f8000892d86e1a4b960bb11c62f948d1cdc949f2f739c7fee9e8ea229eadac0741909b"
      "8862fda0b2de507dafba5e42a64d1ff7a8eb359dafd932b234f53b2d",
      "fe445d498e95405f521c9680e0ec971407699660257cc003440022c7f400358eb46806e0"
      "340485f30e3af260ea5ce8cc198546efe30780ec1464880807e2e40a"
      "99f3ce593d5e1be4bb74c17a540ceae1d5c5f7920f130feabbbe7bbe3803a0c8b1f5c26e"
      "d487095c5b2060bd40439921249a637d1841768836a8e3593c31601b",
      "c14654808dd8f0437ef8aa97fcfe601d70b09ecc651ba0bb06b53cf819f35835c9438b8b"
      "d2f032c906a4a9862801feac8efb33eaaf18eaafa8ba824c4a93be7d"
      "98518f30d49b8e5bdd375dfdd6a0aa635647adfe6679e9d7c9f7af8ed7ebe1af1e3bf5ee"
      "6077dfd8a9a7d9bcf4fa06ff77d1fbf2b6819e57178f1e87db54974a",
      "14933415df4e1f8722d9722836b90ecc44c7ec3a1003dfaeff770a97f767cc63d9300f25"
      "d23a6c745288f9fd6e1587294e6e32c0ba3e950df5a6e356f7695cb7"
      "217dede20489d9cbdd673f3e7eb2534f33a773b717413b18e81e8588eac1ce402a4addd6"
      "269972b9eb34ee9a7170c80f9a4d2d2e77e7d527a56ee67d5a54ee3e",
      "0abe73b98b58cfdd4c186cc537fa6d5928c641d61f956a3539e8cebb737f9eed9e77f1c3"
      "86eccebb7fdfa771dd1c3cef9e9c7e73b98b58cfdd7034915b6fcbe8"
      "7aa452a3e8cc602b99f797d22e779dc6dd259d3fc94389081c1c617761b95b32d49b8e5b"
      "dda751dd469bbc4ee5eee7a7ab2fecd4d3cce9dc45f9be9cc3457f9b",
      "de2e542268962f74daf98ccb5da771d78c839010c5546071b93baf3e2975b36f9f81b699"
      "bbcf7f9dbcb4534f33a77337116b93181a08a09d169f8bf58aa59dca"
      "71c4dd6798fbf36cf57907a3732c5e5d5ce4050af2a9805ff5e7c5e1b733eaed19ea4dc7"
      "2d3fefa0d54f3de9e0541e7f7975ffd44e3dcd9ccee35a271f8b3603",
      "852a9e0eb180a092d866b4e6ee3ffc773cde9f318f0bcdc141770efea73938e8dc39f87d"
      "f3f1773bf534733a7737d2f16dbc5c82d516599213f47a3f9fe94512"
      "2e77e7fd3c5bcddd2b867928118623a8d106c4a2cebd5543bde9b8d57d52eb66fbf95ebb"
      "f97bf967feb79d7a9a2d2a7f6f19e87975f12348348566209587dd0d",
      "06f4319461cb3564f1f9fb07f3e949bd",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 12944U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *epFieldName[6] = {
      "Name",           "NumberOfInputs", "NumberOfOutputs",
      "ConstantInputs", "FullPath",       "TimeStamp"};
  const char_T *propFieldName[6] = {"Version",      "ResolvedFunctions",
                                    "Checksum",     "EntryPoints",
                                    "CoverageInfo", "IsPolymorphic"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 6, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 1);
  emlrtSetField(xEntryPoints, 0, (const char_T *)"Name",
                emlrtMxCreateString((const char_T *)"EOM_eq"));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"NumberOfInputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"NumberOfOutputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 0, (const char_T *)"FullPath",
      emlrtMxCreateString(
          (const char_T
               *)"D:\\R - Clemson\\SRA Program\\Simulation "
                 "Package\\TMTDyn_2_Arm_Backpack\\V002\\eom\\EOM_eq.m"));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"TimeStamp",
                emlrtMxCreateDoubleScalar(738965.43864583329));
  xResult =
      emlrtCreateStructMatrix(1, 1, 6, (const char_T **)&propFieldName[0]);
  emlrtSetField(
      xResult, 0, (const char_T *)"Version",
      emlrtMxCreateString((const char_T *)"9.12.0.2170939 (R2022a) Update 6"));
  emlrtSetField(xResult, 0, (const char_T *)"ResolvedFunctions",
                (mxArray *)emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, (const char_T *)"Checksum",
                emlrtMxCreateString((const char_T *)"BLur9MmfVHqrms4AsUZ63F"));
  emlrtSetField(xResult, 0, (const char_T *)"EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_EOM_eq_info.c) */
