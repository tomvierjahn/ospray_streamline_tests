((nil
  (tv-project-name . "OSPRay Streamline Tests")
  (projectile-project-compilation-dir . "build/darwin.x86_64.apple-clang")
  (projectile-project-compilation-cmd . "cmake --build . -- -j4")
  (projectile-project-test-cmd . "cmake --build . -- -j4 && CTEST_OUTPUT_ON_FAILURE=1 ctest -E  \"^integration_\"")
))
