// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef BDG_PALO_BE_SRC_QUERY_CODEGEN_PALO_IR_DATA_H
#define BDG_PALO_BE_SRC_QUERY_CODEGEN_PALO_IR_DATA_H

/// Header with declarations of Impala IR data. Definitions of the arrays are generated
/// separately.

extern const unsigned char palo_sse_llvm_ir[];
extern const size_t palo_sse_llvm_ir_len;

extern const unsigned char palo_no_sse_llvm_ir[];
extern const size_t palo_no_sse_llvm_ir_len;

#endif
