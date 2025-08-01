/* Copyright 2024 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "xla/backends/gpu/codegen/cudnn.h"

#include <memory>

#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "xla/backends/gpu/codegen/fusion_emitter.h"
#include "xla/backends/gpu/runtime/cudnn_thunk.h"
#include "xla/backends/gpu/runtime/thunk.h"
#include "xla/codegen/emitters/kernel_arguments.h"
#include "xla/hlo/ir/hlo_instructions.h"
#include "xla/service/gpu/gpu_constants.h"
#include "xla/service/gpu/ir_emitter_context.h"
#include "xla/service/gpu/kernel_reuse_cache.h"
#include "xla/tsl/platform/statusor.h"

namespace xla {
namespace gpu {

absl::StatusOr<FusionEmissionResult> CuDnnFusion::Emit(
    IrEmitterContext& ir_emitter_context,
    const HloFusionInstruction& fusion) const {
  VLOG(3) << fusion.ToString();

  TF_ASSIGN_OR_RETURN(
      auto kernel_arguments,
      emitters::KernelArguments::Create(ir_emitter_context.buffer_assignment(),
                                        GetDefaultBufferAlignment(), &fusion));
  FusionEmissionResult result;
  result.thunks.emplace_back(std::make_unique<CuDnnThunk>(
      GetComputationFingerprint(fusion.fused_instructions_computation(), {}),
      Thunk::ThunkInfo::WithProfileAnnotation(&fusion),
      kernel_arguments.GetArgumentBufferSlices(),
      kernel_arguments.GetArgumentOutputFlags()));
  return result;
}

}  // namespace gpu
}  // namespace xla
