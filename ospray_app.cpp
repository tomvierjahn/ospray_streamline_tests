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

#include "ospray_app.hpp"

#include <memory>

OSPRayApp::OSPRayApp()
    : renderer_{std::make_unique<ospray::cpp::Renderer>("scivis")},
      streamlines_{std::make_unique<ospray::cpp::Geometry>("streamlines")},
      model_{std::make_unique<ospray::cpp::Model>()},
      framebuffer_{std::make_unique<ospray::cpp::FrameBuffer>(
          ospcommon::vec2i(1024, 768), OSP_FB_SRGBA, OSP_FB_COLOR)},
      camera_{std::make_unique<ospray::cpp::Camera>("perspective")},
      streamline_vertex_data_{streamline_vertices_.size(), OSP_FLOAT3A,
                              streamline_vertices_.data()},
      streamline_color_data_{streamline_colors_.size(), OSP_FLOAT4,
                             streamline_colors_.data()},
      streamline_index_data_{streamline_indices_.size(), OSP_UINT,
                             streamline_indices_.data()} {
  SetupStreamlines();
  SetupModel();
  SetupCamera();
  SetupRenderer();
  SetupLight();
}

void OSPRayApp::SetupStreamlines() {
  streamline_vertex_data_.commit();
  streamline_color_data_.commit();
  streamline_index_data_.commit();

  streamlines_->set("radius", 0.1f);
  streamlines_->set("vertex", streamline_vertex_data_);
  streamlines_->set("vertex.color", streamline_color_data_);
  streamlines_->set("index", streamline_index_data_);
  streamlines_->commit();
}

void OSPRayApp::SetupModel() {
  model_->addGeometry(*streamlines_);
  model_->commit();
}

void OSPRayApp::SetupCamera() {
  camera_->set("aspect", 1024.0f / 768.0f);
  camera_->set("pos", 0.0f, 0.0f, 20.0f);
  camera_->set("dir", 0.0f, 0.0f, -1.0f);
  camera_->set("up", 0.0f, 1.0f, 0.0f);
  camera_->set("nearClip", 5.0f);
  camera_->set("fovy", 45.0f);
  camera_->commit();
}

void OSPRayApp::SetupRenderer() {
  renderer_->set("shadowsEnabled", 1);
  renderer_->set("aoSamples", 8);
  renderer_->set("spp", 16);
  renderer_->set("bgColor", 1.0F, 1.0F, 1.0F, 1.0F);
  renderer_->set("model", *model_);

  renderer_->set("camera", *camera_);
  renderer_->commit();

  renderer_->commit();
}

void OSPRayApp::SetupLight() {
  auto ambient_light = renderer_->newLight("ambient");
  ambient_light.set("intensity", 0.2f);
  ambient_light.commit();

  auto light_handle = ambient_light.handle();
  ospray::cpp::Data lights(1, OSP_LIGHT, &light_handle);
  lights.commit();
  renderer_->set("lights", lights);
  renderer_->commit();
}

void OSPRayApp::Render() {
  framebuffer_->clear(OSP_FB_COLOR);
  renderer_->renderFrame(*framebuffer_, OSP_FB_COLOR);
}

void OSPRayApp::Save() {
  FILE *file = fopen("out.ppm", "wb");
  if (!file) {
    fprintf(stderr, "fopen('%s', 'wb') failed: %d", "out.ppm", errno);
    return;
  }
  fprintf(file, "P6\n%i %i\n255\n", 1024, 768);
  unsigned char *out = (unsigned char *)alloca(3 * 1024);
  uint32_t *pixel =
      reinterpret_cast<uint32_t *>(framebuffer_->map(OSP_FB_COLOR));
  for (int y = 0; y < 768; y++) {
    const unsigned char *in =
        (const unsigned char *)&pixel[(768 - 1 - y) * 1024];
    for (int x = 0; x < 1024; x++) {
      out[3 * x + 0] = in[4 * x + 0];
      out[3 * x + 1] = in[4 * x + 1];
      out[3 * x + 2] = in[4 * x + 2];
    }
    fwrite(out, 3 * 1024, sizeof(char), file);
  }
  fprintf(file, "\n");
  fclose(file);
  framebuffer_->unmap(reinterpret_cast<void *>(pixel));
}
