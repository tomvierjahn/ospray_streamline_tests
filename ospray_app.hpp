//------------------------------------------------------------------------------
// OSPRay Streamline Tests
//
// Copyright (c) 2018 RWTH Aachen University, Germany,
// Virtual Reality & Immersive Visualisation Group.
//------------------------------------------------------------------------------
//                                 License
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------

#ifndef OSPRAY_APP_HPP_
#define OSPRAY_APP_HPP_

#include <memory>

#include "ospray/ospcommon/vec.h"
#include "ospray/ospray_cpp.h"

class OSPRayApp {
public:
  OSPRayApp();

  void Render();
  void Save();

private:
  void SetupStreamlines();
  void SetupModel();
  void SetupCamera();
  void SetupRenderer();
  void SetupLight();

  std::unique_ptr<ospray::cpp::Renderer> renderer_;
  std::unique_ptr<ospray::cpp::Geometry> streamlines_;
  std::unique_ptr<ospray::cpp::Model> model_;
  std::unique_ptr<ospray::cpp::FrameBuffer> framebuffer_;
  std::unique_ptr<ospray::cpp::Camera> camera_;
  // ospray::cpp::Light ambient_light_;

  std::vector<osp::vec3fa> streamline_vertices_{
      {0, 0, 0, 1}, {1, 0, 0, 1}, {2, 1, 0, 1}};
  std::vector<osp::vec4f> streamline_colors_{
      {1, 0, 0, 1}, {0, 1, 0, 1}, {0, 0, 1, 1}};
  std::vector<uint32_t> streamline_indices_{0, 1};

  ospray::cpp::Data streamline_vertex_data_;
  ospray::cpp::Data streamline_color_data_;
  ospray::cpp::Data streamline_index_data_;
};

#endif // OSPRAY_APP_HPP_
